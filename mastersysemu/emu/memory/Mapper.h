#pragma once

#include "../Constants.h"
#include "MemoryController.h"

#include <ion/core/Types.h>

#include <vector>

namespace emu
{
	namespace memory
	{
		class Mapper
		{
		public:
			Mapper(Controller& controller);

			void Initialise(const u8* data, u32 size);

			u8 ReadVectors(u16 address);
			u8 ReadBank0(u16 address);
			u8 ReadBank1(u16 address);
			u8 ReadBank2(u16 address);
			u8 ReadRegister(u16 address);

			void WriteRegister(u16 address, u8 value);
			void WriteError(u16 address, u8 value);

			//For debugging
			std::vector<u8>& GetMemory() { return m_rom; }

		private:
			std::vector<u8> m_rom;
			u8* m_mappedBank0;
			u8* m_mappedBank1;
			u8* m_mappedBank2;
			u8 m_registers[MAPPER_NUM_REGS];
		};
	}
}