#include "OpcodeTableDD.h"

//Re-redirect tables
#include "OpcodeTableCB.h"
#include "OpcodeTableED.h"
#include "OpcodeTableFD.h"
#include "OpcodeTableDDCB.h"
#include "OpcodeTableFDCB.h"

//Re-redirect prefix handlers
#include "../prefix_cb.h"
#include "../prefix_ed.h"
#include "../prefix_fd.h"

//All opcode handlers
#include "../arithmetic.h"
#include "../bitwise.h"
#include "../comparison.h"
#include "../exchange.h"
#include "../incdec.h"
#include "../jump.h"
#include "../load.h"
#include "../nop.h"
#include "../stack.h"

namespace emu
{
	namespace cpu
	{
		namespace z80
		{
			const Opcode OpcodeTableDD[Z80_MAX_OPCODE_TABLE_SIZE] =
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
				{ 0x23, 0, &opcodes::INC_IX,  "INC", "IX" },
				{ 0x24, 0, &opcodes::INC_IXHL, "INC", "IXH" },
				{ 0x25, 0, &opcodes::DEC_IXHL, "DEC", "IXH" },
				{ 0x26, 1, opcodes::LD_IXHL_n8, "LD", "IXH, #" },
				{ 0x27, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x28, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x29, 0, &opcodes::ADD_IX_r16, "ADD", "IX, IX" },
				{ 0x2A, 2, &opcodes::LD_IX_dn16, "LD", "IX, (##)" },
				{ 0x2B, 0, &opcodes::DEC_IX,  "DEC", "IX" },
				{ 0x2C, 0, &opcodes::INC_IXHL, "INC", "IXL" },
				{ 0x2D, 0, &opcodes::DEC_IXHL, "DEC", "IXL" },
				{ 0x2E, 1, opcodes::LD_IXHL_n8, "LD", "IXL, #" },
				{ 0x2F, 0, &opcodes::Unknown, "UNKNOWN", "" },

				{ 0x30, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x31, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x32, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x33, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x34, 1, &opcodes::INC_dIX, "INC", "(IX+#)" },
				{ 0x35, 1, &opcodes::DEC_dIX, "DEC", "(IX+#)" },
				{ 0x36, 2, &opcodes::LD_dIX_n8, "LD", "(IX+#), #" },
				{ 0x37, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x38, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x39, 0, &opcodes::ADD_IX_r16, "ADD", "IX, SP" },
				{ 0x3A, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x3B, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x3C, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x3D, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x3E, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x3F, 0, &opcodes::Unknown, "UNKNOWN", "" },
				
				{ 0x40, 0, opcodes::LD_r8_r8,	"LD", "B, B" },
				{ 0x41, 0, opcodes::LD_r8_r8,	"LD", "B, C" },
				{ 0x42, 0, opcodes::LD_r8_r8,	"LD", "B, D" },
				{ 0x43, 0, opcodes::LD_r8_r8,	"LD", "B, E" },
				{ 0x44, 0, &opcodes::LD_r8_IXHL, "LD", "B, IXH" },
				{ 0x45, 0, &opcodes::LD_r8_IXHL, "LD", "B, IXL" },
				{ 0x46, 1, &opcodes::LD_r8_dIX, "LD", "B, (IX+#)" },
				{ 0x47, 0, opcodes::LD_r8_r8,	"LD", "B, A" },
				{ 0x48, 0, opcodes::LD_r8_r8,	"LD", "C, B" },
				{ 0x49, 0, opcodes::LD_r8_r8,	"LD", "C, C" },
				{ 0x4A, 0, opcodes::LD_r8_r8,	"LD", "C, D" },
				{ 0x4B, 0, opcodes::LD_r8_r8,	"LD", "C, E" },
				{ 0x4C, 0, &opcodes::LD_r8_IXHL, "LD", "C, IXH" },
				{ 0x4D, 0, &opcodes::LD_r8_IXHL, "LD", "C, IXL" },
				{ 0x4E, 1, &opcodes::LD_r8_dIX, "LD", "C, (IX+#)" },
				{ 0x4F, 0, opcodes::LD_r8_r8,	"LD", "C, A" },

