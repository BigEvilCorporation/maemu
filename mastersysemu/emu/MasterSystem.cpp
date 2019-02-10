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
		//Create memory controller and storage arenas
		m_memoryController = new memory::Controller();
		m_rom = new memory::Storage(ADDR_ROM_START, ADDR_ROM_END, *m_memoryController);
		m_ram = new memory::Storage(ADDR_RAM_START, ADDR_RAM_END, *m_memoryController);

		//Create port controller
		m_portController = new ports::Controller();

		//Create the Z80 bus
		m_bus = new cpu::z80::Bus(*m_memoryController, *m_portController);

		//Create the CPU
		m_Z80 = new cpu::z80::Core(*m_bus);

		//Create peripherals
		m_console = new debug::SDSCConsole(*m_portController);
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

		//Clear memory
	}

	void MasterSystem::Update(float deltaTime)
	{
		//Tick CPU
		m_Z80->Step();
	}

	const debug::SDSCConsole& MasterSystem::GetConsole() const
	{
		return *m_console;
	}

	const cpu::z80::Registers& MasterSystem::GetRegisters() const
	{
		return m_Z80->GetRegisters();
	}

	memory::Storage& MasterSystem::GetRAM()
	{
		return *m_ram;
	}

	memory::Storage& MasterSystem::GetROM()
	{
		return *m_rom;
	}
}