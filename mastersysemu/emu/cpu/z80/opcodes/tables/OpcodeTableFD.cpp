#include "OpcodeTableFD.h"

//Re-redirect tables
#include "OpcodeTableDD.h"
#include "OpcodeTableED.h"
#include "OpcodeTableCB.h"
#include "OpcodeTableDDCB.h"
#include "OpcodeTableFDCB.h"

//Re-redirect prefix handlers
#include "../prefix_dd.h"
#include "../prefix_ed.h"
#include "../prefix_cb.h"

//All opcode handlers
#include "../arithmetic.h"
#include "../bitwise.h"
#include "../comparison.h"
#include "../exchange.h"
#include "../incdec.h"
#include "../jump.h"
#include "../load.h"
#include "../nop.h"
#include "../ports.h"
#include "../stack.h"

namespace emu
{
	namespace cpu
	{
		namespace z80
		{
			const Opcode OpcodeTableFD[Z80_MAX_OPCODE_TABLE_SIZE] =
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
				{ 0x09, 0, &opcodes::ADD_IY_r16, "ADD", "IY, BC" },
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
				{ 0x19, 0, &opcodes::ADD_IY_r16, "ADD", "IY, DE" },
				{ 0x1A, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x1B, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x1C, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x1D, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x1E, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x1F, 0, &opcodes::Unknown, "UNKNOWN", "" },

				{ 0x20, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x21, 2, &opcodes::LD_IY_n16, "LD", "IY, ##" },
				{ 0x22, 2, &opcodes::LD_n16_IY, "LD", "##, IY" },
				{ 0x23, 0, &opcodes::INC_IY,  "INC", "IY" },
				{ 0x24, 0, &opcodes::INC_IYHL, "INC", "IYH" },
				{ 0x25, 0, &opcodes::DEC_IYHL, "DEC", "IYH" },
				{ 0x26, 1, &opcodes::LD_IYH_n8, "LD", "IYH, #" },
				{ 0x27, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x28, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x29, 0, &opcodes::ADD_IY_r16, "ADD", "IY, IX" },
				{ 0x2A, 2, &opcodes::LD_IY_dn16, "LD", "IY, (##)" },
				{ 0x2B, 0, &opcodes::DEC_IY,  "DEC", "IY" },
				{ 0x2C, 0, &opcodes::INC_IYHL, "INC", "IYL" },
				{ 0x2D, 0, &opcodes::DEC_IYHL, "DEC", "IYL" },
				{ 0x2E, 1, &opcodes::LD_IYL_n8, "LD", "IYL, #" },
				{ 0x2F, 0, &opcodes::Unknown, "UNKNOWN", "" },

				{ 0x30, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x31, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x32, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x33, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x34, 1, &opcodes::INC_dIY, "INC", "(IY+#)" },
				{ 0x35, 1, &opcodes::DEC_dIY, "DEC", "(IY+#)" },
				{ 0x36, 2, &opcodes::LD_dIY_n8, "LD", "(IY+#), #" },
				{ 0x37, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x38, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x39, 0, &opcodes::ADD_IY_r16, "ADD", "IY, SP" },
				{ 0x3A, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x3B, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x3C, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x3D, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x3E, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x3F, 0, &opcodes::Unknown, "UNKNOWN", "" },
				
				{ 0x40, 0, &opcodes::LD_r8_r8,	"LD", "B, B" },
				{ 0x41, 0, &opcodes::LD_r8_r8,	"LD", "B, C" },
				{ 0x42, 0, &opcodes::LD_r8_r8,	"LD", "B, D" },
				{ 0x43, 0, &opcodes::LD_r8_r8,	"LD", "B, E" },
				{ 0x44, 0, &opcodes::LD_r8_IYHL, "LD", "B, IYH" },
				{ 0x45, 0, &opcodes::LD_r8_IYHL, "LD", "B, IYL" },
				{ 0x46, 1, &opcodes::LD_r8_dIY, "LD", "B, (IY+#)" },
				{ 0x47, 0, &opcodes::LD_r8_r8,	"LD", "B, A" },
				{ 0x48, 0, &opcodes::LD_r8_r8,	"LD", "C, B" },
				{ 0x49, 0, &opcodes::LD_r8_r8,	"LD", "C, C" },
				{ 0x4A, 0, &opcodes::LD_r8_r8,	"LD", "C, D" },
				{ 0x4B, 0, &opcodes::LD_r8_r8,	"LD", "C, E" },
				{ 0x4C, 0, &opcodes::LD_r8_IYHL, "LD", "C, IYH" },
				{ 0x4D, 0, &opcodes::LD_r8_IYHL, "LD", "C, IYL" },
				{ 0x4E, 1, &opcodes::LD_r8_dIY, "LD", "C, (IY+#)" },
				{ 0x4F, 0, &opcodes::LD_r8_r8,	"LD", "C, A" },