				{ 0x50, 0, opcodes::LD_r8_r8,	"LD", "D, B" },
				{ 0x51, 0, opcodes::LD_r8_r8,	"LD", "D, C" },
				{ 0x52, 0, opcodes::LD_r8_r8,	"LD", "D, D" },
				{ 0x53, 0, opcodes::LD_r8_r8,	"LD", "D, E" },
				{ 0x54, 0, &opcodes::LD_r8_IXHL, "LD", "D, IXH" },
				{ 0x55, 0, &opcodes::LD_r8_IXHL, "LD", "D, IXL" },
				{ 0x56, 1, &opcodes::LD_r8_dIX, "LD", "D, (IX+#)" },
				{ 0x57, 0, opcodes::LD_r8_r8,	"LD", "D, A" },
				{ 0x58, 0, opcodes::LD_r8_r8,	"LD", "E, B" },
				{ 0x59, 0, opcodes::LD_r8_r8,	"LD", "E, C" },
				{ 0x5A, 0, opcodes::LD_r8_r8,	"LD", "E, D" },
				{ 0x5B, 0, opcodes::LD_r8_r8,	"LD", "E, E" },
				{ 0x5C, 0, &opcodes::LD_r8_IXHL, "LD", "E, IXH" },
				{ 0x5D, 0, &opcodes::LD_r8_IXHL, "LD", "E, IXL" },
				{ 0x5E, 1, &opcodes::LD_r8_dIX, "LD", "E, (IX+#)" },
				{ 0x5F, 0, opcodes::LD_r8_r8,	"LD", "E, A" },

				{ 0x60, 0, &opcodes::LD_r8_IXHL, "LD", "IXH, B" },
				{ 0x61, 0, &opcodes::LD_r8_IXHL, "LD", "IXH, C" },
				{ 0x62, 0, &opcodes::LD_r8_IXHL, "LD", "IXH, D" },
				{ 0x63, 0, &opcodes::LD_r8_IXHL, "LD", "IXH, E" },
				{ 0x64, 0, &opcodes::LD_r8_IXHL, "LD", "IXH, IXH" },
				{ 0x65, 0, &opcodes::LD_r8_IXHL, "LD", "IXH, IXL" },
				{ 0x66, 1, &opcodes::LD_r8_dIX, "LD", "H, (IX+#)" },
				{ 0x67, 0, &opcodes::LD_r8_IXHL, "LD", "IXH, A" },
				{ 0x68, 0, &opcodes::LD_r8_IXHL, "LD", "IXL, B" },
				{ 0x69, 0, &opcodes::LD_r8_IXHL, "LD", "IXL, C" },
				{ 0x6A, 0, &opcodes::LD_r8_IXHL, "LD", "IXL, D" },
				{ 0x6B, 0, &opcodes::LD_r8_IXHL, "LD", "IXL, E" },
				{ 0x6C, 0, &opcodes::LD_r8_IXHL, "LD", "IXL, IXH" },
				{ 0x6D, 0, &opcodes::LD_r8_IXHL, "LD", "IXL, IXL" },
				{ 0x6E, 1, &opcodes::LD_r8_dIX, "LD", "L, (IX+#)" },
				{ 0x6F, 0, &opcodes::LD_r8_IXHL, "LD", "IXL, A" },

				{ 0x70, 1, &opcodes::LD_dIX_r8, "LD", "(IX+#), B" },
				{ 0x71, 1, &opcodes::LD_dIX_r8, "LD", "(IX+#), C" },
				{ 0x72, 1, &opcodes::LD_dIX_r8, "LD", "(IX+#), D" },
				{ 0x73, 1, &opcodes::LD_dIX_r8, "LD", "(IX+#), E" },
				{ 0x74, 1, &opcodes::LD_dIX_r8, "LD", "(IX+#), H" },
				{ 0x75, 1, &opcodes::LD_dIX_r8, "LD", "(IX+#), L" },
				{ 0x76, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x77, 1, &opcodes::LD_dIX_r8, "LD", "(IX+#), A" },
				{ 0x78, 0, opcodes::LD_r8_r8,	"LD", "A, B" },
				{ 0x79, 0, opcodes::LD_r8_r8,	"LD", "A, C" },
				{ 0x7A, 0, opcodes::LD_r8_r8,	"LD", "A, D" },
				{ 0x7B, 0, opcodes::LD_r8_r8,	"LD", "A, E" },
				{ 0x7C, 0, &opcodes::LD_r8_IXHL, "LD", "A, IXH" },
				{ 0x7D, 0, &opcodes::LD_r8_IXHL, "LD", "A, IXL" },
				{ 0x7E, 1, &opcodes::LD_r8_dIX, "LD", "A, (IX+#)" },
				{ 0x7F, 0, opcodes::LD_r8_r8,	"LD", "A, A" },

