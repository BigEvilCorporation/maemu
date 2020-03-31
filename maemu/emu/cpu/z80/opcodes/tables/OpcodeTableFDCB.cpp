#include "OpcodeTableFDCB.h"
#include "OpcodeTimings.h"

//All opcode handlers
#include "../bitwise.h"
#include "../nop.h"

namespace emu
{
	namespace cpu
	{
		namespace z80
		{
			const Opcode OpcodeTableFDCB[Z80_MAX_OPCODE_TABLE_SIZE] =
			{
				{ 0x00, 1, timing::RLC_dIY_r8,	&opcodes::RLC_dIY_r8,	"RLC", "(IY+#)->B" },
				{ 0x01, 1, timing::RLC_dIY_r8,	&opcodes::RLC_dIY_r8,	"RLC", "(IY+#)->C" },
				{ 0x02, 1, timing::RLC_dIY_r8,	&opcodes::RLC_dIY_r8,	"RLC", "(IY+#)->D" },
				{ 0x03, 1, timing::RLC_dIY_r8,	&opcodes::RLC_dIY_r8,	"RLC", "(IY+#)->E" },
				{ 0x04, 1, timing::RLC_dIY_r8,	&opcodes::RLC_dIY_r8,	"RLC", "(IY+#)->H" },
				{ 0x05, 1, timing::RLC_dIY_r8,	&opcodes::RLC_dIY_r8,	"RLC", "(IY+#)->L" },
				{ 0x06, 1, timing::RLC_dIY,		&opcodes::RLC_dIY,		"RLC", "(IY+#)" },
				{ 0x07, 1, timing::RLC_dIY_r8,	&opcodes::RLC_dIY_r8,	"RLC", "(IY+#)->A" },
				{ 0x08, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x09, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x0A, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x0B, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x0C, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x0D, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x0E, 1, timing::RRC_dIY,		&opcodes::RRC_dIY,		"RRC", "(IY+#)" },
				{ 0x0F, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },

				{ 0x10, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x11, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x12, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x13, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x14, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x15, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x16, 1, timing::RL_dIY,		&opcodes::RL_dIY,		"RL", "(IY+#)" },
				{ 0x17, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x18, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x19, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x1A, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x1B, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x1C, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x1D, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x1E, 1, timing::RR_dIY,		&opcodes::RR_dIY,		"RR", "(IY+#)" },
				{ 0x1F, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },

				{ 0x20, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x21, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x22, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x23, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x24, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x25, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x26, 1, timing::SLA_dIY,		opcodes::SLA_dIY,		"SLA", "(IY+#)" },
				{ 0x27, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x28, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x29, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x2A, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x2B, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x2C, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x2D, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x2E, 1, timing::SRA_dIY,		&opcodes::SRA_dIY,		"SRA", "(IY+#)" },
				{ 0x2F, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },

				{ 0x30, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x31, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x32, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x33, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x34, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x35, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x36, 1, timing::SLL_dIY,		&opcodes::SLL_dIY,		"SRL", "(IY+#)" },
				{ 0x37, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x38, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x39, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x3A, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x3B, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x3C, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x3D, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x3E, 1, timing::SRL_dIY,		&opcodes::SRL_dIY,		"SRL", "(IY+#)" },
				{ 0x3F, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },

				{ 0x40, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x41, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x42, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x43, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x44, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x45, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x46, 1, timing::BIT_b_dIY,	 opcodes::BIT_b_dIY,	"BIT", "0, (IY+#)" },
				{ 0x47, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x48, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x49, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x4A, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x4B, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x4C, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x4D, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x4E, 1, timing::BIT_b_dIY,	 opcodes::BIT_b_dIY,	"BIT", "1, (IY+#)" },
				{ 0x4F, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },

				{ 0x50, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x51, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x52, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x53, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x54, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x55, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x56, 1, timing::BIT_b_dIY,	 opcodes::BIT_b_dIY,	"BIT", "2, (IY+#)" },
				{ 0x57, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x58, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x59, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x5A, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x5B, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x5C, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x5D, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x5E, 1, timing::BIT_b_dIY,	 opcodes::BIT_b_dIY,	"BIT", "3, (IY+#)" },
				{ 0x5F, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },

				{ 0x60, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x61, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x62, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x63, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x64, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x65, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x66, 1, timing::BIT_b_dIY,	 opcodes::BIT_b_dIY,	"BIT", "4, (IY+#)" },
				{ 0x67, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x68, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x69, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x6A, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x6B, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x6C, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x6D, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x6E, 1, timing::BIT_b_dIY,	 opcodes::BIT_b_dIY,	"BIT", "5, (IY+#)" },
				{ 0x6F, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },

				{ 0x70, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x71, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x72, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x73, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x74, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x75, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x76, 1, timing::BIT_b_dIY,	 opcodes::BIT_b_dIY,	"BIT", "6, (IY+#)" },
				{ 0x77, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x78, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x79, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x7A, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x7B, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x7C, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x7D, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x7E, 1, timing::BIT_b_dIY,	 opcodes::BIT_b_dIY,	"BIT", "7, (IY+#)" },
				{ 0x7F, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },

				{ 0x80, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x81, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x82, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x83, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x84, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x85, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x86, 1, timing::RES_b_dIY,	 opcodes::RES_b_dIY,	"RES", "0, (IY+#)" },
				{ 0x87, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x88, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x89, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x8A, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x8B, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x8C, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x8D, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x8E, 1, timing::RES_b_dIY,	 opcodes::RES_b_dIY,	"RES", "1, (IY+#)" },
				{ 0x8F, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },

				{ 0x90, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x91, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x92, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x93, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x94, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x95, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x96, 1, timing::RES_b_dIY,	 opcodes::RES_b_dIY,	"RES", "2, (IY+#)" },
				{ 0x97, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x98, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x99, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x9A, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x9B, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x9C, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x9D, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0x9E, 1, timing::RES_b_dIY,	 opcodes::RES_b_dIY,	"RES", "3, (IY+#)" },
				{ 0x9F, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },

				{ 0xA0, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xA1, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xA2, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xA3, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xA4, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xA5, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xA6, 1, timing::RES_b_dIY,	 opcodes::RES_b_dIY,	"RES", "4, (IY+#)" },
				{ 0xA7, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xA8, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xA9, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xAA, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xAB, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xAC, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xAD, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xAE, 1, timing::RES_b_dIY,	 opcodes::RES_b_dIY,	"RES", "5, (IY+#)" },
				{ 0xAF, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },

				{ 0xB0, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xB1, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xB2, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xB3, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xB4, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xB5, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xB6, 1, timing::RES_b_dIY,	 opcodes::RES_b_dIY,	"RES", "6, (IY+#)" },
				{ 0xB7, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xB8, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xB9, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xBA, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xBB, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xBC, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xBD, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xBE, 1, timing::RES_b_dIY,	 opcodes::RES_b_dIY,	"RES", "7, (IY+#)" },
				{ 0xBF, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },

				{ 0xC0, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xC1, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xC2, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xC3, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xC4, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xC5, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xC6, 1, timing::SET_b_dIY,	 opcodes::SET_b_dIY,	"SET", "0, (IY+#)" },
				{ 0xC7, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xC8, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xC9, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xCA, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xCB, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xCC, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xCD, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xCE, 1, timing::SET_b_dIY,	 opcodes::SET_b_dIY,	"SET", "1, (IY+#)" },
				{ 0xCF, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },

				{ 0xD0, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xD1, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xD2, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xD3, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xD4, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xD5, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xD6, 1, timing::SET_b_dIY,	 opcodes::SET_b_dIY,	"SET", "2, (IY+#)" },
				{ 0xD7, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xD8, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xD9, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xDA, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xDB, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xDC, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xDD, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xDE, 1, timing::SET_b_dIY,	 opcodes::SET_b_dIY,	"SET", "3, (IY+#)" },
				{ 0xDF, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },

				{ 0xE0, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xE1, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xE2, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xE3, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xE4, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xE5, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xE6, 1, timing::SET_b_dIY,	 opcodes::SET_b_dIY,	"SET", "4, (IY+#)" },
				{ 0xE7, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xE8, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xE9, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xEA, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xEB, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xEC, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xED, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xEE, 1, timing::SET_b_dIY,	 opcodes::SET_b_dIY,	"SET", "5, (IY+#)" },
				{ 0xEF, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },

				{ 0xF0, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xF1, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xF2, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xF3, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xF4, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xF5, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xF6, 1, timing::SET_b_dIY,	 opcodes::SET_b_dIY,	"SET", "6, (IY+#)" },
				{ 0xF7, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xF8, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xF9, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xFA, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xFB, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xFC, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xFD, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
				{ 0xFE, 1, timing::SET_b_dIY,	 opcodes::SET_b_dIY,	"SET", "7, (IY+#)" },
				{ 0xFF, 0, timing::NOP,			&opcodes::Unknown,		"UNKNOWN", "" },
			};
		}
	}
}
