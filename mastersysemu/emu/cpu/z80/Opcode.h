#pragma once

#include "Constants.h"
#include "../Registers.h"
#include "../Flags.h"
#include "../Bus.h"

#include <string>
#include <functional>

#include <ion/core/Types.h>
#include <ion/core/containers/FixedArray.h>

namespace emu
{
	namespace cpu
	{
		namespace z80
		{
			//Opcode handler naming convention:
			//
			// r8  : 8-bit register
			// r16 : 16-bit register
			// n8  : 8-bit literal number
			// n16 : 16-bit literal number
			// d   : dereference register (read/write address)
			// b   : bit
			//
			// e.g.:
			//   LD_r8_n8  : Load 8-bit register from 8-bit literal
			//   LD_dHL_r8 : Load address at HL from 8-bit register

			struct Opcode;

			typedef ion::FixedArray<u8, Z80_MAX_OPCODE_PARAMS> OpcodeParams;
			typedef u16(*OpcodeHandler)(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus);

			struct Opcode
			{
				u8 opcode;
				u8 paramBytes;
				OpcodeHandler handler;
				std::string name;
				std::string paramsFormat;
			};

			enum RegisterDecode_8Bit
			{
				REGISTER_DECODE_8_MASK = 0x07,
				REGISTER_DECODE_8_A = 0x07,
				REGISTER_DECODE_8_B = 0x00,
				REGISTER_DECODE_8_C = 0x01,
				REGISTER_DECODE_8_D = 0x02,
				REGISTER_DECODE_8_E = 0x03,
				REGISTER_DECODE_8_H = 0x04,
				REGISTER_DECODE_8_L = 0x05
			};

			enum RegisterDecode_16Bit
			{
				REGISTER_DECODE_16_MASK = 0x03,
				REGISTER_DECODE_16_BC = 0x00,
				REGISTER_DECODE_16_DE = 0x01,
				REGISTER_DECODE_16_HL = 0x02,
				REGISTER_DECODE_16_SP = 0x03,
				REGISTER_DECODE_16_AF = 0x03,
			};
		}
	}
}