				{ 0x80, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x81, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x82, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x83, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x84, 0, &opcodes::ADD_A_IXHL, "ADD", "A, IXH" },
				{ 0x85, 0, &opcodes::ADD_A_IXHL, "ADD", "A, IXL" },
				{ 0x86, 1, &opcodes::ADD_A_dIX, "ADD", "A, (IX+#)" },
				{ 0x87, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x88, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x89, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x8A, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x8B, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x8C, 0, &opcodes::ADC_A_IXHL, "ADC", "A, IXH" },
				{ 0x8D, 0, &opcodes::ADC_A_IXHL, "ADC", "A, IXL" },
				{ 0x8E, 1, &opcodes::ADC_A_dIX, "ADC", "A, (IX+#)" },
				{ 0x8F, 0, &opcodes::Unknown, "UNKNOWN", "" },

				{ 0x90, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x91, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x92, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x93, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x94, 0, &opcodes::SUB_A_IXHL, "SUB", "A, IXH" },
				{ 0x95, 0, &opcodes::SUB_A_IXHL, "SUB", "A, IXL" },
				{ 0x96, 1, &opcodes::SUB_A_dIX, "SUB", "A, (IX+#)" },
				{ 0x97, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x98, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x99, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x9A, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x9B, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x9C, 0, &opcodes::SBC_A_IXHL, "SBC", "A, IXH" },
				{ 0x9D, 0, &opcodes::SBC_A_IXHL, "SBC", "A, IXL" },
				{ 0x9E, 1, &opcodes::SBC_A_dIX, "SBC", "A, (IX+#)" },
				{ 0x9F, 0, &opcodes::Unknown, "UNKNOWN", "" },

				{ 0xA0, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xA1, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xA2, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xA3, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xA4, 0, &opcodes::AND_A_IXHL, "AND", "A, IXH" },
				{ 0xA5, 0, &opcodes::AND_A_IXHL, "AND", "A, IXY" },
				{ 0xA6, 1, &opcodes::AND_A_dIX,  "AND", "A, (IX+#)" },
				{ 0xA7, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xA8, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xA9, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xAA, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xAB, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xAC, 0, &opcodes::XOR_A_IXHL, "XOR", "A, IXH" },
				{ 0xAD, 0, &opcodes::XOR_A_IXHL, "XOR", "A, IXY" },
				{ 0xAE, 1, &opcodes::XOR_A_dIX,  "XOR", "A, (IX+#)" },
				{ 0xAF, 0, &opcodes::Unknown, "UNKNOWN", "" },

				{ 0xB0, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xB1, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xB2, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xB3, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xB4, 0, &opcodes::OR_A_IXHL, "OR", "A, IXH" },
				{ 0xB5, 0, &opcodes::OR_A_IXHL, "OR", "A, IXY" },
				{ 0xB6, 1, &opcodes::OR_A_dIX,  "OR", "A, (IX+#)" },
				{ 0xB7, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xB8, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xB9, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xBA, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xBB, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xBC, 0, &opcodes::CP_A_IXHL, "CP", "A, IXH" },
				{ 0xBD, 0, &opcodes::CP_A_IXHL, "CP", "A, IXL" },
				{ 0xBE, 1, &opcodes::CP_A_dIX, "CP", "A, (IX+#)" },
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
				{ 0xCB, 1, &opcodes::Prefix_CB,	"", "" },
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
				{ 0xE1, 0, &opcodes::POP_IX,  "POP", "IX" },
				{ 0xE2, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xE3, 0, &opcodes::EX_dSP_IX, "EX", "(SP), IX" },
				{ 0xE4, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xE5, 0, &opcodes::PUSH_IX, "PUSH", "IX" },
				{ 0xE6, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xE7, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xE8, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xE9, 0, &opcodes::JP_IX,   "JP", "(IX)" },
				{ 0xEA, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xEB, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xEC, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xED, 1, &opcodes::Prefix_ED,	"", "" },
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
				{ 0xFD, 1, &opcodes::Prefix_FD,	"", "" },
				{ 0xFE, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xFF, 0, &opcodes::Unknown, "UNKNOWN", "" },
			};
		}
	}
}
