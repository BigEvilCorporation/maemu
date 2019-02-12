#pragma once

#include <ion/core/Types.h>

namespace emu
{
	namespace cpu
	{
		namespace z80
		{
			struct Registers
			{
				struct Pairs
				{
					union
					{
						u16 af;
						struct
						{
							u8 f;
							u8 a;
						};
					};

					union
					{
						u16 bc;
						struct
						{
							u8 c;
							u8 b;
						};
					};

					union
					{
						u16 de;
						struct
						{
							u8 e;
							u8 d;
						};
					};

					union
					{
						u16 hl;
						struct
						{
							u8 l;
							u8 h;
						};
					};
				};

				//8-bit register pairs
				Pairs main;
				Pairs alt;

				//16-bit registers
				u16 sp;
				u16 pc;

				union
				{
					u16 ix;
					struct
					{
						u8 ixl;
						u8 ixh;
					};
				};
				
				union
				{
					u16 iy;
					struct
					{
						u8 iyl;
						u8 iyh;
					};
				};
				

				//I/R
				u8 i;
				u8 r;

				//Internal regs
				struct
				{
					u8 im;
					u8 iff1;
					u8 iff2;
				} internal;
			};
		}
	}
}