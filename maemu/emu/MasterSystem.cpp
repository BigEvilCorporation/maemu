#include "MasterSystem.h"
#include "cpu/z80/Interrupts.h"

#include <ion/io/File.h>

namespace emu
{
	MasterSystem::MasterSystem()
	{
		m_Z80 = nullptr;
		m_VDP = nullptr;
		m_PSG = nullptr;
		m_busZ80 = nullptr;
		m_busVDP = nullptr;
		m_memoryControllerZ80 = nullptr;
		m_memoryControllerVRAM = nullptr;
		m_memoryControllerCRAM = nullptr;
		m_rom = nullptr;
		m_ram = nullptr;
		m_vram = nullptr;
		m_cram = nullptr;
		m_portController = nullptr;
		m_joypad = nullptr;
		m_console = nullptr;
		m_romSize = 0;
		m_cycleCount = 0;
		m_scanline = 0;
		m_frameBufferIdx = 0;

		//Construct the system
		BuildSystem();

		//Initial reset
		Reset();
	}

	void MasterSystem::BuildSystem()
	{
		//Create memory controllers and storage
		m_memoryControllerZ80 = new memory::Controller();
		m_memoryControllerVRAM = new memory::Controller();
		m_memoryControllerCRAM = new memory::Controller();
		m_rom = new memory::Mapper(*m_memoryControllerZ80);
		m_ram = new memory::Storage(SMS_ADDR_RAM_START, SMS_ADDR_RAM_END, *m_memoryControllerZ80);
		m_vram = new memory::Storage(0, cpu::vdp::VDP_VRAM_SIZE, *m_memoryControllerVRAM);
		m_cram = new memory::Storage(0, cpu::vdp::VDP_CRAM_SIZE, *m_memoryControllerCRAM);

		//Create port controller
		m_portController = new ports::Controller();

		//Create the buses
		m_busZ80 = new cpu::z80::Bus(*m_memoryControllerZ80, *m_portController);
		m_busVDP = new cpu::vdp::Bus(*m_memoryControllerVRAM, *m_memoryControllerCRAM, *m_portController);

		//Create the CPU
		m_Z80 = new cpu::z80::Z80(*m_busZ80);

		//Create the VDP
		m_VDP = new cpu::vdp::VDP(*m_busVDP);

		//Create the PSG
		m_PSG = new cpu::psg::PSG(*m_portController);

		//Create peripherals
		m_joypad = new peripherals::Joypad(*m_portController);
		m_console = new debug::SDSCConsole(*m_portController);

		//Initialise framebuffers
		//TODO: PAL vs. NTSC
		for (int i = 0; i < SMS_EMU_NUM_FRAMEBUFFERS; i++)
		{
			m_frameBuffers[i].resize(cpu::vdp::VDP_SCREEN_WIDTH * cpu::vdp::VDP_SCANLINES_NTSC);
			std::fill(m_frameBuffers[i].begin(), m_frameBuffers[i].end(), 0);
		}

		//Initialise audio buffer
		m_audioBuffer.reserve(SMS_PSG_OUTPUT_BUFFER_SIZE_SAMPLES);
	}

	bool MasterSystem::LoadROM(const std::string& filename)
	{
		bool success = false;

		ion::io::File file(filename);

		if (file.IsOpen())
		{
			m_romSize = (u32)file.GetSize();

			//Load data
			u8* rom = new u8[m_romSize];

			if (file.Read(rom, m_romSize) == m_romSize)
			{
				//Write to ROM space
				m_rom->Initialise(rom, m_romSize);
				success = true;
			}

			delete rom;
			file.Close();
		}
		
		return success;
	}

	void MasterSystem::Disassemble(std::vector<cpu::z80::disassembler::Instruction>& disassembly)
	{
		cpu::z80::disassembler::Disassemble(m_rom->GetMemory(), m_romSize, disassembly);
	}

	void MasterSystem::Disassemble(std::vector<cpu::z80::disassembler::Instruction>& disassembly, u16 address, int numInstructions)
	{
		cpu::z80::disassembler::Disassemble(*m_memoryControllerZ80, address, numInstructions, disassembly);
	}

	void MasterSystem::Reset()
	{
		//Reset CPUs
		m_Z80->Reset();
		m_VDP->Reset();
		m_PSG->Reset();

		//Reset counters
		m_cycleCount = 0;
		m_cyclesDelta = 0;
		m_audioSamplesWritten = 0;
		m_scanline = 0;
		m_cyclesToNextScanline = SMS_Z80_CYCLES_PER_SCANLINE;
		m_cyclesToNextPSGStep = SMS_Z80_CYCLES_PER_PSG_STEP;
	}

