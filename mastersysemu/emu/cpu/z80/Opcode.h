#pragma once

#include "Constants.h"
#include "../Registers.h"
#include "../Flags.h"
#include "../../../Bus.h"

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
		}
	}
}