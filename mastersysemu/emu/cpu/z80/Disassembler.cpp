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
				void HandleRedirect(u16& address, Instruction& instruction, const std::vector<u8>& rom)
				{
					u8 prefix = 0;

					do
					{
						prefix = 0;

						if (instruction.opcode->handler == opcodes::Prefix_CB)
						{
							prefix = 0xCB;
							instruction.prefix = (instruction.prefix << 8) | prefix;
							instruction.opcodeIdx = rom[address++];
							instruction.opcode = &OpcodeTableCB[instruction.opcodeIdx];
						}
						else if (instruction.opcode->handler == opcodes::Prefix_DD)
						{
							prefix = 0xDD;
							instruction.prefix = (instruction.prefix << 8) | prefix;
							instruction.opcodeIdx = rom[address++];
							instruction.opcode = &OpcodeTableDD[instruction.opcodeIdx];
						}
						else if (instruction.opcode->handler == opcodes::Prefix_ED)
						{
							prefix = 0xED;
							instruction.prefix = (instruction.prefix << 8) | prefix;
							instruction.opcodeIdx = rom[address++];
							instruction.opcode = &OpcodeTableED[instruction.opcodeIdx];
						}
						else if (instruction.opcode->handler == opcodes::Prefix_FD)
						{
							prefix = 0xFD;
							instruction.prefix = (instruction.prefix << 8) | prefix;
							instruction.opcodeIdx = rom[address++];
							instruction.opcode = &OpcodeTableFD[instruction.opcodeIdx];
						}

					} while (prefix != 0);
				}

				void Disassemble(const std::vector<u8>& rom, u16 size, std::vector<Instruction>& disassembly)
				{
					u16 address = 0;

					while (address < size)
					{
						Instruction instruction;
						instruction.address = address;
						instruction.prefix = 0;

						//Get opcode idx
						instruction.opcodeIdx = rom[address++];

						//Get opcode
						instruction.opcode = &OpcodeTable[instruction.opcodeIdx];

						//Handle redirects
						HandleRedirect(address, instruction, rom);

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
					text << SSTREAM_HEX4(instruction.address) << " ";

					if (instruction.prefix)
					{
						text << "[" << SSTREAM_HEX4(instruction.prefix) << "] ";
					}

					text << SSTREAM_HEX2(instruction.opcodeIdx) << " " << instruction.opcode->name << " ";

					int paramIdx = 0;
					const std::string& format = instruction.opcode->paramsFormat;
					for (int i = 0; i < format.size(); i++)
					{
						if (format[i] == '#')
						{
							//Constant param
							text << "$";

							if ((i + 1) < format.size() && format[i + 1] == '#')
							{
								//2-byte param, switch endianness
								text << SSTREAM_HEX2(instruction.params[paramIdx+1]);
								text << SSTREAM_HEX2(instruction.params[paramIdx]);
								i += 2;
							}
							else
							{
								//1-byte param
								text << SSTREAM_HEX2(instruction.params[paramIdx++]);
							}
						}
						else
						{
							text << instruction.opcode->paramsFormat[i];
						}
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