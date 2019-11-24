#include "OpcodeTableED.h"

//Re-redirect tables
#include "OpcodeTableDD.h"
#include "OpcodeTableCB.h"
#include "OpcodeTableFD.h"
#include "OpcodeTableDDCB.h"
#include "OpcodeTableFDCB.h"

//Re-redirect prefix handlers
#include "../prefix_dd.h"
#include "../prefix_cb.h"
#include "../prefix_fd.h"

//All opcode handlers
#include "../arithmetic.h"
#include "../comparison.h"
#include "../interrupts.h"
#include "../ports.h"
#include "../load.h"
#include "../nop.h"

namespace emu
{
	namespace cpu
	{
		namespace z80
		{
			const Opcode OpcodeTableED[Z80_MAX_OPCODE_TABLE_SIZE] =
			{
				{ 0x00, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x01, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x02, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x03, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x04, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x05, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x06, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x07, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x08, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x09, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x0A, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x0B, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x0C, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x0D, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x0E, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x0F, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },

				{ 0x10, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x11, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x12, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x13, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x14, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x15, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x16, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x17, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x18, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x19, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x1A, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x1B, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x1C, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x1D, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x1E, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x1F, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },

				{ 0x20, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x21, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x22, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x23, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x24, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x25, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x26, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x27, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x28, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x29, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x2A, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x2B, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x2C, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x2D, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x2E, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x2F, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },

				{ 0x30, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x31, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x32, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x33, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x34, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x35, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x36, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x37, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x38, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x39, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x3A, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x3B, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x3C, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x3D, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x3E, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x3F, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },

				{ 0x40, 0, 8, &opcodes::IN_r8_C,		"IN", "B, (C)" },
				{ 0x41, 0, 8, &opcodes::OUT_C_r8,		"OUT", "(C), B" },
				{ 0x42, 0, 8, &opcodes::SBC_HL_r16,	"SBC", "HL, BC" },
				{ 0x43, 2, 8, opcodes::LD_n16_r16,	"LD", "(##), BC" },
				{ 0x44, 0, 8, &opcodes::NEG,			"NEG", "A" },
				{ 0x45, 0, 8, &opcodes::RETN,			"RETN", "" },
				{ 0x46, 0, 8, &opcodes::IM_0,			"IM", "0" },
				{ 0x47, 0, 8, opcodes::LD_I_A,			"LD", "I, A" },
				{ 0x48, 0, 8, &opcodes::IN_r8_C,		"IN", "C, (C)" },
				{ 0x49, 0, 8, &opcodes::OUT_C_r8,		"OUT", "(C), C" },
				{ 0x4A, 0, 8, &opcodes::ADC_HL_r16,	"ADC", "HL, BC" },
				{ 0x4B, 2, 8, opcodes::LD_r16_dn16,	"LD", "BC, (##)" },
				{ 0x4C, 0, 8, &opcodes::NEG,			"NEG", "A" },
				{ 0x4D, 0, 8, &opcodes::RETI,			"RETI", "" },
				{ 0x4E, 0, 8, &opcodes::IM_0,			"IM", "0" },
				{ 0x4F, 0, 8, opcodes::LD_R_A,			"LD", "R, A" },

				{ 0x50, 0, 8, &opcodes::IN_r8_C,		"IN", "D, (C)" },
				{ 0x51, 0, 8, &opcodes::OUT_C_r8,		"OUT", "(C), D" },
				{ 0x52, 0, 8, &opcodes::SBC_HL_r16,	"SBC", "HL, DE" },
				{ 0x53, 2, 8, opcodes::LD_n16_r16,	"LD", "(##), DE" },
				{ 0x54, 0, 8, &opcodes::NEG,			"NEG", "A" },
				{ 0x55, 0, 8, &opcodes::RETN,			"RETN", "" },
				{ 0x56, 0, 8, &opcodes::IM_1,			"IM", "1" },
				{ 0x57, 0, 8, opcodes::LD_A_I,			"LD", "A, I" },
				{ 0x58, 0, 8, &opcodes::IN_r8_C,		"IN", "E, (C)" },
				{ 0x59, 0, 8, &opcodes::OUT_C_r8,		"OUT", "(C), E" },
				{ 0x5A, 0, 8, &opcodes::ADC_HL_r16,	"ADC", "HL, DE" },
				{ 0x5B, 2, 8, opcodes::LD_r16_dn16,	"LD", "DE, (##)" },
				{ 0x5C, 0, 8, &opcodes::NEG,			"NEG", "A" },
				{ 0x5D, 0, 8, &opcodes::RETI,			"RETI", "" },
				{ 0x5E, 0, 8, &opcodes::IM_2,			"IM", "2" },
				{ 0x5F, 0, 8, opcodes::LD_A_R,			"LD", "A, R" },

				{ 0x60, 0, 8, &opcodes::IN_r8_C,		"IN", "H, (C)" },
				{ 0x61, 0, 8, &opcodes::OUT_C_r8,		"OUT", "(C), H" },
				{ 0x62, 0, 8, &opcodes::SBC_HL_r16,	"SBC", "HL, HL" },
				{ 0x63, 2, 8, opcodes::LD_n16_r16,	"LD", "(##), HL" },
				{ 0x64, 0, 8, &opcodes::NEG,			"NEG", "A" },
				{ 0x65, 0, 8, &opcodes::RETN,			"RETN", "" },
				{ 0x66, 0, 8, &opcodes::IM_0,			"IM", "0" },
				{ 0x67, 0, 8, &opcodes::RRD,			"RRD", "" },
				{ 0x68, 0, 8, &opcodes::IN_r8_C,		"IN", "L, (C)" },
				{ 0x69, 0, 8, &opcodes::OUT_C_r8,		"OUT", "(C), L" },
				{ 0x6A, 0, 8, &opcodes::ADC_HL_r16,	"ADC", "HL, HL" },
				{ 0x6B, 2, 8, opcodes::LD_r16_dn16,	"LD", "HL, (##)" },
				{ 0x6C, 0, 8, &opcodes::NEG,			"NEG", "A" },
				{ 0x6D, 0, 8, &opcodes::RETI,			"RETI", "" },
				{ 0x6E, 0, 8, &opcodes::IM_0,			"IM", "0" },
				{ 0x6F, 0, 8, &opcodes::RLD,			"RLD", "" },

				{ 0x70, 0, 8, &opcodes::IN_F_C,		"IN", "F, (C)" },
				{ 0x71, 0, 8, &opcodes::OUT_C_F,		"OUT", "(C), F" },
				{ 0x72, 0, 8, &opcodes::SBC_HL_r16,	"SBC", "HL, SP" },
				{ 0x73, 2, 8, opcodes::LD_n16_r16,	"LD", "(##), SP" },
				{ 0x74, 0, 8, &opcodes::NEG,			"NEG", "A" },
				{ 0x75, 0, 8, &opcodes::RETN,			"RETN", "" },
				{ 0x76, 0, 8, &opcodes::IM_1,			"IM", "1" },
				{ 0x77, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x78, 0, 8, &opcodes::IN_r8_C,		"IN", "A, (C)" },
				{ 0x79, 0, 8, &opcodes::OUT_C_r8,		"OUT", "(C), A" },
				{ 0x7A, 0, 8, &opcodes::ADC_HL_r16,	"ADC", "HL, SP" },
				{ 0x7B, 2, 8, opcodes::LD_r16_dn16,	"LD", "SP, (##)" },
				{ 0x7C, 0, 8, &opcodes::NEG,			"NEG", "A" },
				{ 0x7D, 0, 8, &opcodes::RETI,			"RETI", "" },
				{ 0x7E, 0, 8, &opcodes::IM_2,			"IM", "2" },
				{ 0x7F, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },

				{ 0x80, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x81, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x82, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x83, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x84, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x85, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x86, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x87, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x88, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x89, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x8A, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x8B, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x8C, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x8D, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x8E, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x8F, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },

				{ 0x90, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x91, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x92, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x93, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x94, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x95, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x96, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x97, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x98, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x99, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x9A, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x9B, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x9C, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x9D, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x9E, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x9F, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },

				{ 0xA0, 0, 8, &opcodes::LDI,			"LDI", "" },
				{ 0xA1, 0, 8, &opcodes::CPI,			"CPI", "" },
				{ 0xA2, 0, 8, &opcodes::INI,			"INI", "" },
				{ 0xA3, 0, 8, &opcodes::OTI,			"OTI", "" },
				{ 0xA4, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xA5, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xA6, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xA7, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xA8, 0, 8, &opcodes::LDD,			"LDD", "" },
				{ 0xA9, 0, 8, &opcodes::CPD,			"CPD", "" },
				{ 0xAA, 0, 8, &opcodes::IND,			"IND", "" },
				{ 0xAB, 0, 8, &opcodes::OTD,			"OTD", "" },
				{ 0xAC, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xAD, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xAE, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xAF, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },

				{ 0xB0, 0, 8, &opcodes::LDIR,			"LDIR", "" },
				{ 0xB1, 0, 8, &opcodes::CPIR,			"CPIR", "" },
				{ 0xB2, 0, 8, &opcodes::INIR,			"INIR", "" },
				{ 0xB3, 0, 8, &opcodes::OTIR,			"OTIR", "" },
				{ 0xB4, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xB5, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xB6, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xB7, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xB8, 0, 8, &opcodes::LDDR,			"LDDR", "" },
				{ 0xB9, 0, 8, &opcodes::CPDR,			"CPDR", "" },
				{ 0xBA, 0, 8, &opcodes::INDR,			"INDR", "" },
				{ 0xBB, 0, 8, &opcodes::OTDR,			"OTDR", "" },
				{ 0xBC, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xBD, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xBE, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xBF, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },

				{ 0xC0, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xC1, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xC2, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xC3, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xC4, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xC5, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xC6, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xC7, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xC8, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xC9, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xCA, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xCB, 1, 8, &opcodes::Prefix_CB,		"", "" },
				{ 0xCC, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xCD, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xCE, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xCF, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },

				{ 0xD0, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xD1, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xD2, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xD3, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xD4, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xD5, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xD6, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xD7, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xD8, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xD9, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xDA, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xDB, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xDC, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xDD, 1, 8, &opcodes::Prefix_DD,		"", "" },
				{ 0xDE, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xDF, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },

				{ 0xE0, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xE1, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xE2, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xE3, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xE4, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xE5, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xE6, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xE7, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xE8, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xE9, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xEA, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xEB, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xEC, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xED, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xEE, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xEF, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },

				{ 0xF0, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xF1, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xF2, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xF3, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xF4, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xF5, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xF6, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xF7, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xF8, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xF9, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xFA, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xFB, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xFC, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xFD, 1, 8, &opcodes::Prefix_FD,		"", "" },
				{ 0xFE, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xFF, 0, 8, &opcodes::Unknown,		"UNKNOWN", "" },
			};
		}
	}
}
