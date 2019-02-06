#pragma once

#include <string>

#include "Constants.h"

#include "cpu/z80/Core.h"
#include "cpu/z80/Registers.h"
#include "memory/MemoryController.h"
#include "memory/Storage.h"
#include "ports/PortController.h"
#include "debug/SDSCConsole.h"

namespace emu
{
	class MasterSystem
	{
	public:
		MasterSystem();

		//Initialisation
		bool LoadROM(const std::string& filename);
		void Reset();

		//Processing
		void Update(float deltaTime);

		//Debugging
		const debug::SDSCConsole& GetConsole() const;
		const cpu::z80::Registers& GetRegisters() const;
		memory::Storage& GetRAM();
		memory::Storage& GetROM();

	private:
		void BuildSystem();

		//Processors
		cpu::z80::Core* m_Z80;

		//Memory/peripheral bus
		Bus* m_bus;

		//Memory
		memory::Controller* m_memoryController;
		memory::Storage* m_rom;
		memory::Storage* m_ram;

		//Ports
		ports::Controller* m_portController;

		//Debug
		debug::SDSCConsole* m_console;
	};
}