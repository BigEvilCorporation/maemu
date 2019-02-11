#include "Z80.h"
#include "Constants.h"

#include <ion/core/debug/Debug.h>

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
			}

			void Z80::Reset()
			{
				//Guaranteed initial reg values - all others undefined
				m_regs.pc = 0x0000;
				m_regs.sp = 0xFFFF;
				m_regs.main.af = 0xFFFF;
			}

			void Z80::Step()
			{
				//Read and decode next instruction
				u8 opcodeIdx = m_bus.memoryController.ReadMemory(m_regs.pc++);

				//Get opcode
				const Opcode& opcode = OpcodeTable[opcodeIdx];

				//Read params
				OpcodeParams params;

				for (int i = 0; i < opcode.paramBytes; i++)
				{
					params[i] = m_bus.memoryController.ReadMemory(m_regs.pc++);
				}

				//Execute instruction
				opcode.handler(opcode, params, m_regs, m_bus);
			}

			const Registers& Z80::GetRegisters() const
			{
				return m_regs;
			}
		}
	}
}