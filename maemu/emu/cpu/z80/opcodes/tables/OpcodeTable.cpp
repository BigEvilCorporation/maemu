#pragma once

#include "OpcodeTable.h"
#include "OpcodeTimings.h"

//Prefix tables
#include "OpcodeTableCB.h"
#include "OpcodeTableDD.h"
#include "OpcodeTableED.h"
#include "OpcodeTableFD.h"
#include "OpcodeTableDDCB.h"
#include "OpcodeTableFDCB.h"

//Prefix handlers
#include "../prefix_cb.h"
#include "../prefix_dd.h"
#include "../prefix_ed.h"
#include "../prefix_fd.h"

//All opcode handlers
#include "../arithmetic.h"
#include "../bitwise.h"
#include "../comparison.h"
#include "../exchange.h"
#include "../flags.h"
#include "../halt.h"
#include "../incdec.h"
#include "../interrupts.h"
#include "../ports.h"
#include "../jump.h"
#include "../load.h"
#include "../nop.h"
#include "../routines.h"
#include "../stack.h"

namespace emu
{
	namespace cpu
	{
		namespace z80
		{
			const Opcode OpcodeTable[Z80_MAX_OPCODE_TABLE_SIZE] =
			{
				{ 0x00, 0, timing::NOP,			&opcodes::NOP,			"NOP", "" },
				{ 0x01, 2, timing::LD_r16_n16,	 opcodes::LD_r16_n16,	"LD", "BC, ##" },
				{ 0x02, 0, timing::LD_dBC_A,	 opcodes::LD_dBC_A,		"LD", "(BC), A" },
				{ 0x03, 0, timing::INC_r16,		 opcodes::INC_r16,		"INC", "BC" },
				{ 0x04, 0, timing::INC_r8,		 opcodes::INC_r8,		"INC", "B" },
				{ 0x05, 0, timing::DEC_r8,		 opcodes::DEC_r8,		"DEC", "B" },
				{ 0x06, 1, timing::LD_r8_n8,	 opcodes::LD_r8_n8,		"LD", "B, #" },
				{ 0x07, 0, timing::RLCA,		 opcodes::RLCA,			"RLCA", "" },
				{ 0x08, 0, timing::EX_AF_AFa,	&opcodes::EX_AF_AFa,	"EX", "AF, AF'" },
				{ 0x09, 0, timing::ADD_HL_r16,	 opcodes::ADD_HL_r16,	"ADD", "HL, BC" },
				{ 0x0A, 0, timing::LD_A_dBC,	 opcodes::LD_A_dBC,		"LD", "A, (BC)" },
				{ 0x0B, 0, timing::DEC_r16,		 opcodes::DEC_r16,		"DEC", "BC" },
				{ 0x0C, 0, timing::INC_r8,		 opcodes::INC_r8,		"INC", "C" },
				{ 0x0D, 0, timing::DEC_r8,		 opcodes::DEC_r8,		"DEC", "C" },
				{ 0x0E, 1, timing::LD_r8_n8,	 opcodes::LD_r8_n8,		"LD", "C, #" },
				{ 0x0F, 0, timing::RRCA,		&opcodes::RRCA,			"RRCA", "" },

				{ 0x10, 1, timing::DJNZ_n8,		&opcodes::DJNZ_n8,		"DJNZ", "#" },
				{ 0x11, 2, timing::LD_r16_n16,	 opcodes::LD_r16_n16,	"LD", "DE, ##" },
				{ 0x12, 0, timing::LD_dDE_A,	 opcodes::LD_dDE_A,		"LD", "(DE), A" },
				{ 0x13, 0, timing::INC_r16,		 opcodes::INC_r16,		"INC", "DE" },
				{ 0x14, 0, timing::INC_r8,		 opcodes::INC_r8,		"INC", "D" },
				{ 0x15, 0, timing::DEC_r8,		 opcodes::DEC_r8,		"DEC", "D" },
				{ 0x16, 1, timing::LD_r8_n8,	 opcodes::LD_r8_n8,		"LD", "D, #" },
				{ 0x17, 0, timing::RLA,			&opcodes::RLA,			"RLA", "" },
				{ 0x18, 1, timing::JR_n8,		&opcodes::JR_n8,		"JR", "#" },
				{ 0x19, 0, timing::ADD_HL_r16,	 opcodes::ADD_HL_r16,	"ADD", "HL, DE" },
				{ 0x1A, 0, timing::LD_A_dDE,	 opcodes::LD_A_dDE,		"LD", "A, (DE)" },
				{ 0x1B, 0, timing::DEC_r16,		 opcodes::DEC_r16,		"DEC", "DE" },
				{ 0x1C, 0, timing::INC_r8,		 opcodes::INC_r8,		"INC", "E" },
				{ 0x1D, 0, timing::DEC_r8,		 opcodes::DEC_r8,		"DEC", "E" },
				{ 0x1E, 1, timing::LD_r8_n8,	 opcodes::LD_r8_n8,		"LD", "E, #" },
				{ 0x1F, 0, timing::RRA,			&opcodes::RRA,			"RRA", "" },

				{ 0x20, 1, timing::JR_NZ_n8,	&opcodes::JR_NZ_n8,		"JR", "NZ, #" },
				{ 0x21, 2, timing::LD_r16_n16,	 opcodes::LD_r16_n16,	"LD", "HL, ##" },
				{ 0x22, 2, timing::LD_n16_HL,	 opcodes::LD_n16_HL,	"LD", "##, HL" },
				{ 0x23, 0, timing::INC_r16,		 opcodes::INC_r16,		"INC", "HL" },
				{ 0x24, 0, timing::INC_r8,		 opcodes::INC_r8,		"INC", "H" },
				{ 0x25, 0, timing::DEC_r8,		 opcodes::DEC_r8,		"DEC", "H" },
				{ 0x26, 1, timing::LD_r8_n8,	 opcodes::LD_r8_n8,		"LD", "H, #" },
				{ 0x27, 0, timing::DAA,			&opcodes::DAA,			"DAA", "" },
				{ 0x28, 1, timing::JR_Z_n8,		&opcodes::JR_Z_n8,		"JR", "Z, #" },
				{ 0x29, 0, timing::ADD_HL_r16,	 opcodes::ADD_HL_r16,	"ADD", "HL, HL" },
				{ 0x2A, 2, timing::LD_r16_dn16,	 opcodes::LD_r16_dn16,	"LD", "HL, (##)" },
				{ 0x2B, 0, timing::DEC_r16,		 opcodes::DEC_r16,		"DEC", "HL" },
				{ 0x2C, 0, timing::INC_r8,		 opcodes::INC_r8,		"INC", "L" },
				{ 0x2D, 0, timing::DEC_r8,		 opcodes::DEC_r8,		"DEC", "L" },
				{ 0x2E, 1, timing::LD_r8_n8,	 opcodes::LD_r8_n8,		"LD", "L, #" },
				{ 0x2F, 0, timing::CPL_A,		&opcodes::CPL_A,		"CPL_A", "" },

				{ 0x30, 1, timing::JR_NC_n8,	&opcodes::JR_NC_n8,		"JR", "NC, #" },
				{ 0x31, 2, timing::LD_r16_n16,	 opcodes::LD_r16_n16,	"LD", "SP, ##" },
				{ 0x32, 2, timing::LD_n16_A,	 opcodes::LD_n16_A,		"LD", "##, A" },
				{ 0x33, 0, timing::INC_r16,		 opcodes::INC_r16,		"INC", "SP" },
				{ 0x34, 0, timing::INC_dHL,		 opcodes::INC_dHL,		"INC", "(HL)" },
				{ 0x35, 0, timing::DEC_dHL,		 opcodes::DEC_dHL,		"DEC", "(HL)" },
				{ 0x36, 1, timing::LD_dHL_n8,	 opcodes::LD_dHL_n8,	"LD", "(HL), #" },
				{ 0x37, 0, timing::SCF,			&opcodes::SCF,			"SCF", "" },
				{ 0x38, 1, timing::JR_C_n8,		&opcodes::JR_C_n8,		"JR", "C, #" },
				{ 0x39, 0, timing::ADD_HL_r16,	 opcodes::ADD_HL_r16,	"ADD", "HL, SP" },
				{ 0x3A, 2, timing::LD_A_d16,	 opcodes::LD_A_d16,		"LD", "A,(##)" },
				{ 0x3B, 0, timing::DEC_r16,		 opcodes::DEC_r16,		"DEC", "SP" },
				{ 0x3C, 0, timing::INC_r8,		 opcodes::INC_r8,		"INC", "A" },
				{ 0x3D, 0, timing::DEC_r8,		 opcodes::DEC_r8,		"DEC", "A" },
				{ 0x3E, 1, timing::LD_r8_n8,	 opcodes::LD_r8_n8,		"LD", "A, #" },
				{ 0x3F, 0, timing::CCF,			&opcodes::CCF,			"CCF", "" },

				{ 0x40, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "B, B" },
				{ 0x41, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "B, C" },
				{ 0x42, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "B, D" },
				{ 0x43, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "B, E" },
				{ 0x44, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "B, H" },
				{ 0x45, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "B, L" },
				{ 0x46, 0, timing::LD_r8_dHL,	 opcodes::LD_r8_dHL,	"LD", "B, (HL)" },
				{ 0x47, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "B, A" },
				{ 0x48, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "C, B" },
				{ 0x49, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "C, C" },
				{ 0x4A, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "C, D" },
				{ 0x4B, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "C, E" },
				{ 0x4C, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "C, H" },
				{ 0x4D, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "C, L" },
				{ 0x4E, 0, timing::LD_r8_dHL,	 opcodes::LD_r8_dHL,	"LD", "C, (HL)" },
				{ 0x4F, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "C, A" },

				{ 0x50, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "D, B" },
				{ 0x51, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "D, C" },
				{ 0x52, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "D, D" },
				{ 0x53, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "D, E" },
				{ 0x54, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "D, H" },
				{ 0x55, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "D, L" },
				{ 0x56, 0, timing::LD_r8_dHL,	 opcodes::LD_r8_dHL,	"LD", "D, (HL)" },
				{ 0x57, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "D, A" },
				{ 0x58, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "E, B" },
				{ 0x59, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "E, C" },
				{ 0x5A, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "E, D" },
				{ 0x5B, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "E, E" },
				{ 0x5C, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "E, H" },
				{ 0x5D, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "E, L" },
				{ 0x5E, 0, timing::LD_r8_dHL,	 opcodes::LD_r8_dHL,	"LD", "E, (HL)" },
				{ 0x5F, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "E, A" },

				{ 0x60, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "H, B" },
				{ 0x61, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "H, C" },
				{ 0x62, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "H, D" },
				{ 0x63, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "H, E" },
				{ 0x64, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "H, H" },
				{ 0x65, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "H, L" },
				{ 0x66, 0, timing::LD_r8_dHL,	 opcodes::LD_r8_dHL,	"LD", "H, (HL)" },
				{ 0x67, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "H, A" },
				{ 0x68, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "L, B" },
				{ 0x69, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "L, C" },
				{ 0x6A, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "L, D" },
				{ 0x6B, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "L, E" },
				{ 0x6C, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "L, H" },
				{ 0x6D, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "L, L" },
				{ 0x6E, 0, timing::LD_r8_dHL,	 opcodes::LD_r8_dHL,	"LD", "L, (HL)" },
				{ 0x6F, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "L, A" },

				{ 0x70, 0, timing::LD_dHL_r8,	 opcodes::LD_dHL_r8,	"LD", "(HL), B" },
				{ 0x71, 0, timing::LD_dHL_r8,	 opcodes::LD_dHL_r8,	"LD", "(HL), C" },
				{ 0x72, 0, timing::LD_dHL_r8,	 opcodes::LD_dHL_r8,	"LD", "(HL), D" },
				{ 0x73, 0, timing::LD_dHL_r8,	 opcodes::LD_dHL_r8,	"LD", "(HL), E" },
				{ 0x74, 0, timing::LD_dHL_r8,	 opcodes::LD_dHL_r8,	"LD", "(HL), H" },
				{ 0x75, 0, timing::LD_dHL_r8,	 opcodes::LD_dHL_r8,	"LD", "(HL), L" },
				{ 0x76, 0, timing::HALT,		 opcodes::HALT,			"HALT", "" },
				{ 0x77, 0, timing::LD_dHL_r8,	 opcodes::LD_dHL_r8,	"LD", "(HL), A" },
				{ 0x78, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "A, B" },
				{ 0x79, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "A, C" },
				{ 0x7A, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "A, D" },
				{ 0x7B, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "A, E" },
				{ 0x7C, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "A, H" },
				{ 0x7D, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "A, L" },
				{ 0x7E, 0, timing::LD_r8_dHL,	 opcodes::LD_r8_dHL,	"LD", "A, (HL)" },
				{ 0x7F, 0, timing::LD_r8_r8,	 opcodes::LD_r8_r8,		"LD", "A, A" },

				{ 0x80, 0, timing::ADD_A_r8,	 opcodes::ADD_A_r8,		"ADD", "A, B" },
				{ 0x81, 0, timing::ADD_A_r8,	 opcodes::ADD_A_r8,		"ADD", "A, C" },
				{ 0x82, 0, timing::ADD_A_r8,	 opcodes::ADD_A_r8,		"ADD", "A, D" },
				{ 0x83, 0, timing::ADD_A_r8,	 opcodes::ADD_A_r8,		"ADD", "A, E" },
				{ 0x84, 0, timing::ADD_A_r8,	 opcodes::ADD_A_r8,		"ADD", "A, H" },
				{ 0x85, 0, timing::ADD_A_r8,	 opcodes::ADD_A_r8,		"ADD", "A, L" },
				{ 0x86, 0, timing::ADD_A_dHL,	 opcodes::ADD_A_dHL,	"ADD", "A, (HL)" },
				{ 0x87, 0, timing::ADD_A_r8,	 opcodes::ADD_A_r8,		"ADD", "A, A" },
				{ 0x88, 0, timing::ADC_A_r8,	 opcodes::ADC_A_r8,		"ADC", "A, B" },
				{ 0x89, 0, timing::ADC_A_r8,	 opcodes::ADC_A_r8,		"ADC", "A, C" },
				{ 0x8A, 0, timing::ADC_A_r8,	 opcodes::ADC_A_r8,		"ADC", "A, D" },
				{ 0x8B, 0, timing::ADC_A_r8,	 opcodes::ADC_A_r8,		"ADC", "A, E" },
				{ 0x8C, 0, timing::ADC_A_r8,	 opcodes::ADC_A_r8,		"ADC", "A, H" },
				{ 0x8D, 0, timing::ADC_A_r8,	 opcodes::ADC_A_r8,		"ADC", "A, L" },
				{ 0x8E, 0, timing::ADC_A_dHL,	 opcodes::ADC_A_dHL,	"ADC", "A, (HL)" },
				{ 0x8F, 0, timing::ADC_A_r8,	 opcodes::ADC_A_r8,		"ADC", "A, A" },

				{ 0x90, 0, timing::SUB_A_r8,	 opcodes::SUB_A_r8,		"SUB", "A, B" },
				{ 0x91, 0, timing::SUB_A_r8,	 opcodes::SUB_A_r8,		"SUB", "A, C" },
				{ 0x92, 0, timing::SUB_A_r8,	 opcodes::SUB_A_r8,		"SUB", "A, D" },
				{ 0x93, 0, timing::SUB_A_r8,	 opcodes::SUB_A_r8,		"SUB", "A, E" },
				{ 0x94, 0, timing::SUB_A_r8,	 opcodes::SUB_A_r8,		"SUB", "A, H" },
				{ 0x95, 0, timing::SUB_A_r8,	 opcodes::SUB_A_r8,		"SUB", "A, L" },
				{ 0x96, 0, timing::SUB_A_dHL,	 opcodes::SUB_A_dHL,	"SUB", "A, (HL)" },
				{ 0x97, 0, timing::SUB_A_r8,	 opcodes::SUB_A_r8,		"SUB", "A, A" },
				{ 0x98, 0, timing::SBC_A_r8,	 opcodes::SBC_A_r8,		"SBC", "A, B" },
				{ 0x99, 0, timing::SBC_A_r8,	 opcodes::SBC_A_r8,		"SBC", "A, C" },
				{ 0x9A, 0, timing::SBC_A_r8,	 opcodes::SBC_A_r8,		"SBC", "A, D" },
				{ 0x9B, 0, timing::SBC_A_r8,	 opcodes::SBC_A_r8,		"SBC", "A, E" },
				{ 0x9C, 0, timing::SBC_A_r8,	 opcodes::SBC_A_r8,		"SBC", "A, H" },
				{ 0x9D, 0, timing::SBC_A_r8,	 opcodes::SBC_A_r8,		"SBC", "A, L" },
				{ 0x9E, 0, timing::SBC_A_dHL,	 opcodes::SBC_A_dHL,	"SBC", "A, (HL)" },
				{ 0x9F, 0, timing::SBC_A_r8,	 opcodes::SBC_A_r8,		"SBC", "A, A" },

				{ 0xA0, 0, timing::AND_A_r8,	 opcodes::AND_A_r8,		"AND", "B" },
				{ 0xA1, 0, timing::AND_A_r8,	 opcodes::AND_A_r8,		"AND", "C" },
				{ 0xA2, 0, timing::AND_A_r8,	 opcodes::AND_A_r8,		"AND", "D" },
				{ 0xA3, 0, timing::AND_A_r8,	 opcodes::AND_A_r8,		"AND", "E" },
				{ 0xA4, 0, timing::AND_A_r8,	 opcodes::AND_A_r8,		"AND", "H" },
				{ 0xA5, 0, timing::AND_A_r8,	 opcodes::AND_A_r8,		"AND", "L" },
				{ 0xA6, 0, timing::AND_A_dHL,	 opcodes::AND_A_dHL,	"AND", "(HL)" },
				{ 0xA7, 0, timing::AND_A_r8,	 opcodes::AND_A_r8,		"AND", "A" },
				{ 0xA8, 0, timing::XOR_A_r8,	 opcodes::XOR_A_r8,		"XOR", "B" },
				{ 0xA9, 0, timing::XOR_A_r8,	 opcodes::XOR_A_r8,		"XOR", "C" },
				{ 0xAA, 0, timing::XOR_A_r8,	 opcodes::XOR_A_r8,		"XOR", "D" },
				{ 0xAB, 0, timing::XOR_A_r8,	 opcodes::XOR_A_r8,		"XOR", "E" },
				{ 0xAC, 0, timing::XOR_A_r8,	 opcodes::XOR_A_r8,		"XOR", "H" },
				{ 0xAD, 0, timing::XOR_A_r8,	 opcodes::XOR_A_r8,		"XOR", "L" },
				{ 0xAE, 0, timing::XOR_A_dHL,	 opcodes::XOR_A_dHL,	"XOR", "(HL)" },
				{ 0xAF, 0, timing::XOR_A_r8,	 opcodes::XOR_A_r8,		"XOR", "A" },

				{ 0xB0, 0, timing::OR_A_r8,		 opcodes::OR_A_r8,		"OR", "B" },
				{ 0xB1, 0, timing::OR_A_r8,		 opcodes::OR_A_r8,		"OR", "C" },
				{ 0xB2, 0, timing::OR_A_r8,		 opcodes::OR_A_r8,		"OR", "D" },
				{ 0xB3, 0, timing::OR_A_r8,		 opcodes::OR_A_r8,		"OR", "E" },
				{ 0xB4, 0, timing::OR_A_r8,		 opcodes::OR_A_r8,		"OR", "H" },
				{ 0xB5, 0, timing::OR_A_r8,		 opcodes::OR_A_r8,		"OR", "L" },
				{ 0xB6, 0, timing::OR_A_dHL,	 opcodes::OR_A_dHL,		"OR", "(HL)" },
				{ 0xB7, 0, timing::OR_A_r8,		 opcodes::OR_A_r8,		"OR", "A" },
				{ 0xB8, 0, timing::CP_A_r8,		 opcodes::CP_A_r8,		"CP", "B" },
				{ 0xB9, 0, timing::CP_A_r8,		 opcodes::CP_A_r8,		"CP", "C" },
				{ 0xBA, 0, timing::CP_A_r8,		 opcodes::CP_A_r8,		"CP", "D" },
				{ 0xBB, 0, timing::CP_A_r8,		 opcodes::CP_A_r8,		"CP", "E" },
				{ 0xBC, 0, timing::CP_A_r8,		 opcodes::CP_A_r8,		"CP", "H" },
				{ 0xBD, 0, timing::CP_A_r8,		 opcodes::CP_A_r8,		"CP", "L" },
				{ 0xBE, 0, timing::CP_A_dHL,	 opcodes::CP_A_dHL,		"CP", "HL" },
				{ 0xBF, 0, timing::CP_A_r8,		 opcodes::CP_A_r8,		"CP", "A" },

				{ 0xC0, 0, timing::RET_CC,		&opcodes::RET_CC,		"RET", "NZ" },
				{ 0xC1, 0, timing::POP_r16,		&opcodes::POP_r16,		"POP", "BC" },
				{ 0xC2, 2, timing::JP_CC_n16,	&opcodes::JP_CC_n16,	"JP", "NZ, ##" },
				{ 0xC3, 2, timing::JP_n16,		&opcodes::JP_n16,		"JP", "##" },
				{ 0xC4, 2, timing::CALL_CC_n16,	&opcodes::CALL_CC_n16,	"CALL", "NZ, ##" },
				{ 0xC5, 0, timing::PUSH_r16,	&opcodes::PUSH_r16,		"PUSH", "BC" },
				{ 0xC6, 1, timing::ADD_A_n8,	 opcodes::ADD_A_n8,		"ADD", "A, #" },
				{ 0xC7, 0, timing::RST,			&opcodes::RST,			"RST", "$00" },
				{ 0xC8, 0, timing::RET_CC,		&opcodes::RET_CC,		"RET", "Z" },
				{ 0xC9, 0, timing::RET,			&opcodes::RET,			"RET", "" },
				{ 0xCA, 2, timing::JP_CC_n16,	&opcodes::JP_CC_n16,	"JP", "Z, ##" },
				{ 0xCB, 1, 0,					&opcodes::Prefix_CB,	"", "" },
				{ 0xCC, 2, timing::CALL_CC_n16,	&opcodes::CALL_CC_n16,	"CALL", "Z, ##" },
				{ 0xCD, 2, timing::CALL_n16,	&opcodes::CALL_n16,		"CALL", "##" },
				{ 0xCE, 1, timing::ADC_A_n8,	 opcodes::ADC_A_n8,		"ADC", "A, #" },
				{ 0xCF, 0, timing::RST,			&opcodes::RST,			"RST", "$08" },

				{ 0xD0, 0, timing::RET_CC,		&opcodes::RET_CC,		"RET", "NC" },
				{ 0xD1, 0, timing::POP_r16,		&opcodes::POP_r16,		"POP", "DE" },
				{ 0xD2, 2, timing::JP_CC_n16,	&opcodes::JP_CC_n16,	"JP", "NC, ##" },
				{ 0xD3, 1, timing::OUT_n8_A,	&opcodes::OUT_n8_A,		"OUT", "#, A" },
				{ 0xD4, 2, timing::CALL_CC_n16,	&opcodes::CALL_CC_n16,	"CALL", "NC, ##" },
				{ 0xD5, 0, timing::PUSH_r16,	&opcodes::PUSH_r16,		"PUSH", "DE" },
				{ 0xD6, 1, timing::SUB_A_n8,	 opcodes::SUB_A_n8,		"SUB", "A, #" },
				{ 0xD7, 0, timing::RST,			&opcodes::RST,			"RST", "$10" },
				{ 0xD8, 0, timing::RET_CC,		&opcodes::RET_CC,		"RET", "C" },
				{ 0xD9, 0, timing::EXX,			&opcodes::EXX,			"EXX", "" },
				{ 0xDA, 2, timing::JP_CC_n16,	&opcodes::JP_CC_n16,	"JP", "C, ##" },
				{ 0xDB, 1, timing::IN_A_n8,		&opcodes::IN_A_n8,		"IN", "A, #" },
				{ 0xDC, 2, timing::CALL_CC_n16,	&opcodes::CALL_CC_n16,	"CALL", "C, ##" },
				{ 0xDD, 1, 0,					&opcodes::Prefix_DD,	"", "" },
				{ 0xDE, 1, timing::SBC_A_n8,	 opcodes::SBC_A_n8,		"SBC", "A, #" },
				{ 0xDF, 0, timing::RST,			&opcodes::RST,			"RST", "$18" },

				{ 0xE0, 0, timing::RET_CC,		&opcodes::RET_CC,		"RET", "PO" },
				{ 0xE1, 0, timing::POP_r16,		&opcodes::POP_r16,		"POP", "HL" },
				{ 0xE2, 2, timing::JP_CC_n16,	&opcodes::JP_CC_n16,	"JP", "PO, ##" },
				{ 0xE3, 0, timing::EX_dSP_HL,	&opcodes::EX_dSP_HL,	"EX", "(SP), HL" },
				{ 0xE4, 2, timing::CALL_CC_n16,	&opcodes::CALL_CC_n16,	"CALL", "PO, ##" },
				{ 0xE5, 0, timing::PUSH_r16,	&opcodes::PUSH_r16,		"PUSH", "HL" },
				{ 0xE6, 1, timing::AND_A_n8,	 opcodes::AND_A_n8,		"AND", "A, #" },
				{ 0xE7, 0, timing::RST,			&opcodes::RST,			"RST", "$20" },
				{ 0xE8, 0, timing::RET_CC,		&opcodes::RET_CC,		"RET", "PE" },
				{ 0xE9, 0, timing::JP_HL,		&opcodes::JP_HL,		"JP", "(HL)" },
				{ 0xEA, 2, timing::JP_CC_n16,	&opcodes::JP_CC_n16,	"JP", "PE, ##" },
				{ 0xEB, 0, timing::EX_DE_HL,	&opcodes::EX_DE_HL,		"EX", "DE, HL" },
				{ 0xEC, 2, timing::CALL_CC_n16,	&opcodes::CALL_CC_n16,	"CALL", "PE, ##" },
				{ 0xED, 1, 0,					&opcodes::Prefix_ED,	"", "" },
				{ 0xEE, 1, timing::XOR_A_n8,	 opcodes::XOR_A_n8,		"XOR", "A, #" },
				{ 0xEF, 0, timing::RST,			&opcodes::RST,			"RST", "$28" },

				{ 0xF0, 0, timing::RET_CC,		&opcodes::RET_CC,		"RET", "P" },
				{ 0xF1, 0, timing::POP_r16,		&opcodes::POP_r16,		"POP", "AF" },
				{ 0xF2, 2, timing::JP_CC_n16,	&opcodes::JP_CC_n16,	"JP", "P, ##" },
				{ 0xF3, 0, timing::DI,			&opcodes::DI,			"DI", "" },
				{ 0xF4, 2, timing::CALL_CC_n16,	&opcodes::CALL_CC_n16,	"CALL", "P, ##" },
				{ 0xF5, 0, timing::PUSH_r16,	&opcodes::PUSH_r16,		"PUSH", "AF" },
				{ 0xF6, 1, timing::OR_A_n8,		 opcodes::OR_A_n8,		"OR", "A, #" },
				{ 0xF7, 0, timing::RST,			&opcodes::RST,			"RST", "$30" },
				{ 0xF8, 0, timing::RET_CC,		&opcodes::RET_CC,		"RET", "M" },
				{ 0xF9, 0, timing::LD_SP_HL,	 opcodes::LD_SP_HL,		"LD", "SP, HL" },
				{ 0xFA, 2, timing::JP_CC_n16,	&opcodes::JP_CC_n16,	"JP", "M, ##" },
				{ 0xFB, 0, timing::EI,			&opcodes::EI,			"EI", "" },
				{ 0xFC, 2, timing::CALL_CC_n16,	&opcodes::CALL_CC_n16,	"CALL", "M, ##" },
				{ 0xFD, 1, 0,					&opcodes::Prefix_FD,	"", "" },
				{ 0xFE, 1, timing::CP_A_n8,		 opcodes::CP_A_n8,		"CP", "#" },
				{ 0xFF, 0, timing::RST,			&opcodes::RST,			"RST", "$38" },
			};
		}
	}
}