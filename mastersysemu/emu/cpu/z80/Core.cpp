#include "Core.h"
#include "Constants.h"

#include <ion/core/debug/Debug.h>

namespace emu
{
	namespace cpu
	{
		namespace z80
		{
			Core::Core(Bus& bus)
				: m_bus(bus)
			{
				Reset();
			}

			void Core::Reset()
			{
				m_regs.pc = 0x0000;
				m_regs.sp = 0x0000;
				m_regs.main.f = 0x00;
			}

			void Core::Step()
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

			const Registers& Core::GetRegisters() const
			{
				return m_regs;
			}
		}
	}
}