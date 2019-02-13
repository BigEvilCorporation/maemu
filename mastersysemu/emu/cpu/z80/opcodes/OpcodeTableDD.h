#pragma once

#include "Opcode.h"

//All opcode handlers
#include "opcodes/prefix.h"
#include "opcodes/stack.h"
#include "opcodes/load.h"
#include "opcodes/nop.h"

namespace emu
{
	namespace cpu
	{
		namespace z80
		{
			static const Opcode OpcodeTableDD[] =
			{
				{ 0x00, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x01, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x02, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x03, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x04, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x05, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x06, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x07, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x08, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x09, 0, &opcodes::ADD_IX_r16, "ADD", "IX, BC" },
				{ 0x0A, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x0B, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x0C, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x0D, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x0E, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x0F, 0, &opcodes::Unknown, "UNKNOWN", "" },

				{ 0x10, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x11, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x12, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x13, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x14, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x15, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x16, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x17, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x18, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x19, 0, &opcodes::ADD_IX_r16, "ADD", "IX, DE" },
				{ 0x1A, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x1B, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x1C, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x1D, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x1E, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x1F, 0, &opcodes::Unknown, "UNKNOWN", "" },

				{ 0x20, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x21, 2, &opcodes::LD_IX_n16, "LD", "IX, ##" },
				{ 0x22, 2, &opcodes::LD_n16_IX, "LD", "##, IX" },
				{ 0x23, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x24, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x25, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x26, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x27, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x28, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x29, 0, &opcodes::ADD_IX_r16, "ADD", "IX, IX" },
				{ 0x2A, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x2B, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x2C, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x2D, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x2E, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x2F, 0, &opcodes::Unknown, "UNKNOWN", "" },

				{ 0x30, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x31, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x32, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x33, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x34, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x35, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x36, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x37, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x38, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x39, 0, &opcodes::ADD_IX_r16, "ADD", "IX, SP" },
				{ 0x3A, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x3B, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x3C, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x3D, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x3E, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x3F, 0, &opcodes::Unknown, "UNKNOWN", "" },
				
				{ 0x40, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x41, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x42, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x43, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x44, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x45, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x46, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x47, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x48, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x49, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x4A, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x4B, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x4C, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x4D, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x4E, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x4F, 0, &opcodes::Unknown, "UNKNOWN", "" },

				{ 0x50, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x51, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x52, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x53, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x54, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x55, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x56, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x57, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x58, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x59, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x5A, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x5B, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x5C, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x5D, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x5E, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x5F, 0, &opcodes::Unknown, "UNKNOWN", "" },

				{ 0x60, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x61, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x62, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x63, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x64, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x65, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x66, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x67, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x68, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x69, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x6A, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x6B, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x6C, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x6D, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x6E, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x6F, 0, &opcodes::Unknown, "UNKNOWN", "" },

				{ 0x70, 1, &opcodes::LD_dIX_r8, "LD", "(IX), B" },
				{ 0x71, 1, &opcodes::LD_dIX_r8, "LD", "(IX), C" },
				{ 0x72, 1, &opcodes::LD_dIX_r8, "LD", "(IX), D" },
				{ 0x73, 1, &opcodes::LD_dIX_r8, "LD", "(IX), E" },
				{ 0x74, 1, &opcodes::LD_dIX_r8, "LD", "(IX), H" },
				{ 0x75, 1, &opcodes::LD_dIX_r8, "LD", "(IX), L" },
				{ 0x76, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x77, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x78, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x79, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x7A, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x7B, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x7C, 0, &opcodes::LD_r8_IX, "LD", "A, IXH" },
				{ 0x7D, 0, &opcodes::LD_r8_IX, "LD", "A, IXL" },
				{ 0x7E, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x7F, 0, &opcodes::Unknown, "UNKNOWN", "" },

				{ 0x80, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x81, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x82, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x83, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x84, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x85, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x86, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x87, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x88, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x89, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x8A, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x8B, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x8C, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x8D, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x8E, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x8F, 0, &opcodes::Unknown, "UNKNOWN", "" },

				{ 0x90, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x91, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x92, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x93, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x94, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x95, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x96, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x97, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x98, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x99, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x9A, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x9B, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x9C, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x9D, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x9E, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x9F, 0, &opcodes::Unknown, "UNKNOWN", "" },

				{ 0xA0, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xA1, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xA2, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xA3, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xA4, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xA5, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xA6, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xA7, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xA8, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xA9, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xAA, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xAB, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xAC, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xAD, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xAE, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xAF, 0, &opcodes::Unknown, "UNKNOWN", "" },

				{ 0xB0, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xB1, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xB2, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xB3, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xB4, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xB5, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xB6, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xB7, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xB8, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xB9, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xBA, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xBB, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xBC, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xBD, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xBE, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xBF, 0, &opcodes::Unknown, "UNKNOWN", "" },

				{ 0xC0, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xC1, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xC2, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xC3, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xC4, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xC5, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xC6, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xC7, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xC8, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xC9, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xCA, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xCB, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xCC, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xCD, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xCE, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xCF, 0, &opcodes::Unknown, "UNKNOWN", "" },

				{ 0xD0, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xD1, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xD2, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xD3, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xD4, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xD5, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xD6, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xD7, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xD8, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xD9, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xDA, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xDB, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xDC, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xDD, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xDE, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xDF, 0, &opcodes::Unknown, "UNKNOWN", "" },

				{ 0xE0, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xE1, 1, &opcodes::POP_r16,  "POP", "IX" },
				{ 0xE2, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xE3, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xE4, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xE5, 1, &opcodes::PUSH_r16, "PUSH", "HL" },
				{ 0xE6, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xE7, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xE8, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xE9, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xEA, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xEB, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xEC, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xED, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xEE, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xEF, 0, &opcodes::Unknown, "UNKNOWN", "" },

				{ 0xF0, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xF1, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xF2, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xF3, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xF4, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xF5, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xF6, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xF7, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xF8, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xF9, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xFA, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xFB, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xFC, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xFD, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xFE, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xFF, 0, &opcodes::Unknown, "UNKNOWN", "" },
			};
		}
	}
}