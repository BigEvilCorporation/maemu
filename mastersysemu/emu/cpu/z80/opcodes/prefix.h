#pragma once

#include "../Opcode.h"

//Redirect opcode tables
#include "OpcodeTableDD.h"
#include "OpcodeTableED.h"

#include <ion/core/memory/Memory.h>

namespace emu
{
	namespace cpu
	{
		namespace z80
		{
			namespace opcodes
			{
				static u16 Prefix_DD(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Opcode in first param
					const Opcode& redirect = OpcodeTableDD[params[0]];

					//Read remaining params
					OpcodeParams redirectParams;

					for (int i = 0; i < redirect.paramBytes; i++)
					{
						redirectParams[i] = bus.memoryController.ReadMemory(regs.pc++);
					}

					//Execute
					return redirect.handler(redirect, redirectParams, regs, bus);
				}

				static u16 Prefix_ED(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
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