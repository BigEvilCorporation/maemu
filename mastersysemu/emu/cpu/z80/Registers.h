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
							u8 a;
							u8 f;
						};
					};

					union
					{
						u16 bc;
						struct
						{
							u8 b;
							u8 c;
						};
					};

					union
					{
						u16 de;
						struct
						{
							u8 d;
							u8 e;
						};
					};

					union
					{
						u16 hl;
						struct
						{
							u8 h;
							u8 l;
						};					};
				};

				Pairs main;
				Pairs alt;

				u16 sp;
				u16 pc;

				union
				{
					u16 ix;
					struct
					{
						u8 ixh;
						u8 ixl;
					};
				};
				
				union
				{
					u16 iy;
					struct
					{
						u8 iyh;
						u8 iyl;
					};
				};
				
				u8 i;
				u8 r;
			};
		}
	}
}