				{ 0x50, 0, &opcodes::LD_r8_r8,	"LD", "D, B" },
				{ 0x51, 0, &opcodes::LD_r8_r8,	"LD", "D, C" },
				{ 0x52, 0, &opcodes::LD_r8_r8,	"LD", "D, D" },
				{ 0x53, 0, &opcodes::LD_r8_r8,	"LD", "D, E" },
				{ 0x54, 0, &opcodes::LD_r8_IYHL, "LD", "D, IYH" },
				{ 0x55, 0, &opcodes::LD_r8_IYHL, "LD", "D, IYL" },
				{ 0x56, 1, &opcodes::LD_r8_dIY, "LD", "D, (IY+#)" },
				{ 0x57, 0, &opcodes::LD_r8_r8,	"LD", "D, A" },
				{ 0x58, 0, &opcodes::LD_r8_r8,	"LD", "E, B" },
				{ 0x59, 0, &opcodes::LD_r8_r8,	"LD", "E, C" },
				{ 0x5A, 0, &opcodes::LD_r8_r8,	"LD", "E, D" },
				{ 0x5B, 0, &opcodes::LD_r8_r8,	"LD", "E, E" },
				{ 0x5C, 0, &opcodes::LD_r8_IYHL, "LD", "E, IYH" },
				{ 0x5D, 0, &opcodes::LD_r8_IYHL, "LD", "E, IYL" },
				{ 0x5E, 1, &opcodes::LD_r8_dIY, "LD", "E, (IY+#)" },
				{ 0x5F, 0, &opcodes::LD_r8_r8,	"LD", "E, A" },

				{ 0x60, 0, &opcodes::LD_r8_IYHL, "LD", "IYH, B" },
				{ 0x61, 0, &opcodes::LD_r8_IYHL, "LD", "IYH, C" },
				{ 0x62, 0, &opcodes::LD_r8_IYHL, "LD", "IYH, D" },
				{ 0x63, 0, &opcodes::LD_r8_IYHL, "LD", "IYH, E" },
				{ 0x64, 0, &opcodes::LD_r8_IYHL, "LD", "IYH, IXH" },
				{ 0x65, 0, &opcodes::LD_r8_IYHL, "LD", "IYH, IXL" },
				{ 0x66, 1, &opcodes::LD_r8_dIY,  "LD", "H, (IY+#)" },
				{ 0x67, 0, &opcodes::LD_r8_IYHL, "LD", "IYH, A" },
				{ 0x68, 0, &opcodes::LD_r8_IYHL, "LD", "IYL, B" },
				{ 0x69, 0, &opcodes::LD_r8_IYHL, "LD", "IYL, C" },
				{ 0x6A, 0, &opcodes::LD_r8_IYHL, "LD", "IYL, D" },
				{ 0x6B, 0, &opcodes::LD_r8_IYHL, "LD", "IYL, E" },
				{ 0x6C, 0, &opcodes::LD_r8_IYHL, "LD", "IYL, IXH" },
				{ 0x6D, 0, &opcodes::LD_r8_IYHL, "LD", "IYL, IXL" },
				{ 0x6E, 1, &opcodes::LD_r8_dIY,  "LD", "L, (IY+#)" },
				{ 0x6F, 0, &opcodes::LD_r8_IYHL, "LD", "IYL, A" },

				{ 0x70, 1, &opcodes::LD_dIY_r8, "LD", "(IY+#), B" },
				{ 0x71, 1, &opcodes::LD_dIY_r8, "LD", "(IY+#), C" },
				{ 0x72, 1, &opcodes::LD_dIY_r8, "LD", "(IY+#), D" },
				{ 0x73, 1, &opcodes::LD_dIY_r8, "LD", "(IY+#), E" },
				{ 0x74, 1, &opcodes::LD_dIY_r8, "LD", "(IY+#), H" },
				{ 0x75, 1, &opcodes::LD_dIY_r8, "LD", "(IY+#), L" },
				{ 0x76, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x77, 1, &opcodes::LD_dIY_r8, "LD", "(IY+#), A" },
				{ 0x78, 0, &opcodes::LD_r8_r8,	"LD", "A, B" },
				{ 0x79, 0, &opcodes::LD_r8_r8,	"LD", "A, C" },
				{ 0x7A, 0, &opcodes::LD_r8_r8,	"LD", "A, D" },
				{ 0x7B, 0, &opcodes::LD_r8_r8,	"LD", "A, E" },
				{ 0x7C, 0, &opcodes::LD_r8_IYHL, "LD", "A, IYH" },
				{ 0x7D, 0, &opcodes::LD_r8_IYHL, "LD", "A, IYL" },
				{ 0x7E, 1, &opcodes::LD_r8_dIY, "LD", "A, (IY+#)" },
				{ 0x7F, 0, &opcodes::LD_r8_r8,	"LD", "A, A" },

