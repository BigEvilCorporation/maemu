#pragma once

#include <ion/core/Types.h>

#include <functional>
#include <vector>

namespace emu
{
	namespace memory
	{
		typedef std::function<u8(u16 address)> OnRead;
		typedef std::function<void(u16 address, u8 value)> OnWrite;

		class Controller
		{
		public:
			Controller();

			void AddHandler(u16 mapStart, u16 mapEnd, OnRead const& reader, OnWrite const& writer);

			u8 ReadMemory(u16 address);
			void WriteMemory(u16 address, u8 value);

		private:
			struct MappedMemory
			{
				u16 mapStart;
				u16 mapEnd;
				OnRead reader;
				OnWrite writer;
			};

			MappedMemory* FindMappedArea(u16 address);
			MappedMemory* FindMappedArea(u16 mapStart, u16 mapEnd);

			std::vector<MappedMemory> m_memoryMap;
		};
	}
}