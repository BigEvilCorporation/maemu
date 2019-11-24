#pragma once

#include "Constants.h"
#include "Registers.h"
#include "opcodes/tables/OpcodeTable.h"
#include "Bus.h"

namespace emu
{
	namespace cpu
	{
		namespace z80
		{
			class Z80
			{
			public:
				Z80(Bus& bus);

				//Execution
				void Reset();
				u32 StepInstruction();

				//Interrupts
				void TriggerInterrupt(Interrupts interrupt);

				//Debugging
				const Registers& GetRegisters() const;
				void GetPCHistory(std::vector<Registers>& history) const;

			private:
				Registers m_regs;
				Bus& m_bus;

				std::vector<Registers> m_history;
				u32 m_historyIdx;
			};
		}
	}
}