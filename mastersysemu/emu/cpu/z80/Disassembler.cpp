#include "Disassembler.h"

#include "opcodes/tables/OpcodeTable.h"
#include "opcodes/tables/OpcodeTableCB.h"
#include "opcodes/tables/OpcodeTableDD.h"
#include "opcodes/tables/OpcodeTableED.h"
#include "opcodes/tables/OpcodeTableFD.h"
#include "opcodes/tables/OpcodeTableDDCB.h"
#include "opcodes/tables/OpcodeTableFDCB.h"

#include "opcodes/prefix_cb.h"
#include "opcodes/prefix_dd.h"
#include "opcodes/prefix_ed.h"
#include "opcodes/prefix_fd.h"

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
				bool HandleRedirect(u16& address, Instruction& instruction, const std::vector<u8>& rom)
				{
					u8 prefix = 0;
					bool paramFirst = false;

					do
					{
						prefix = 0;

						if (instruction.opcodeIdx == 0xCB)
						{
							if (instruction.prefix == 0xDD)
							{
								instruction.opcode = &OpcodeTableDDCB[instruction.opcodeIdx];
								paramFirst = true;
							}
							else if (instruction.prefix == 0xFD)
							{
								instruction.opcode = &OpcodeTableFDCB[instruction.opcodeIdx];
								paramFirst = true;
							}
							else
							{
								instruction.opcode = &OpcodeTableCB[instruction.opcodeIdx];
							}

							prefix = instruction.opcodeIdx;
							instruction.prefix = (instruction.prefix << 8) | prefix;
							instruction.opcodeIdx = rom[address++];
							
						}
						else if (instruction.opcodeIdx == 0xDD)
						{
							prefix = instruction.opcodeIdx;
							instruction.prefix = (instruction.prefix << 8) | prefix;
							instruction.opcodeIdx = rom[address++];
							instruction.opcode = &OpcodeTableDD[instruction.opcodeIdx];
						}
						else if (instruction.opcodeIdx == 0xED)
						{
							prefix = instruction.opcodeIdx;
							instruction.prefix = (instruction.prefix << 8) | prefix;
							instruction.opcodeIdx = rom[address++];
							instruction.opcode = &OpcodeTableED[instruction.opcodeIdx];
						}
						else if (instruction.opcodeIdx == 0xFD)
						{
							prefix = instruction.opcodeIdx;
							instruction.prefix = (instruction.prefix << 8) | prefix;
							instruction.opcodeIdx = rom[address++];
							instruction.opcode = &OpcodeTableFD[instruction.opcodeIdx];
						}

					} while (prefix != 0);

					return paramFirst;
				}

				bool HandleRedirect(u16& address, Instruction& instruction, memory::Controller& memoryController)
				{
					u8 prefix = 0;
					bool paramFirst = false;

					do
					{
						prefix = 0;

						if (instruction.opcodeIdx == 0xCB)
						{
							if (instruction.prefix == 0xDD)
							{
								instruction.opcode = &OpcodeTableDDCB[instruction.opcodeIdx];
								paramFirst = true;
							}
							else if (instruction.prefix == 0xFD)
							{
								instruction.opcode = &OpcodeTableFDCB[instruction.opcodeIdx];
								paramFirst = true;
							}
							else
							{
								instruction.opcode = &OpcodeTableCB[instruction.opcodeIdx];
							}

							prefix = instruction.opcodeIdx;
							instruction.prefix = (instruction.prefix << 8) | prefix;
							instruction.opcodeIdx = memoryController.ReadMemory(address++);
						}
						else if (instruction.opcodeIdx == 0xDD)
						{
							prefix = instruction.opcodeIdx;
							instruction.prefix = (instruction.prefix << 8) | prefix;
							instruction.opcodeIdx = memoryController.ReadMemory(address++);
							instruction.opcode = &OpcodeTableDD[instruction.opcodeIdx];
						}
						else if (instruction.opcodeIdx == 0xED)
						{
							prefix = instruction.opcodeIdx;
							instruction.prefix = (instruction.prefix << 8) | prefix;
							instruction.opcodeIdx = memoryController.ReadMemory(address++);
							instruction.opcode = &OpcodeTableED[instruction.opcodeIdx];
						}
						else if (instruction.opcodeIdx == 0xFD)
						{
							prefix = instruction.opcodeIdx;
							instruction.prefix = (instruction.prefix << 8) | prefix;
							instruction.opcodeIdx = memoryController.ReadMemory(address++);
							instruction.opcode = &OpcodeTableFD[instruction.opcodeIdx];
						}

					} while (prefix != 0);

					return paramFirst;
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
						if (HandleRedirect(address, instruction, rom))
						{
							//Param first, read opcode
							instruction.opcode = &OpcodeTable[rom[address++]];

							#if defined DEBUG
							instruction.params.count = instruction.opcode->paramBytes;
							#endif

							//Original opcode is actually first param
							instruction.params[0] = instruction.opcodeIdx;

							//Read remaining params
							for (int i = 0; i < instruction.opcode->paramBytes - 1; i++)
							{
								instruction.params[i] = rom[address++];
							}
						}
						else
						{
							//Opcode first
							#if defined DEBUG
							instruction.params.count = instruction.opcode->paramBytes;
							#endif

							//Read params
							for (int i = 0; i < instruction.opcode->paramBytes; i++)
							{
								instruction.params[i] = rom[address++];
							}
						}

						disassembly.push_back(instruction);
					}
				}

				void Disassemble(memory::Controller& memoryController, u16 address, int numInstructions, std::vector<Instruction>& disassembly)
				{
					for (int i = 0; i < numInstructions; i++)
					{
						Instruction instruction;
						instruction.address = address;
						instruction.prefix = 0;

						//Get opcode idx
						instruction.opcodeIdx = memoryController.ReadMemory(address++);

						//Get opcode
						instruction.opcode = &OpcodeTable[instruction.opcodeIdx];

						//Handle redirects
						if (HandleRedirect(address, instruction, memoryController))
						{
							//Param first, read opcode
							instruction.opcode = &OpcodeTable[memoryController.ReadMemory(address++)];

							#if defined DEBUG
							instruction.params.count = instruction.opcode->paramBytes;
							#endif

							//Original opcode is actually first param
							instruction.params[0] = instruction.opcodeIdx;

							//Read remaining params
							for (int i = 0; i < instruction.opcode->paramBytes - 1; i++)
							{
								instruction.params[i] = memoryController.ReadMemory(address++);
							}
						}
						else
						{
							//Opcode first
							#if defined DEBUG
							instruction.params.count = instruction.opcode->paramBytes;
							#endif

							//Read params
							for (int i = 0; i < instruction.opcode->paramBytes; i++)
							{
								instruction.params[i] = memoryController.ReadMemory(address++);
							}
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
								i++;
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