#include "MasterSystem.h"

#include <ion/io/File.h>

namespace emu
{
	MasterSystem::MasterSystem()
	{
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
		m_rom = new memory::Storage(ADDR_ROM_START, ADDR_ROM_END, *m_memoryControllerZ80);
		m_ram = new memory::Storage(ADDR_RAM_START, ADDR_RAM_END, *m_memoryControllerZ80);
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

		//Create peripherals
		m_joypad = new peripherals::Joypad(*m_portController);
		m_console = new debug::SDSCConsole(*m_portController);

		//Initialise framebuffer
		//TODO: PAL vs. NTSC
		m_frameBuffer.resize(cpu::vdp::VDP_SCREEN_WIDTH * cpu::vdp::VDP_SCANLINES_PAL);
	}

	bool MasterSystem::LoadROM(const std::string& filename)
	{
		bool success = false;

		ion::io::File file(filename);

		if (file.IsOpen())
		{
			m_romSize = (u16)file.GetSize();

			//Load data
			u8* rom = new u8[m_romSize];

			if (file.Read(rom, m_romSize) == m_romSize)
			{
				//TODO: Pre-compile opcodes

				//Write to ROM space
				m_rom->Initialise(rom, (u16)m_romSize);
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

	void MasterSystem::Reset()
	{
		//Reset CPUs
		m_Z80->Reset();
		m_VDP->Reset();

		//TODO: Clear memory
	}

	void MasterSystem::Update(int steps)
	{
		//Tick CPU
		for (int i = 0; i < steps; i++)
		{
			m_Z80->Step();
		}

		//TODO: Interrupt callbacks
		int yoffset = ((cpu::vdp::VDP_SCANLINES_PAL - cpu::vdp::VDP_SCREEN_HEIGHT) / 2);

		for (int i = 0; i < cpu::vdp::VDP_SCREEN_HEIGHT; i++)
		{
			m_VDP->DrawLine(&m_frameBuffer[(yoffset + i) * cpu::vdp::VDP_SCREEN_WIDTH], i);
		}
	}

	const std::vector<u32>& MasterSystem::GetFramebuffer() const
	{
		return m_frameBuffer;
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

	memory::Storage& MasterSystem::GetRAM()
	{
		return *m_ram;
	}

	memory::Storage& MasterSystem::GetVRAM()
	{
		return *m_vram;
	}

	memory::Storage& MasterSystem::GetROM()
	{
		return *m_rom;
	}

	void MasterSystem::GetPCHistory(std::vector<u16>& history) const
	{
		return m_Z80->GetPCHistory(history);
	}
}