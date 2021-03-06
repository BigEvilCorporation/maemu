#ifndef PREFIX_CB_H
#define PREFIX_CB_H

#include "../Opcode.h"
#include <ion/core/memory/Memory.h>

namespace emu
{
	namespace cpu
	{
		namespace z80
		{
			namespace opcodes
			{
				static u16 Prefix_CB(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					const Opcode* opcodeTable = nullptr;

					bool paramBeforeOpcode = false;

					if (regs.internal.prefix1 == 0)
					{
						opcodeTable = OpcodeTableCB;
						regs.internal.prefix1 = 0xCB;
					}
					else if (regs.internal.prefix1 == 0xDD)
					{
						opcodeTable = OpcodeTableDDCB;
						regs.internal.prefix2 = 0xCB;

						//For DDCB table, param is first, opcode is second
						paramBeforeOpcode = true;
					}
					else if (regs.internal.prefix1 == 0xFD)
					{
						opcodeTable = OpcodeTableFDCB;
						regs.internal.prefix2 = 0xCB;

						//For FDCB table, param is first, opcode is second
						paramBeforeOpcode = true;
					}

					if (paramBeforeOpcode)
					{
						//Opcode is yet to come
						const Opcode& redirect = opcodeTable[bus.memoryController.ReadMemory(regs.pc++)];

						//Read remaining params
						OpcodeParams redirectParams;

#if defined DEBUG
						redirectParams.count = redirect.paramBytes;
#endif

						for (int i = 0; i < redirect.paramBytes; i++)
						{
							redirectParams[i] = params[0];
						}

						//Execute
						return redirect.handler(redirect, redirectParams, regs, bus);
					}
					else
					{
						//Opcode in first param
						const Opcode& redirect = opcodeTable[params[0]];

						//Read remaining params
						OpcodeParams redirectParams;

#if defined DEBUG
						redirectParams.count = redirect.paramBytes;
#endif

						for (int i = 0; i < redirect.paramBytes; i++)
						{
							redirectParams[i] = bus.memoryController.ReadMemory(regs.pc++);
						}

						//Execute
						return redirect.handler(redirect, redirectParams, regs, bus);
					}
				}
			}
		}
	}
}

#endif // PREFIX_CB_H