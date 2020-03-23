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
		m_audioOutputPtr = 0;

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

		//Initialise framebuffer
		//TODO: PAL vs. NTSC
		m_frameBuffer.resize(cpu::vdp::VDP_SCREEN_WIDTH * cpu::vdp::VDP_SCANLINES_PAL);

		//Alloc and initialise audio buffer
		m_audioBuffer = new cpu::psg::SampleFormat[SMS_PSG_OUTPUT_BUFFER_SIZE];
		ion::memory::MemSet(m_audioBuffer, 0, sizeof(cpu::psg::SampleFormat) * SMS_PSG_OUTPUT_BUFFER_SIZE);
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
		m_scanline = 0;
		m_cyclesToNextScanline = SMS_Z80_CYCLES_PER_SCANLINE;
		m_cyclesToNextPSGStep = SMS_Z80_CYCLES_PER_PSG_STEP;
		m_cyclesToNextDAC = SMS_Z80_CYCLES_PER_DAC_OUT;
	}

	void MasterSystem::StepDelta(float deltaTime)
	{
		m_cyclesDelta += ion::maths::Round((float)SMS_Z80_CYCLES_PER_SECOND_NTSC * deltaTime);
		m_cyclesDelta -= StepCycles(m_cyclesDelta);
	}

	void MasterSystem::StepFrame()
	{
		for(int i = 0; i < cpu::vdp::VDP_SCANLINES_NTSC; i++)
		{
			StepScanline();
		}
	}

	void MasterSystem::StepScanline()
	{
		//Step approx. one scanline's worth of CPU cycles
		StepCycles(SMS_Z80_CYCLES_PER_SCANLINE);
	}

	void MasterSystem::StepInstruction()
	{
		u32 cyclesExecuted = m_Z80->StepInstruction();
		m_cycleCount += cyclesExecuted;
		ProcessAudioVideo(cyclesExecuted);
	}

	u32 MasterSystem::StepCycles(u32 cycles)
	{
		int cyclesRemaining = (int)cycles;
		u32 totalCyclesExecuted = 0;

		while(cyclesRemaining > 0)
		{
			u32 cyclesExecuted = m_Z80->StepInstruction();

			m_cycleCount += cyclesExecuted;
			totalCyclesExecuted += cyclesExecuted;
			cyclesRemaining -= cyclesExecuted;

			ProcessAudioVideo(cyclesExecuted);
		}

		return totalCyclesExecuted;
	}

	void MasterSystem::ProcessAudioVideo(u32 cycles)
	{
		m_cyclesToNextScanline -= cycles;
		m_cyclesToNextPSGStep -= cycles;
		m_cyclesToNextDAC -= cycles;

		//Process PSG
		if (m_cyclesToNextPSGStep <= 0)
		{
			m_PSG->Step();
			m_cyclesToNextPSGStep += SMS_Z80_CYCLES_PER_PSG_STEP;
		}

		//Process scanline rendering
		if (m_cyclesToNextScanline <= 0)
		{
			//Begin scanline (sets VINT if 0)
			m_VDP->BeginScanline(m_scanline);

			//TODO: VDP should interrupt via bus
			if (m_VDP->PeekStatus() & cpu::vdp::VDP_STATUS_VBLANK)
			{
				m_Z80->TriggerInterrupt(cpu::z80::Z80_INTERRUPT_IFF1);
			}

			m_VDP->DrawLine(&m_frameBuffer[m_scanline * cpu::vdp::VDP_SCREEN_WIDTH], m_scanline);
			m_scanline++;

			if (m_scanline == cpu::vdp::VDP_SCANLINES_NTSC)
			{
				m_scanline = 0;
			}

			m_cyclesToNextScanline += SMS_Z80_CYCLES_PER_SCANLINE;
		}

		//Process DAC
		if (m_cyclesToNextDAC <= 0)
		{
			ion::debug::Assert(m_audioOutputPtr < SMS_PSG_OUTPUT_BUFFER_SIZE, "Out of audio buffer space, PSG running too fast");
			m_audioBuffer[m_audioOutputPtr++] = m_PSG->GetOutputSample();
			m_cyclesToNextDAC += SMS_Z80_CYCLES_PER_DAC_OUT;
		}
	}

	void MasterSystem::SetButtonState(peripherals::Joypad::PadIndex joypad, peripherals::Joypad::Button button, bool state)
	{
		m_joypad->SetButtonState(joypad, button, state);
	}

	const std::vector<u32>& MasterSystem::GetFramebuffer() const
	{
		return m_frameBuffer;
	}

	void MasterSystem::ConsumeAudioBuffer(std::vector<cpu::psg::SampleFormat>& buffer, int numChannels)
	{
		buffer.resize(m_audioOutputPtr * numChannels);

		for (int i = 0; i < m_audioOutputPtr; i++)
		{
			for (int j = 0; j < numChannels; j++)
			{
				buffer[(i * numChannels) + j] = m_audioBuffer[i];
			}
		}

		m_audioOutputPtr = 0;
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
}