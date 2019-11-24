#include "Z80.h"
#include "Constants.h"
#include "Interrupts.h"

#include "../../Constants.h"

#include <ion/core/debug/Debug.h>
#include <ion/maths/Maths.h>
#include <ion/core/time/Time.h>

namespace emu
{
	namespace cpu
	{
		namespace z80
		{
			Z80::Z80(Bus& bus)
				: m_bus(bus)
			{
				Reset();

				m_history.resize(Z80_DEBUG_MAX_PC_HISTORY);
			}

			void Z80::Reset()
			{
				//Guaranteed initial reg values - all others undefined
				m_regs.pc = 0x0000;
				m_regs.sp = 0xFFFF;
				m_regs.i = 0;
				m_regs.r = 0;
				m_regs.main.af = 0xFFFF;

				//Interrupt mode 0 by default
				m_regs.internal.im = Z80_INT_MODE0;

				//Clear interrupt state
				m_regs.internal.iff1 = 0;
				m_regs.internal.iff2 = 0;
				m_regs.internal.irq = 0;

				//Clear error flag
				m_regs.internal.err = 0;

				int seed = ion::time::GetSystemTicks();
				ion::maths::RandSeed(seed);
				m_regs.main.bc = ion::maths::RandInt();
				m_regs.main.de = ion::maths::RandInt();
				m_regs.main.hl = ion::maths::RandInt();
				m_regs.alt.af = ion::maths::RandInt();
				m_regs.alt.bc = ion::maths::RandInt();
				m_regs.alt.de = ion::maths::RandInt();
				m_regs.alt.hl = ion::maths::RandInt();
				m_regs.ix = ion::maths::RandInt();
				m_regs.iy = ion::maths::RandInt();

				for (int i = SMS_ADDR_RAM_START; i < SMS_ADDR_RAM_END; i++)
				{
					m_bus.memoryController.WriteMemory(i, ion::maths::RandInt());
				}
			}

			u32 Z80::StepInstruction()
			{
				//NOP = 4 cycles
				u32 cycleCount = 4;

				if (m_regs.internal.err == 0)
				{
					//Process pending interrupts
					if (m_regs.internal.irq && m_regs.internal.iff1)
					{
						//Disable interrupts before handling
						m_regs.internal.iff1 = 0;
						m_regs.internal.iff2 = 0;

						switch (m_regs.internal.im)
						{
							case Z80_INT_MODE0:
								break;
							case Z80_INT_MODE1:
								{
									//Push PC
									m_regs.sp--;
									m_bus.memoryController.WriteMemory(m_regs.sp, m_regs.pc >> 8);
									m_regs.sp--;
									m_bus.memoryController.WriteMemory(m_regs.sp, m_regs.pc & 0xFF);

									//Execute vector at 0x38
									m_regs.pc = Z80_INT_MODE2_ADDRESS;

									break;
								}
							case Z80_INT_MODE2:
								break;
						}

						//Clear IRQ
						m_regs.internal.irq = 0;
					}

					m_history[m_historyIdx++ % m_history.size()] = m_regs;

					//Clear prefix
					m_regs.internal.prefix1 = 0;
					m_regs.internal.prefix2 = 0;

					//Read and decode next instruction
					u8 opcodeIdx = m_bus.memoryController.ReadMemory(m_regs.pc++);

					//Get opcode
					const Opcode& opcode = OpcodeTable[opcodeIdx];

					//Read params
					OpcodeParams params;

#if defined DEBUG
					params.count = opcode.paramBytes;
#endif

					for (int i = 0; i < opcode.paramBytes; i++)
					{
						params[i] = m_bus.memoryController.ReadMemory(m_regs.pc++);
					}

					//Execute instruction
					opcode.handler(opcode, params, m_regs, m_bus);

					//TODO: cycle counts in table
					cycleCount = 8;
				}

				return cycleCount;
			}

			void Z80::TriggerInterrupt(Interrupts interrupt)
			{
				m_regs.internal.irq = 1;
			}

			const Registers& Z80::GetRegisters() const
			{
				return m_regs;
			}

			void Z80::GetPCHistory(std::vector<Registers>& history) const
			{
				history.resize(Z80_DEBUG_MAX_PC_HISTORY);

				for (int i = 0; i < Z80_DEBUG_MAX_PC_HISTORY; i++)
				{
					history[i] = m_history[(m_historyIdx + i) % Z80_DEBUG_MAX_PC_HISTORY];
				}
			}
		}
	}
}