	u32 MasterSystem::StepDelta(double deltaTime)
	{
		//Can only step full Z80 instructions, so keep track of over/under Z80 cycles
		u64 numDACCycles = ion::maths::Round(deltaTime * SMS_PSG_OUTPUT_SAMPLE_RATE);
		u64 numz80CyclesPerDAC = SMS_Z80_CYCLES_PER_SECOND_NTSC / SMS_PSG_OUTPUT_SAMPLE_RATE;
		
		u32 totalZ80Cycles = 0;

		for (int i = 0; i < numDACCycles; i++)
		{
			m_cyclesDelta += numz80CyclesPerDAC;

			while (m_cyclesDelta > 0)
			{
				//Step Z80
				u32 z80CyclesExecuted = m_Z80->StepInstruction();

				totalZ80Cycles += z80CyclesExecuted;
				m_cycleCount += z80CyclesExecuted;
				m_cyclesDelta -= z80CyclesExecuted;
				m_cyclesToNextScanline -= z80CyclesExecuted;
				m_cyclesToNextPSGStep -= z80CyclesExecuted;

				//Process PSG
				while (m_cyclesToNextPSGStep <= 0)
				{
					m_PSG->Step();
					m_cyclesToNextPSGStep += SMS_Z80_CYCLES_PER_PSG_STEP;
				}

				//Process scanline rendering
				while (m_cyclesToNextScanline <= 0)
				{
					//Begin scanline (sets VINT if 0)
					m_VDP->BeginScanline(m_scanline);

					//TODO: VDP should interrupt via bus
					if (m_VDP->PeekStatus() & cpu::vdp::VDP_STATUS_VBLANK)
					{
						m_Z80->TriggerInterrupt(cpu::z80::Z80_INTERRUPT_IFF1);
					}

					m_VDP->DrawLine(&m_frameBuffers[m_frameBufferIdx][m_scanline * cpu::vdp::VDP_SCREEN_WIDTH], m_scanline);
					m_scanline++;

					if (m_scanline == cpu::vdp::VDP_SCANLINES_NTSC)
					{
						//End of video frame, swap framebuffers and reset scanline
						m_scanline = 0;
						m_frameBufferIdx = ((m_frameBufferIdx + 1) % SMS_EMU_NUM_FRAMEBUFFERS);
					}

					m_cyclesToNextScanline += SMS_Z80_CYCLES_PER_SCANLINE;
				}
			}

			//Process DAC
			m_audioBuffer.push_back(m_PSG->GetOutputSample());
			m_audioSamplesWritten++;

			//Push audio buffer if full
			if (m_audioBuffer.size() == SMS_PSG_OUTPUT_BUFFER_SIZE_SAMPLES)
			{
				if (m_audioBufferCallback)
					m_audioBufferCallback(m_audioBuffer);

				m_audioBuffer.clear();
			}
		}

		return totalZ80Cycles;
	}

	void MasterSystem::SetButtonState(peripherals::Joypad::PadIndex joypad, peripherals::Joypad::Button button, bool state)
	{
		m_joypad->SetButtonState(joypad, button, state);
	}

	const std::vector<u32>& MasterSystem::GetFramebuffer() const
	{
		return m_frameBuffers[ion::maths::WrapRange(m_frameBufferIdx - 1, 0, SMS_EMU_NUM_FRAMEBUFFERS)];
	}

	void MasterSystem::SetAudioCallback(OnAudioBufferFilled const& callback)
	{
		m_audioBufferCallback = callback;
	}

	const debug::SDSCConsole& MasterSystem::GetConsole() const
	{
		return *m_console;
	}

	const cpu::z80::Registers& MasterSystem::GetRegistersZ80() const
	{
		return m_Z80->GetRegisters();
	}

	const cpu::vdp::Registers& MasterSystem::GetRegistersVDP() const
	{
		return m_VDP->GetRegisters();
	}

	const cpu::psg::Registers& MasterSystem::GetRegistersPSG() const
	{
		return m_PSG->GetRegisters();
	}

	memory::Storage& MasterSystem::GetRAM()
	{
		return *m_ram;
	}

	memory::Storage& MasterSystem::GetVRAM()
	{
		return *m_vram;
	}

	memory::Mapper& MasterSystem::GetROM()
	{
		return *m_rom;
	}

	void MasterSystem::GetPCHistory(std::vector<cpu::z80::Registers>& history) const
	{
		return m_Z80->GetPCHistory(history);
	}

	u64 MasterSystem::GetZ80CyclesExecuted() const
	{
		return m_cycleCount;
	}

	u64 MasterSystem::GetAudioSamplesWritten() const
	{
		return m_audioSamplesWritten;
	}
}