				{ 0x80, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x81, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x82, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x83, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x84, 0, &opcodes::ADD_A_IYHL, "ADD", "A, IYH" },
				{ 0x85, 0, &opcodes::ADD_A_IYHL, "ADD", "A, IYL" },
				{ 0x86, 1, &opcodes::ADD_A_dIY, "ADD", "A, (IY+#)" },
				{ 0x87, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x88, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x89, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x8A, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x8B, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x8C, 0, &opcodes::ADC_A_IYHL, "ADC", "A, IYH" },
				{ 0x8D, 0, &opcodes::ADC_A_IYHL, "ADC", "A, IYL" },
				{ 0x8E, 1, &opcodes::ADC_A_dIY, "ADC", "A, (IY+#)" },
				{ 0x8F, 0, &opcodes::Unknown, "UNKNOWN", "" },

				{ 0x90, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x91, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x92, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x93, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x94, 0, &opcodes::SUB_A_IYHL, "SUB", "A, IYH" },
				{ 0x95, 0, &opcodes::SUB_A_IYHL, "SUB", "A, IYL" },
				{ 0x96, 1, &opcodes::SUB_A_dIY, "SUB", "A, (IY+#)" },
				{ 0x97, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x98, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x99, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x9A, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x9B, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0x9C, 0, &opcodes::SBC_A_IYHL, "SBC", "A, IYH" },
				{ 0x9D, 0, &opcodes::SBC_A_IYHL, "SBC", "A, IYL" },
				{ 0x9E, 1, &opcodes::SBC_A_dIY, "SBC", "A, (IY+#)" },
				{ 0x9F, 0, &opcodes::Unknown, "UNKNOWN", "" },

				{ 0xA0, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xA1, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xA2, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xA3, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xA4, 0, &opcodes::AND_A_IYHL, "AND", "A, IYH" },
				{ 0xA5, 0, &opcodes::AND_A_IYHL, "AND", "A, IYY" },
				{ 0xA6, 1, &opcodes::AND_A_dIY,  "AND", "A, (IY+#)" },
				{ 0xA7, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xA8, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xA9, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xAA, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xAB, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xAC, 0, &opcodes::XOR_A_IYHL, "XOR", "A, IYH" },
				{ 0xAD, 0, &opcodes::XOR_A_IYHL, "XOR", "A, IYY" },
				{ 0xAE, 1, &opcodes::XOR_A_dIY,  "XOR", "A, (IY+#)" },
				{ 0xAF, 0, &opcodes::Unknown, "UNKNOWN", "" },

				{ 0xB0, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xB1, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xB2, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xB3, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xB4, 0, &opcodes::OR_A_IYHL, "OR", "A, IYH" },
				{ 0xB5, 0, &opcodes::OR_A_IYHL, "OR", "A, IYY" },
				{ 0xB6, 1, &opcodes::OR_A_dIY,  "OR", "A, (IY+#)" },
				{ 0xB7, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xB8, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xB9, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xBA, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xBB, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xBC, 0, &opcodes::CP_A_IYHL, "CP", "A, IYH" },
				{ 0xBD, 0, &opcodes::CP_A_IYHL, "CP", "A, IYL" },
				{ 0xBE, 1, &opcodes::CP_A_dIY, "CP", "A, (IY+#)" },
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
				{ 0xDD, 1, &opcodes::Prefix_DD,	"", "" },
				{ 0xDE, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xDF, 0, &opcodes::Unknown, "UNKNOWN", "" },

				{ 0xE0, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xE1, 0, &opcodes::POP_IY,  "POP", "IY" },
				{ 0xE2, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xE3, 0, &opcodes::EX_dSP_IY, "EX", "(SP), IY" },
				{ 0xE4, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xE5, 0, &opcodes::PUSH_IY, "PUSH", "IY" },
				{ 0xE6, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xE7, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xE8, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xE9, 0, &opcodes::JP_IY,   "JP", "(IY)" },
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
				{ 0xFD, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xFE, 0, &opcodes::Unknown, "UNKNOWN", "" },
				{ 0xFF, 0, &opcodes::Unknown, "UNKNOWN", "" },
			};
		}
	}
}
