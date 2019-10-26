#pragma once

#include "Opcode.h"
#include "../../memory/MemoryController.h"

#include <string>
#include <vector>

namespace emu
{
	namespace cpu
	{
		namespace z80
		{
			namespace disassembler
			{
				struct Instruction
				{
					u32 address;
					u16 prefix;
					u8 opcodeIdx;
					const Opcode* opcode;
					OpcodeParams params;
				};

				void Disassemble(const std::vector<u8>& rom, u32 size, std::vector<Instruction>& disassembly);
				void Disassemble(memory::Controller& memoryController, u32 address, int numInstructions, std::vector<Instruction>& disassembly);
				std::string ToText(const Instruction& instruction);
				std::string ToText(const std::vector<Instruction>& disassembly);
			}
		}
	}
}