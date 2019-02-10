#pragma once

#include "opcodes/OpcodeTable.h"
#include "opcodes/OpcodeTableDD.h"

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
					u16 address;
					u8 opcodeIdx;
					const Opcode* opcode;
					OpcodeParams params;
				};

				void Disassemble(const std::vector<u8>& rom, u16 size, std::vector<Instruction>& disassembly);
				std::string ToText(const Instruction& instruction);
				std::string ToText(const std::vector<Instruction>& disassembly);
			}
		}
	}
}