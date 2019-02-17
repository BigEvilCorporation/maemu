#ifndef PREFIX_ED_H
#define PREFIX_ED_H

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
				static u16 Prefix_ED(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//ED prefix
					regs.internal.prefix1 = 0xED;

					//Opcode in first param
					const Opcode& redirect = OpcodeTableED[params[0]];

					//Read remaining params
					OpcodeParams redirectParams;

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

#endif // PREFIX_ED_H