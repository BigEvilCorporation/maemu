#include "Disassembler.h"

#include <ion/core/utils/STL.h>

#include <sstream>

namespace emu
{
	namespace cpu
	{
		namespace z80
		{
			namespace disassembler
			{
				void Disassemble(const std::vector<u8>& rom, u16 size, std::vector<Instruction>& disassembly)
				{
					u16 address = 0;

					while (address < size)
					{
						Instruction instruction;
						instruction.address = address;

						//Get opcode idx
						instruction.opcodeIdx = rom[address++];

						//Get opcode
						instruction.opcode = &OpcodeTable[instruction.opcodeIdx];

						//Handle redirects
						if (instruction.opcode->handler == opcodes::Prefix_DD)
						{
							instruction.opcodeIdx = rom[address++];
							instruction.opcode = &OpcodeTableDD[instruction.opcodeIdx];
						}

						//Output params
						for (int i = 0; i < instruction.opcode->paramBytes; i++)
						{
							instruction.params[i] = rom[address++];
						}

						disassembly.push_back(instruction);
					}
				}

				std::string ToText(const Instruction& instruction)
				{
					std::stringstream text;
					text << SSTREAM_HEX4(instruction.address) << " " << instruction.opcode->name << " ";

					for (int i = 0; i < instruction.opcode->paramBytes; i++)
					{
						text << SSTREAM_HEX2(instruction.params[i]) << " ";
					}

					text << std::endl;
					return text.str();
				}

				std::string ToText(const std::vector<Instruction>& disassembly)
				{
					std::string text;

					for (int i = 0; i < disassembly.size(); i++)
					{
						text += ToText(disassembly[i]);
					}

					return text;
				}
			}
		}
	}
}