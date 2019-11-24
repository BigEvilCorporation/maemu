#pragma once

#include "Constants.h"
#include "cpu/z80/Z80.h"
#include "cpu/z80/Bus.h"
#include "cpu/z80/Registers.h"
#include "cpu/z80/Disassembler.h"
#include "cpu/vdp/VDP.h"
#include "cpu/vdp/Bus.h"
#include "cpu/vdp/Registers.h"
#include "cpu/psg/PSG.h"
#include "cpu/psg/Registers.h"
#include "memory/Mapper.h"
#include "memory/MemoryController.h"
#include "memory/Storage.h"
#include "ports/PortController.h"
#include "peripherals/Joypad.h"
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
		void StepFrame();
		void StepScanline();
		void StepCycles(u32 cycles);
		void StepInstruction();

		//Rendering
		const std::vector<u32>& GetFramebuffer() const;

		//Audio
		void ConsumeAudioBuffer(std::vector<cpu::psg::SampleFormat>& buffer, int numChannels);

		//Input
		void SetButtonState(peripherals::Joypad::PadIndex joypad, peripherals::Joypad::Button button, bool state);

		//Debugging
		void Disassemble(std::vector<cpu::z80::disassembler::Instruction>& disassembly);
		void Disassemble(std::vector<cpu::z80::disassembler::Instruction>& disassembly, u16 address, int numInstructions);
		void GetPCHistory(std::vector<cpu::z80::Registers>& history) const;
		const debug::SDSCConsole& GetConsole() const;
		const cpu::z80::Registers& GetRegistersZ80() const;
		const cpu::vdp::Registers& GetRegistersVDP() const;
		const cpu::psg::Registers& GetRegistersPSG() const;
		memory::Storage& GetRAM();
		memory::Mapper& GetROM();
		memory::Storage& GetVRAM();

	private:
		void BuildSystem();
		void ProcessAudioVideo(u32 cycles);

		//Processors
		cpu::z80::Z80* m_Z80;
		cpu::vdp::VDP* m_VDP;
		cpu::psg::PSG* m_PSG;

		//Memory/peripheral bus
		cpu::z80::Bus* m_busZ80;
		cpu::vdp::Bus* m_busVDP;

		//Memory
		memory::Controller* m_memoryControllerZ80;
		memory::Controller* m_memoryControllerVRAM;
		memory::Controller* m_memoryControllerCRAM;
		memory::Mapper* m_rom;
		memory::Storage* m_ram;
		memory::Storage* m_vram;
		memory::Storage* m_cram;
		u32 m_romSize;

		//Ports
		ports::Controller* m_portController;

		//Audio
		cpu::psg::SampleFormat* m_audioBuffer;
		u32 m_audioOutputPtr;

		//Peripherals
		peripherals::Joypad* m_joypad;
		debug::SDSCConsole* m_console;

		//Timing
		u32 m_cycleCount;
		int m_cyclesToNextScanline;
		int m_cyclesToNextPSGStep;
		int m_cyclesToNextDAC;
		u16 m_scanline;

		//Rendering
		std::vector<u32> m_frameBuffer;
	};
}