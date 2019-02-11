#pragma once

#include "Constants.h"
#include "cpu/z80/Z80.h"
#include "cpu/z80/Bus.h"
#include "cpu/z80/Registers.h"
#include "cpu/z80/Disassembler.h"
#include "cpu/vdp/VDP.h"
#include "cpu/vdp/Bus.h"
#include "cpu/vdp/Registers.h"
#include "memory/MemoryController.h"
#include "memory/Storage.h"
#include "ports/PortController.h"
#include "debug/SDSCConsole.h"

#include <string>
#include <Vector>

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

		//Rendering
		const std::vector<u32>& GetFramebuffer() const;

		//Debugging
		void Disassemble(std::vector<cpu::z80::disassembler::Instruction>& disassembly);
		const debug::SDSCConsole& GetConsole() const;
		const cpu::z80::Registers& GetRegisters() const;
		memory::Storage& GetRAM();
		memory::Storage& GetROM();

	private:
		void BuildSystem();

		//Processors
		cpu::z80::Z80* m_Z80;
		cpu::vdp::VDP* m_VDP;

		//Memory/peripheral bus
		cpu::z80::Bus* m_busZ80;
		cpu::vdp::Bus* m_busVDP;

		//Memory
		memory::Controller* m_memoryControllerZ80;
		memory::Controller* m_memoryControllerVRAM;
		memory::Controller* m_memoryControllerCRAM;
		memory::Storage* m_rom;
		memory::Storage* m_ram;
		memory::Storage* m_vram;
		memory::Storage* m_cram;
		u16 m_romSize;

		//Ports
		ports::Controller* m_portController;

		//Rendering
		std::vector<u32> m_frameBuffer;

		//Debug
		debug::SDSCConsole* m_console;
	};
}