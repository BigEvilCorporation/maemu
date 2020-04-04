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
				static const int REGISTER_DECODE_INCDEC_16_REG_SHIFT = 0x4;

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// OPERATION TEMPLATES
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//Increment 8-bit
				template <LoadFunc8 LOAD_8_T, StoreFunc8 STORE_8_T>
				static u16 INC_8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Load value
					u8 value = LOAD_8_T(opcode, params, regs, bus);
					u8 prev = value;

					//Increment value
					value++;

					//Store value
					STORE_8_T(opcode, params, regs, bus, value);

					//Set flags
					ComputeFlagS(value, regs.main.f);
					ComputeFlagZ(value, regs.main.f);
					ComputeFlagH(prev, value, regs.main.f);
					ComputeFlagV(prev, value, regs.main.f);
					SetFlag(FLAG_N, false, regs.main.f);

					return opcode.cycles;
				}

				//Decrement 8-bit
				template <LoadFunc8 LOAD_8_T, StoreFunc8 STORE_8_T>
				static u16 DEC_8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Load value
					u8 value = LOAD_8_T(opcode, params, regs, bus);
					u8 prev = value;

					//Decrement value
					value--;

					//Store value
					STORE_8_T(opcode, params, regs, bus, value);

					//Set flags
					ComputeFlagH(prev, value, regs.main.f);
					ComputeFlagV(prev, value, regs.main.f);
					ComputeFlagZ(value, regs.main.f);
					ComputeFlagS(value, regs.main.f);
					SetFlag(FLAG_N, true, regs.main.f);

					return opcode.cycles;
				}

				//Increment 16-bit
				template <LoadFunc16 LOAD_16_T, StoreFunc16 STORE_16_T>
				static u16 INC_16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Load, increment, store
					STORE_16_T(opcode, params, regs, bus, LOAD_16_T(opcode, params, regs, bus) + 1);

					return opcode.cycles;
				}

				//Decrement 16-bit
				template <LoadFunc16 LOAD_16_T, StoreFunc16 STORE_16_T>
				static u16 DEC_16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Load, decrement, store
					STORE_16_T(opcode, params, regs, bus, LOAD_16_T(opcode, params, regs, bus) - 1);

					return opcode.cycles;
				}

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// INCREMENT/DECREMENT OPERATIONS
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//Increment 8-bit register
				static auto INC_r8 = INC_8<LD_Fetch_DST_r8, LD_Store_DST_r8>;

				//Increment value at address in (HL)
				static auto INC_dHL = INC_8<LD_Fetch_dHL, LD_Store_dHL>;

				//Increment value at address in (IX+offset)
				static auto INC_dIX = INC_8<LD_Fetch_dIXoff, LD_Store_dIXoff>;

				//Increment value at address in (IY+offset)
				static auto INC_dIY = INC_8<LD_Fetch_dIYoff, LD_Store_dIYoff>;

				//Increment IXH/IXL
				static auto INC_IXHL = INC_8<LD_Fetch_DST_rIXHL, LD_Store_rIXHL>;

				//Increment IYH/IYL
				static auto INC_IYHL = INC_8<LD_Fetch_DST_rIYHL, LD_Store_rIYHL>;

				//Decrement 8-bit register
				static auto DEC_r8 = DEC_8<LD_Fetch_DST_r8, LD_Store_DST_r8>;

				//Decrement value at address in (HL)
				static auto DEC_dHL = DEC_8<LD_Fetch_dHL, LD_Store_dHL>;

				//Decrement value at address in (IX+offset)
				static auto DEC_dIX = DEC_8<LD_Fetch_dIXoff, LD_Store_dIXoff>;

				//Decrement value at address in (IY+offset)
				static auto DEC_dIY = DEC_8<LD_Fetch_dIYoff, LD_Store_dIYoff>;

				//Decrement IXH/IXL
				static auto DEC_IXHL = DEC_8<LD_Fetch_DST_rIXHL, LD_Store_rIXHL>;

				//Decrement IYH/IYL
				static auto DEC_IYHL = DEC_8<LD_Fetch_DST_rIYHL, LD_Store_rIYHL>;

				//Increment 16-bit register
				static auto INC_r16 = INC_16<LD_Fetch_DST_r16, LD_Store_r16>;

				//Increment IX
				static auto INC_IX = INC_16<LD_Fetch_rIX, LD_Store_rIX>;

				//Increment IY
				static auto INC_IY = INC_16<LD_Fetch_rIY, LD_Store_rIY>;

				//Decrement 16-bit register
				static auto DEC_r16 = DEC_16<LD_Fetch_DST_r16, LD_Store_r16>;

				//Decrement IX
				static auto DEC_IX = DEC_16<LD_Fetch_rIX, LD_Store_rIX>;

				//Decrement IY
				static auto DEC_IY = DEC_16<LD_Fetch_rIY, LD_Store_rIY>;
			}
		}
	}
}