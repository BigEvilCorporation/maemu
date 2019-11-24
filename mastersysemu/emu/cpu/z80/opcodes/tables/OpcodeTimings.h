#pragma once

namespace emu
{
	namespace cpu
	{
		namespace z80
		{
			namespace timing
			{
				static const int ADC_A_dHL = 7;
				static const int ADC_A_n8 = 7;
				static const int ADC_A_r8 = 4;
				static const int ADC_A_dIX = 19;
				static const int ADC_A_IXHL = 4;
				static const int ADC_HL_r16 = 15;
				static const int ADD_A_dHL = 7;
				static const int ADD_A_n8 = 7;
				static const int ADD_A_dIX = 19;
				static const int ADD_A_r8 = 4;
				static const int ADD_A_IXHL = 4;
				static const int ADD_HL_r16 = 11;
				static const int ADD_IX_r16 = 15;
				static const int ADD_IY_r16 = 15;
				static const int AND_A_dHL = 7;
				static const int AND_A_n8 = 7;
				static const int AND_A_dIX = 19;
				static const int AND_A_r8 = 4;
				static const int AND_A_IXHL = 4;
				static const int BIT_b_dHL = 12;
				static const int BIT_b_dIX = 20;
				static const int BIT_b_r8 = 8;
				static const int CALL_CC_n16 = 17;
				static const int CALL_n16 = 17;
				static const int CP_A_dHL = 7;
				static const int CP_A_n8 = 7;
				static const int CP_A_dIX = 19;
				static const int CP_A_r8 = 4;
				static const int CP_A_IXHL = 4;
				static const int DEC_dHL = 11;
				static const int DEC_dIX = 23;
				static const int DEC_IX = 10;
				static const int DEC_r8 = 4;
				static const int DEC_IXHL = 4;
				static const int DEC_r16 = 6;
				static const int DJNZ_n8 = 13;
				static const int EX_dSP_IX = 23;
				static const int EX_AF_AFa = 4;
				static const int EX_DE_HL = 4;
				static const int EX_dSP_HL = 4;
				static const int IM_0 = 8;
				static const int IM_1 = 8;
				static const int IM_2 = 8;
				static const int IN_A_n8 = 11;
				static const int IN_r8_C = 12;
				static const int IN_F_C = 12;
				static const int INC_dHL = 11;
				static const int INC_dIX = 23;
				static const int INC_IX = 10;
				static const int INC_r8 = 4;
				static const int INC_IXHL = 4;
				static const int INC_r16 = 6;
				static const int JP_CC_n16 = 10;
				static const int JP_HL = 4;
				static const int JP_IX = 8;
				static const int JP_n16 = 10;
				static const int JR_CC_n8 = 12;
				static const int JR_NZ_n8 = 12;
				static const int JR_Z_n8 = 12;
				static const int JR_C_n8 = 12;
				static const int JR_NC_n8 = 12;
				static const int JR_n8 = 12;
				static const int LD_dIX_n8 = 19;
				static const int LD_dIX_r8 = 19;
				static const int LD_dBC_A = 13;
				static const int LD_dDE_A = 13;
				static const int LD_A_dBC = 13;
				static const int LD_A_dDE = 13;
				static const int LD_A_d16 = 13;
				static const int LD_r8_dHL = 7;
				static const int LD_n16_A = 13;
				static const int LD_n16_HL = 16;
				static const int LD_n16_r16 = 20;
				static const int LD_n16_IX = 20;
				static const int LD_r16_r8 = 7;
				static const int LD_IXHL_n8 = 7;
				static const int LD_dHL_r8 = 7;
				static const int LD_A_n16 = 13;
				static const int LD_A_I = 9;
				static const int LD_A_R = 9;
				static const int LD_HL_n16 = 16;
				static const int LD_dHL_n8 = 13;
				static const int LD_I_A = 9;
				static const int LD_R_A = 9;
				static const int LD_IX_n16 = 14;
				static const int LD_IX_dn16 = 20;
				static const int LD_r8_dIX = 19;
				static const int LD_r8_r16 = 7;
				static const int LD_r8_n8 = 7;
				static const int LD_r8_RLC_IX = 4;
				static const int LD_r8_r8 = 4;
				static const int LD_r8_IXHL = 4;
				static const int LD_r16_dn16 = 20;
				static const int LD_r16_n16 = 10;
				static const int LD_SP_HL = 6;
				static const int LD_SP_IX = 10;
				static const int OR_A_dIX = 19;
				static const int OR_A_dHL = 19;
				static const int OR_A_n8 = 7;
				static const int OR_A_r8 = 4;
				static const int OR_A_IXHL = 4;
				static const int OUT_C_r8 = 12;
				static const int OUT_C_n8 = 12;
				static const int OUT_C_F = 12;
				static const int OUT_n8_A = 11;
				static const int POP_IX = 14;
				static const int POP_r16 = 10;
				static const int PUSH_IX = 15;
				static const int PUSH_r16 = 11;
				static const int RES_b_dHL = 15;
				static const int RES_b_dIX = 23;
				static const int RES_b_r8 = 8;
				static const int RET_CC = 11;
				static const int RL_dHL = 15;
				static const int RL_dIX = 23;
				static const int RL_r8 = 8;
				static const int RR_dHL = 15;
				static const int RR_dIX = 23;
				static const int RR_r8 = 8;
				static const int RRC_dHL = 15;
				static const int RRC_dIX = 23;
				static const int RLC_dHL = 15;
				static const int RLC_dIX = 23;
				static const int RRC = 4;
				static const int RLC = 4;
				static const int RST = 11;
				static const int SBC_A_dIX = 19;
				static const int SBC_A_dHL = 7;
				static const int SBC_A_n8 = 7;
				static const int SBC_HL_r16 = 15;
				static const int SBC_A_r8 = 4;
				static const int SBC_A_IXHL = 4;
				static const int SET_b_dHL = 15;
				static const int SET_b_dIX = 23;
				static const int SET_b_r8 = 8;
				static const int SLA_dHL = 15;
				static const int SLA_dIX = 23;
				static const int SLA_r8 = 8;
				static const int SLL_dHL = 15;
				static const int SLL_sIX = 23;
				static const int SLL_r8 = 8;
				static const int SRA_dHL = 15;
				static const int SRA_dIX = 23;
				static const int SRA_r8 = 8;
				static const int SRL_dHL = 15;
				static const int SRL_dIX = 23;
				static const int SRL_r8 = 8;
				static const int SUB_A_dIX = 19;
				static const int SUB_A_dHL = 7;
				static const int SUB_A_n8 = 7;
				static const int SUB_A_r8 = 4;
				static const int SUB_A_IXHL = 4;
				static const int XOR_A_dIX = 19;
				static const int XOR_A_n8 = 7;
				static const int XOR_A_dHL = 7;
				static const int XOR_A_r8 = 4;
				static const int XOR_A_IXHL = 4;
				static const int DI = 4;
				static const int EI = 4;
				static const int IND = 16;
				static const int INI = 16;
				static const int INDR = 21;
				static const int INIR = 21;
				static const int RLC_r8 = 8;
				static const int RRC_r8 = 8;
				static const int RLD = 18;
				static const int RRD = 18;
				static const int RETI = 14;
				static const int RETN = 14;
				static const int RLA = 4;
				static const int RRA = 4;
				static const int RLCA = 4;
				static const int RRCA = 4;
				static const int SCF = 4;
				static const int RET = 10;
				static const int OTD = 16;
				static const int OTI = 16;
				static const int OTDR = 21;
				static const int OTIR = 21;
				static const int LDD = 16;
				static const int LDI = 16;
				static const int LDDR = 21;
				static const int LDIR = 21;
				static const int NEG = 8;
				static const int NOP = 4;
				static const int EXX = 4;
				static const int HALT = 4;
				static const int CPD = 16;
				static const int CPDR = 21;
				static const int CPI = 16;
				static const int CPIR = 21;
				static const int CPL_A = 4;
				static const int DAA = 4;
				static const int CCF = 4;
			}
		}
	}
}