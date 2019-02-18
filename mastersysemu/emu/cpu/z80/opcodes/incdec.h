#pragma once

#include "../Opcode.h"

namespace emu
{
	namespace cpu
	{
		namespace z80
		{
			namespace opcodes
			{
				static const int REGISTER_DECODE_INCDEC_8_REG_SHIFT = 0x3;
				static const int REGISTER_DECODE_INCDEC_16_REG_SHIFT = 0x4;

				//Increment 8-bit register
				static u16 INC_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_INCDEC_8_REG_SHIFT);

					//Increment reg
					reg++;

					//Set flags
					ComputeFlagsZCS(reg, regs.main.f);

					return 0;
				}

				//Decrement 8-bit register
				static u16 DEC_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_INCDEC_8_REG_SHIFT);

					//Decrement reg
					reg--;

					//Set flags
					ComputeFlagsZCS(reg, regs.main.f);

					return 0;
				}

				//Increment 16-bit register
				static u16 INC_r16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u16& reg = DecodeReg16(regs, opcode.opcode, REGISTER_DECODE_INCDEC_16_REG_SHIFT);

					//Increment reg
					reg++;

					return 0;
				}

				//Decrement 16-bit register
				static u16 DEC_r16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u16& reg = DecodeReg16(regs, opcode.opcode, REGISTER_DECODE_INCDEC_16_REG_SHIFT);

					//Decrement reg
					reg--;

					return 0;
				}

				//Increment IX
				static u16 INC_IX(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Increment IX
					regs.ix++;

					return 0;
				}

				//Decrement IX
				static u16 DEC_IX(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Decrement IX
					regs.ix--;

					return 0;
				}

				//Increment IXH/IXL
				static u16 INC_IXHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8_IX(regs, opcode.opcode, REGISTER_DECODE_INCDEC_8_REG_SHIFT);

					//Increment reg
					reg++;

					return 0;
				}

				//Decrement IXH/IXL
				static u16 DEC_IXHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8_IX(regs, opcode.opcode, REGISTER_DECODE_INCDEC_8_REG_SHIFT);

					//Decrement reg
					reg--;

					return 0;
				}

				//Increment IY
				static u16 INC_IY(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Increment IY
					regs.iy++;

					return 0;
				}

				//Decrement IY
				static u16 DEC_IY(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Decrement IY
					regs.iy--;

					return 0;
				}

				//Increment IYH/IYL
				static u16 INC_IYHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8_IY(regs, opcode.opcode, REGISTER_DECODE_INCDEC_8_REG_SHIFT);

					//Increment reg
					reg++;

					return 0;
				}

				//Decrement IYH/IYL
				static u16 DEC_IYHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8_IY(regs, opcode.opcode, REGISTER_DECODE_INCDEC_8_REG_SHIFT);

					//Decrement reg
					reg--;

					return 0;
				}

				//Increment value at address in (HL)
				static u16 INC_dHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Read value
					u8 value = bus.memoryController.ReadMemory(regs.main.hl);

					//Increment and write
					value++;
					bus.memoryController.WriteMemory(regs.main.hl, value);

					//Set flags
					ComputeFlagsZCS(value, regs.main.f);

					return 0;
				}

				//Increment value at address in (IX+offset)
				static u16 INC_dIX(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get address + offset
					u16 address = regs.ix + params[0];

					//Read value
					u8 value = bus.memoryController.ReadMemory(address);

					//Increment and write
					value++;
					bus.memoryController.WriteMemory(address, value);

					//Set flags
					ComputeFlagsZCS(value, regs.main.f);

					return 0;
				}

				//Decrement value at address in (IX+offset)
				static u16 DEC_dIX(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get address + offset
					u16 address = regs.ix + params[0];

					//Read value
					u8 value = bus.memoryController.ReadMemory(address);

					//Decrement and write
					value--;
					bus.memoryController.WriteMemory(address, value);

					//Set flags
					ComputeFlagsZCS(value, regs.main.f);

					return 0;
				}

				//Increment value at address in (IY+offset)
				static u16 INC_dIY(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get address + offset
					u16 address = regs.iy + params[0];

					//Read value
					u8 value = bus.memoryController.ReadMemory(address);

					//Increment and write
					value++;
					bus.memoryController.WriteMemory(address, value);

					//Set flags
					ComputeFlagsZCS(value, regs.main.f);

					return 0;
				}

				//Decrement value at address in (IY+offset)
				static u16 DEC_dIY(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get address + offset
					u16 address = regs.iy + params[0];

					//Read value
					u8 value = bus.memoryController.ReadMemory(address);

					//Decrement and write
					value--;
					bus.memoryController.WriteMemory(address, value);

					//Set flags
					ComputeFlagsZCS(value, regs.main.f);

					return 0;
				}

				//Decrement value at address in (HL)
				static u16 DEC_dHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Read value
					u8 value = bus.memoryController.ReadMemory(regs.main.hl);

					//Decrement and write
					value--;
					bus.memoryController.WriteMemory(regs.main.hl, value);

					//Set flags
					ComputeFlagsZCS(value, regs.main.f);

					return 0;
				}
			}
		}
	}
}