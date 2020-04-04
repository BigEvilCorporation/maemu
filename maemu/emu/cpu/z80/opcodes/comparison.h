#pragma once

#include "../Opcode.h"
#include "load.h"

namespace emu
{
	namespace cpu
	{
		namespace z80
		{
			namespace opcodes
			{
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// OPERATION TEMPLATES
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//Compare with A
				template <LoadFunc8 LOAD_8_T>
				static u16 CP_A(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Load value
					u8 value = LOAD_8_T(opcode, params, regs, bus);

					//Compare value with A
					u16 result = (regs.main.a - value);

					//Set flags
					ComputeFlags_ArithmeticSUB(regs.main.a, value, result, regs.main.f);

					return opcode.cycles;
				}

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// COMPARISON OPERATIONS
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//Compare A with 8-bit literal
				static auto CP_A_n8 = CP_A<LD_Fetch_n8>;

				//Compare A with 8-bit register
				static auto CP_A_r8 = CP_A<LD_Fetch_r8>;

				//Compare A with value at address in (HL)
				static auto CP_A_dHL = CP_A<LD_Fetch_dHL>;

				//Compare A with value at address in (IX+offset)
				static auto CP_A_dIX = CP_A<LD_Fetch_dIXoff>;

				//Compare A with value at address in (IY+offset)
				static auto CP_A_dIY = CP_A<LD_Fetch_dIYoff>;

				//Compare A with IXH/IXL
				static auto CP_A_IXHL = CP_A<LD_Fetch_rIXHL>;

				//Compare A with IYH/IYL
				static auto CP_A_IYHL = CP_A<LD_Fetch_rIYHL>;

				//Compare A with value at address in (HL), then increment HL and decrement BC
				static u16 CPI(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Read value at address in (HL)
					u8 value = bus.memoryController.ReadMemory(regs.main.hl);

					//Compare A with value
					u16 diff = (regs.main.a - value);

					//Increment HL, decrement BC
					regs.main.hl++;
					regs.main.bc--;

					//Set flags
					ComputeFlagZ(diff, regs.main.f);
					ComputeFlagS(diff, regs.main.f);
					SetFlagP((regs.main.bc != 0) ? 1 : 0, regs.main.f);
					SetFlagH((((regs.main.a & 0xF) - (value & 0xF)) < 0) ? 1 : 0, regs.main.f);
					SetFlagN(1, regs.main.f);

					return opcode.cycles;
				}

				//Compare A with value at address in (HL), then increment HL and decrement BC while BC!=0 and A!=(HL)
				static u16 CPIR(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					do
					{
						CPI(opcode, params, regs, bus);

					} while (regs.main.bc != 0 && !CheckFlagZ(regs.main.f));

					return opcode.cycles;
				}

				//Compare A with value at address in (HL), then decrement HL and BC
				static u16 CPD(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Read value at address in (HL)
					u8 value = bus.memoryController.ReadMemory(regs.main.hl);

					//Compare A with value
					u16 diff = (regs.main.a - value);

					//Decrement HL and BC
					regs.main.hl--;
					regs.main.bc--;

					//Set flags
					ComputeFlagZ(diff, regs.main.f);
					ComputeFlagS(diff, regs.main.f);
					SetFlagP((regs.main.bc != 0) ? 1 : 0, regs.main.f);
					SetFlagH((((regs.main.a & 0xF) - (value & 0xF)) < 0) ? 1 : 0, regs.main.f);
					SetFlagN(1, regs.main.f);

					return opcode.cycles;
				}

				//Compare A with value at address in (HL), then decrement HL and BC while BC!=0 and A!=(HL)
				static u16 CPDR(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					do
					{
						CPD(opcode, params, regs, bus);

					} while (regs.main.bc != 0 && !CheckFlagZ(regs.main.f));

					return opcode.cycles;
				}
			}
		}
	}
}