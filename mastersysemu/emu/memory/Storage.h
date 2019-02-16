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
			enum Flags
			{
				FLAGS_NONE = 0,
				FLAGS_READONLY = (1 << 0),
			};

			Storage(u16 mapStart, u16 mapEnd, Controller& controller, u32 flags = 0);

			void Initialise(const u8* data, u16 size);

			u8 Read(u16 address);
			void Write(u16 address, u8 value);
			void WriteError(u16 address, u8 value);

			//For debugging
			std::vector<u8>& GetMemory() { return m_memory; }
			u16 GetMappedAddress() { return m_mappedAddress; }

		private:
			std::vector<u8> m_memory;
			u16 m_mappedAddress;
			u32 m_flags;
		};
	}
}