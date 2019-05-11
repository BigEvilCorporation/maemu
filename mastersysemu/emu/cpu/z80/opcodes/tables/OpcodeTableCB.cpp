#include "OpcodeTableCB.h"

//Re-redirect tables
#include "OpcodeTableDD.h"
#include "OpcodeTableED.h"
#include "OpcodeTableFD.h"

//Re-redirect prefix handlers
#include "../prefix_dd.h"
#include "../prefix_ed.h"
#include "../prefix_fd.h"

//All opcode handlers
#include "../bitwise.h"
#include "../ports.h"
#include "../load.h"
#include "../nop.h"

namespace emu
{
	namespace cpu
	{
		namespace z80
		{
			const Opcode OpcodeTableCB[Z80_MAX_OPCODE_TABLE_SIZE] =
			{
				{ 0x00, 0, &opcodes::RLC,			"RLC", "B" },
				{ 0x01, 0, &opcodes::RLC,			"RLC", "C" },
				{ 0x02, 0, &opcodes::RLC,			"RLC", "D" },
				{ 0x03, 0, &opcodes::RLC,			"RLC", "E" },
				{ 0x04, 0, &opcodes::RLC,			"RLC", "H" },
				{ 0x05, 0, &opcodes::RLC,			"RLC", "L" },
				{ 0x06, 0, &opcodes::RLC_dHL,		"RLC", "(HL)" },
				{ 0x07, 0, &opcodes::RLC,			"RLC", "A" },
				{ 0x08, 0, &opcodes::RRC,			"RRC", "B" },
				{ 0x09, 0, &opcodes::RRC,			"RRC", "C" },
				{ 0x0A, 0, &opcodes::RRC,			"RRC", "D" },
				{ 0x0B, 0, &opcodes::RRC,			"RRC", "E" },
				{ 0x0C, 0, &opcodes::RRC,			"RRC", "H" },
				{ 0x0D, 0, &opcodes::RRC,			"RRC", "L" },
				{ 0x0E, 0, &opcodes::RRC_dHL,		"RRC", "(HL)" },
				{ 0x0F, 0, &opcodes::RRC,			"RRC", "A" },

				{ 0x10, 0, &opcodes::RL_r8,			"RL", "B" },
				{ 0x11, 0, &opcodes::RL_r8,			"RL", "C" },
				{ 0x12, 0, &opcodes::RL_r8,			"RL", "D" },
				{ 0x13, 0, &opcodes::RL_r8,			"RL", "E" },
				{ 0x14, 0, &opcodes::RL_r8,			"RL", "H" },
				{ 0x15, 0, &opcodes::RL_r8,			"RL", "L" },
				{ 0x16, 0, &opcodes::RL_dHL,		"RL", "(HL)" },
				{ 0x17, 0, &opcodes::RL_r8,			"RL", "A" },
				{ 0x18, 0, &opcodes::RR_r8,			"RR", "B" },
				{ 0x19, 0, &opcodes::RR_r8,			"RR", "C" },
				{ 0x1A, 0, &opcodes::RR_r8,			"RR", "D" },
				{ 0x1B, 0, &opcodes::RR_r8,			"RR", "E" },
				{ 0x1C, 0, &opcodes::RR_r8,			"RR", "H" },
				{ 0x1D, 0, &opcodes::RR_r8,			"RR", "L" },
				{ 0x1E, 0, &opcodes::RR_dHL,		"RR", "(HL)" },
				{ 0x1F, 0, &opcodes::RR_r8,			"RR", "A" },

				{ 0x20, 0, &opcodes::SLA_r8,		"SLA", "B" },
				{ 0x21, 0, &opcodes::SLA_r8,		"SLA", "C" },
				{ 0x22, 0, &opcodes::SLA_r8,		"SLA", "D" },
				{ 0x23, 0, &opcodes::SLA_r8,		"SLA", "E" },
				{ 0x24, 0, &opcodes::SLA_r8,		"SLA", "H" },
				{ 0x25, 0, &opcodes::SLA_r8,		"SLA", "L" },
				{ 0x26, 0, &opcodes::SLA_dHL,		"SLA", "(HL)" },
				{ 0x27, 0, &opcodes::SLA_r8,		"SLA", "A" },
				{ 0x28, 0, &opcodes::SRA_r8,		"SRA", "B" },
				{ 0x29, 0, &opcodes::SRA_r8,		"SRA", "C" },
				{ 0x2A, 0, &opcodes::SRA_r8,		"SRA", "D" },
				{ 0x2B, 0, &opcodes::SRA_r8,		"SRA", "E" },
				{ 0x2C, 0, &opcodes::SRA_r8,		"SRA", "H" },
				{ 0x2D, 0, &opcodes::SRA_r8,		"SRA", "L" },
				{ 0x2E, 0, &opcodes::SRA_dHL,		"SRA", "(HL)" },
				{ 0x2F, 0, &opcodes::SRA_r8,		"SRA", "A" },

				{ 0x30, 0, &opcodes::SLL_r8,		"SRL", "B" },
				{ 0x31, 0, &opcodes::SLL_r8,		"SRL", "C" },
				{ 0x32, 0, &opcodes::SLL_r8,		"SRL", "D" },
				{ 0x33, 0, &opcodes::SLL_r8,		"SRL", "E" },
				{ 0x34, 0, &opcodes::SLL_r8,		"SRL", "H" },
				{ 0x35, 0, &opcodes::SLL_r8,		"SRL", "L" },
				{ 0x36, 0, &opcodes::SLL_dHL,		"SRL", "(HL)" },
				{ 0x37, 0, &opcodes::SLL_r8,		"SRL", "A" },
				{ 0x38, 0, &opcodes::SRL_r8,		"SRL", "B" },
				{ 0x39, 0, &opcodes::SRL_r8,		"SRL", "C" },
				{ 0x3A, 0, &opcodes::SRL_r8,		"SRL", "D" },
				{ 0x3B, 0, &opcodes::SRL_r8,		"SRL", "E" },
				{ 0x3C, 0, &opcodes::SRL_r8,		"SRL", "H" },
				{ 0x3D, 0, &opcodes::SRL_r8,		"SRL", "L" },
				{ 0x3E, 0, &opcodes::SRL_dHL,		"SRL", "(HL)" },
				{ 0x3F, 0, &opcodes::SRL_r8,		"SRL", "A" },
				
				{ 0x40, 0, opcodes::BIT_b_r8,		"BIT", "0, B" },
				{ 0x41, 0, opcodes::BIT_b_r8,		"BIT", "0, C" },
				{ 0x42, 0, opcodes::BIT_b_r8,		"BIT", "0, D" },
				{ 0x43, 0, opcodes::BIT_b_r8,		"BIT", "0, E" },
				{ 0x44, 0, opcodes::BIT_b_r8,		"BIT", "0, H" },
				{ 0x45, 0, opcodes::BIT_b_r8,		"BIT", "0, L" },
				{ 0x46, 0, opcodes::BIT_b_dHL,		"BIT", "0, (HL)" },
				{ 0x47, 0, opcodes::BIT_b_r8,		"BIT", "0, A" },
				{ 0x48, 0, opcodes::BIT_b_r8,		"BIT", "1, B" },
				{ 0x49, 0, opcodes::BIT_b_r8,		"BIT", "1, C" },
				{ 0x4A, 0, opcodes::BIT_b_r8,		"BIT", "1, D" },
				{ 0x4B, 0, opcodes::BIT_b_r8,		"BIT", "1, E" },
				{ 0x4C, 0, opcodes::BIT_b_r8,		"BIT", "1, H" },
				{ 0x4D, 0, opcodes::BIT_b_r8,		"BIT", "1, L" },
				{ 0x4E, 0, opcodes::BIT_b_dHL,		"BIT", "1, (HL)" },
				{ 0x4F, 0, opcodes::BIT_b_r8,		"BIT", "1, A" },

				{ 0x50, 0, opcodes::BIT_b_r8,		"BIT", "2, B" },
				{ 0x51, 0, opcodes::BIT_b_r8,		"BIT", "2, C" },
				{ 0x52, 0, opcodes::BIT_b_r8,		"BIT", "2, D" },
				{ 0x53, 0, opcodes::BIT_b_r8,		"BIT", "2, E" },
				{ 0x54, 0, opcodes::BIT_b_r8,		"BIT", "2, H" },
				{ 0x55, 0, opcodes::BIT_b_r8,		"BIT", "2, L" },
				{ 0x56, 0, opcodes::BIT_b_dHL,		"BIT", "2, (HL)" },
				{ 0x57, 0, opcodes::BIT_b_r8,		"BIT", "2, A" },
				{ 0x58, 0, opcodes::BIT_b_r8,		"BIT", "3, B" },
				{ 0x59, 0, opcodes::BIT_b_r8,		"BIT", "3, C" },
				{ 0x5A, 0, opcodes::BIT_b_r8,		"BIT", "3, D" },
				{ 0x5B, 0, opcodes::BIT_b_r8,		"BIT", "3, E" },
				{ 0x5C, 0, opcodes::BIT_b_r8,		"BIT", "3, H" },
				{ 0x5D, 0, opcodes::BIT_b_r8,		"BIT", "3, L" },
				{ 0x5E, 0, opcodes::BIT_b_dHL,		"BIT", "3, (HL)" },
				{ 0x5F, 0, opcodes::BIT_b_r8,		"BIT", "3, A" },

				{ 0x60, 0, opcodes::BIT_b_r8,		"BIT", "4, B" },
				{ 0x61, 0, opcodes::BIT_b_r8,		"BIT", "4, C" },
				{ 0x62, 0, opcodes::BIT_b_r8,		"BIT", "4, D" },
				{ 0x63, 0, opcodes::BIT_b_r8,		"BIT", "4, E" },
				{ 0x64, 0, opcodes::BIT_b_r8,		"BIT", "4, H" },
				{ 0x65, 0, opcodes::BIT_b_r8,		"BIT", "4, L" },
				{ 0x66, 0, opcodes::BIT_b_dHL,		"BIT", "4, (HL)" },
				{ 0x67, 0, opcodes::BIT_b_r8,		"BIT", "4, A" },
				{ 0x68, 0, opcodes::BIT_b_r8,		"BIT", "5, B" },
				{ 0x69, 0, opcodes::BIT_b_r8,		"BIT", "5, C" },
				{ 0x6A, 0, opcodes::BIT_b_r8,		"BIT", "5, D" },
				{ 0x6B, 0, opcodes::BIT_b_r8,		"BIT", "5, E" },
				{ 0x6C, 0, opcodes::BIT_b_r8,		"BIT", "5, H" },
				{ 0x6D, 0, opcodes::BIT_b_r8,		"BIT", "5, L" },
				{ 0x6E, 0, opcodes::BIT_b_dHL,		"BIT", "5, (HL)" },
				{ 0x6F, 0, opcodes::BIT_b_r8,		"BIT", "5, A" },

				{ 0x70, 0, opcodes::BIT_b_r8,		"BIT", "6, B" },
				{ 0x71, 0, opcodes::BIT_b_r8,		"BIT", "6, C" },
				{ 0x72, 0, opcodes::BIT_b_r8,		"BIT", "6, D" },
				{ 0x73, 0, opcodes::BIT_b_r8,		"BIT", "6, E" },
				{ 0x74, 0, opcodes::BIT_b_r8,		"BIT", "6, H" },
				{ 0x75, 0, opcodes::BIT_b_r8,		"BIT", "6, L" },
				{ 0x76, 0, opcodes::BIT_b_dHL,		"BIT", "6, (HL)" },
				{ 0x77, 0, opcodes::BIT_b_r8,		"BIT", "6, A" },
				{ 0x78, 0, opcodes::BIT_b_r8,		"BIT", "7, B" },
				{ 0x79, 0, opcodes::BIT_b_r8,		"BIT", "7, C" },
				{ 0x7A, 0, opcodes::BIT_b_r8,		"BIT", "7, D" },
				{ 0x7B, 0, opcodes::BIT_b_r8,		"BIT", "7, E" },
				{ 0x7C, 0, opcodes::BIT_b_r8,		"BIT", "7, H" },
				{ 0x7D, 0, opcodes::BIT_b_r8,		"BIT", "7, L" },
				{ 0x7E, 0, opcodes::BIT_b_dHL,		"BIT", "7, (HL)" },
				{ 0x7F, 0, opcodes::BIT_b_r8,		"BIT", "7, A" },

				{ 0x80, 0, opcodes::RES_b_r8,		"RES", "0, B" },
				{ 0x81, 0, opcodes::RES_b_r8,		"RES", "0, C" },
				{ 0x82, 0, opcodes::RES_b_r8,		"RES", "0, D" },
				{ 0x83, 0, opcodes::RES_b_r8,		"RES", "0, E" },
				{ 0x84, 0, opcodes::RES_b_r8,		"RES", "0, H" },
				{ 0x85, 0, opcodes::RES_b_r8,		"RES", "0, L" },
				{ 0x86, 0, opcodes::RES_b_dHL,		"RES", "0, (HL)" },
				{ 0x87, 0, opcodes::RES_b_r8,		"RES", "0, A" },
				{ 0x88, 0, opcodes::RES_b_r8,		"RES", "1, B" },
				{ 0x89, 0, opcodes::RES_b_r8,		"RES", "1, C" },
				{ 0x8A, 0, opcodes::RES_b_r8,		"RES", "1, D" },
				{ 0x8B, 0, opcodes::RES_b_r8,		"RES", "1, E" },
				{ 0x8C, 0, opcodes::RES_b_r8,		"RES", "1, H" },
				{ 0x8D, 0, opcodes::RES_b_r8,		"RES", "1, L" },
				{ 0x8E, 0, opcodes::RES_b_dHL,		"RES", "1, (HL)" },
				{ 0x8F, 0, opcodes::RES_b_r8,		"RES", "1, A" },

				{ 0x90, 0, opcodes::RES_b_r8,		"RES", "2, B" },
				{ 0x91, 0, opcodes::RES_b_r8,		"RES", "2, C" },
				{ 0x92, 0, opcodes::RES_b_r8,		"RES", "2, D" },
				{ 0x93, 0, opcodes::RES_b_r8,		"RES", "2, E" },
				{ 0x94, 0, opcodes::RES_b_r8,		"RES", "2, H" },
				{ 0x95, 0, opcodes::RES_b_r8,		"RES", "2, L" },
				{ 0x96, 0, opcodes::RES_b_dHL,		"RES", "2, (HL)" },
				{ 0x97, 0, opcodes::RES_b_r8,		"RES", "2, A" },
				{ 0x98, 0, opcodes::RES_b_r8,		"RES", "3, B" },
				{ 0x99, 0, opcodes::RES_b_r8,		"RES", "3, C" },
				{ 0x9A, 0, opcodes::RES_b_r8,		"RES", "3, D" },
				{ 0x9B, 0, opcodes::RES_b_r8,		"RES", "3, E" },
				{ 0x9C, 0, opcodes::RES_b_r8,		"RES", "3, H" },
				{ 0x9D, 0, opcodes::RES_b_r8,		"RES", "3, L" },
				{ 0x9E, 0, opcodes::RES_b_dHL,		"RES", "3, (HL)" },
				{ 0x9F, 0, opcodes::RES_b_r8,		"RES", "3, A" },

				{ 0xA0, 0, opcodes::RES_b_r8,		"RES", "4, B" },
				{ 0xA1, 0, opcodes::RES_b_r8,		"RES", "4, C" },
				{ 0xA2, 0, opcodes::RES_b_r8,		"RES", "4, D" },
				{ 0xA3, 0, opcodes::RES_b_r8,		"RES", "4, E" },
				{ 0xA4, 0, opcodes::RES_b_r8,		"RES", "4, H" },
				{ 0xA5, 0, opcodes::RES_b_r8,		"RES", "4, L" },
				{ 0xA6, 0, opcodes::RES_b_dHL,		"RES", "4, (HL)" },
				{ 0xA7, 0, opcodes::RES_b_r8,		"RES", "4, A" },
				{ 0xA8, 0, opcodes::RES_b_r8,		"RES", "5, B" },
				{ 0xA9, 0, opcodes::RES_b_r8,		"RES", "5, C" },
				{ 0xAA, 0, opcodes::RES_b_r8,		"RES", "5, D" },
				{ 0xAB, 0, opcodes::RES_b_r8,		"RES", "5, E" },
				{ 0xAC, 0, opcodes::RES_b_r8,		"RES", "5, H" },
				{ 0xAD, 0, opcodes::RES_b_r8,		"RES", "5, L" },
				{ 0xAE, 0, opcodes::RES_b_dHL,		"RES", "5, (HL)" },
				{ 0xAF, 0, opcodes::RES_b_r8,		"RES", "5, A" },

				{ 0xB0, 0, opcodes::RES_b_r8,		"RES", "6, B" },
				{ 0xB1, 0, opcodes::RES_b_r8,		"RES", "6, C" },
				{ 0xB2, 0, opcodes::RES_b_r8,		"RES", "6, D" },
				{ 0xB3, 0, opcodes::RES_b_r8,		"RES", "6, E" },
				{ 0xB4, 0, opcodes::RES_b_r8,		"RES", "6, H" },
				{ 0xB5, 0, opcodes::RES_b_r8,		"RES", "6, L" },
				{ 0xB6, 0, opcodes::RES_b_dHL,		"RES", "6, (HL)" },
				{ 0xB7, 0, opcodes::RES_b_r8,		"RES", "6, A" },
				{ 0xB8, 0, opcodes::RES_b_r8,		"RES", "7, B" },
				{ 0xB9, 0, opcodes::RES_b_r8,		"RES", "7, C" },
				{ 0xBA, 0, opcodes::RES_b_r8,		"RES", "7, D" },
				{ 0xBB, 0, opcodes::RES_b_r8,		"RES", "7, E" },
				{ 0xBC, 0, opcodes::RES_b_r8,		"RES", "7, H" },
				{ 0xBD, 0, opcodes::RES_b_r8,		"RES", "7, L" },
				{ 0xBE, 0, opcodes::RES_b_dHL,		"RES", "7, (HL)" },
				{ 0xBF, 0, opcodes::RES_b_r8,		"RES", "7, A" },

				{ 0xC0, 0, opcodes::SET_b_r8,		"SET", "0, B" },
				{ 0xC1, 0, opcodes::SET_b_r8,		"SET", "0, C" },
				{ 0xC2, 0, opcodes::SET_b_r8,		"SET", "0, D" },
				{ 0xC3, 0, opcodes::SET_b_r8,		"SET", "0, E" },
				{ 0xC4, 0, opcodes::SET_b_r8,		"SET", "0, H" },
				{ 0xC5, 0, opcodes::SET_b_r8,		"SET", "0, L" },
				{ 0xC6, 0, opcodes::SET_b_dHL,		"SET", "0, (HL)" },
				{ 0xC7, 0, opcodes::SET_b_r8,		"SET", "0, A" },
				{ 0xC8, 0, opcodes::SET_b_r8,		"SET", "1, B" },
				{ 0xC9, 0, opcodes::SET_b_r8,		"SET", "1, C" },
				{ 0xCA, 0, opcodes::SET_b_r8,		"SET", "1, D" },
				{ 0xCB, 0, opcodes::SET_b_r8,		"SET", "1, E" },
				{ 0xCC, 0, opcodes::SET_b_r8,		"SET", "1, H" },
				{ 0xCD, 0, opcodes::SET_b_r8,		"SET", "1, L" },
				{ 0xCE, 0, opcodes::SET_b_dHL,		"SET", "1, (HL)" },
				{ 0xCF, 0, opcodes::SET_b_r8,		"SET", "1, A" },

				{ 0xD0, 0, opcodes::SET_b_r8,		"SET", "2, B" },
				{ 0xD1, 0, opcodes::SET_b_r8,		"SET", "2, C" },
				{ 0xD2, 0, opcodes::SET_b_r8,		"SET", "2, D" },
				{ 0xD3, 0, opcodes::SET_b_r8,		"SET", "2, E" },
				{ 0xD4, 0, opcodes::SET_b_r8,		"SET", "2, H" },
				{ 0xD5, 0, opcodes::SET_b_r8,		"SET", "2, L" },
				{ 0xD6, 0, opcodes::SET_b_dHL,		"SET", "2, (HL)" },
				{ 0xD7, 0, opcodes::SET_b_r8,		"SET", "2, A" },
				{ 0xD8, 0, opcodes::SET_b_r8,		"SET", "3, B" },
				{ 0xD9, 0, opcodes::SET_b_r8,		"SET", "3, C" },
				{ 0xDA, 0, opcodes::SET_b_r8,		"SET", "3, D" },
				{ 0xDB, 0, opcodes::SET_b_r8,		"SET", "3, E" },
				{ 0xDC, 0, opcodes::SET_b_r8,		"SET", "3, H" },
				{ 0xDD, 0, opcodes::SET_b_r8,		"SET", "3, L" },
				{ 0xDE, 0, opcodes::SET_b_dHL,		"SET", "3, (HL)" },
				{ 0xDF, 0, opcodes::SET_b_r8,		"SET", "3, A" },

				{ 0xE0, 0, opcodes::SET_b_r8,		"SET", "4, B" },
				{ 0xE1, 0, opcodes::SET_b_r8,		"SET", "4, C" },
				{ 0xE2, 0, opcodes::SET_b_r8,		"SET", "4, D" },
				{ 0xE3, 0, opcodes::SET_b_r8,		"SET", "4, E" },
				{ 0xE4, 0, opcodes::SET_b_r8,		"SET", "4, H" },
				{ 0xE5, 0, opcodes::SET_b_r8,		"SET", "4, L" },
				{ 0xE6, 0, opcodes::SET_b_dHL,		"SET", "4, (HL)" },
				{ 0xE7, 0, opcodes::SET_b_r8,		"SET", "4, A" },
				{ 0xE8, 0, opcodes::SET_b_r8,		"SET", "5, B" },
				{ 0xE9, 0, opcodes::SET_b_r8,		"SET", "5, C" },
				{ 0xEA, 0, opcodes::SET_b_r8,		"SET", "5, D" },
				{ 0xEB, 0, opcodes::SET_b_r8,		"SET", "5, E" },
				{ 0xEC, 0, opcodes::SET_b_r8,		"SET", "5, H" },
				{ 0xED, 0, opcodes::SET_b_r8,		"SET", "5, L" },
				{ 0xEE, 0, opcodes::SET_b_dHL,		"SET", "5, (HL)" },
				{ 0xEF, 0, opcodes::SET_b_r8,		"SET", "5, A" },

				{ 0xF0, 0, opcodes::SET_b_r8,		"SET", "6, B" },
				{ 0xF1, 0, opcodes::SET_b_r8,		"SET", "6, C" },
				{ 0xF2, 0, opcodes::SET_b_r8,		"SET", "6, D" },
				{ 0xF3, 0, opcodes::SET_b_r8,		"SET", "6, E" },
				{ 0xF4, 0, opcodes::SET_b_r8,		"SET", "6, H" },
				{ 0xF5, 0, opcodes::SET_b_r8,		"SET", "6, L" },
				{ 0xF6, 0, opcodes::SET_b_dHL,		"SET", "6, (HL)" },
				{ 0xF7, 0, opcodes::SET_b_r8,		"SET", "6, A" },
				{ 0xF8, 0, opcodes::SET_b_r8,		"SET", "7, B" },
				{ 0xF9, 0, opcodes::SET_b_r8,		"SET", "7, C" },
				{ 0xFA, 0, opcodes::SET_b_r8,		"SET", "7, D" },
				{ 0xFB, 0, opcodes::SET_b_r8,		"SET", "7, E" },
				{ 0xFC, 0, opcodes::SET_b_r8,		"SET", "7, H" },
				{ 0xFD, 0, opcodes::SET_b_r8,		"SET", "7, L" },
				{ 0xFE, 0, opcodes::SET_b_dHL,		"SET", "7, (HL)" },
				{ 0xFF, 0, opcodes::SET_b_r8,		"SET", "7, A" },
			};
		}
	}
}
