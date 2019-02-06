#pragma once

#include "MemoryController.h"

#include <ion/core/Types.h>

#include <vector>

namespace emu
{
	namespace memory
	{
		class Storage
		{
		public:
			Storage(u16 mapStart, u16 mapEnd, Controller& controller);

			void Initialise(const u8* data, u16 size);

			u8 Read(u16 address);
			void Write(u16 address, u8 value);

			//For debugging
			std::vector<u8>& GetMemory() { return m_memory; }
			u16 GetMappedAddress() { return m_mappedAddress; }

		private:
			std::vector<u8> m_memory;
			u16 m_mappedAddress;
		};
	}
}