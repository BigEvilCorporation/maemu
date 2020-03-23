#include "Storage.h"

#include <ion/core/debug/Debug.h>
#include <ion/core/memory/Memory.h>

#include <functional>

namespace emu
{
	namespace memory
	{
		Storage::Storage(u16 mapStart, u16 mapEnd, Controller& controller, u32 flags)
			: m_mappedAddress(mapStart)
			, m_flags(flags)
		{
			m_memory.resize(mapEnd - mapStart);
			controller.AddHandler(mapStart, mapEnd, std::bind(&Storage::Read, this, std::placeholders::_1), std::bind((flags & FLAGS_READONLY) ? &Storage::WriteError : &Storage::Write, this, std::placeholders::_1, std::placeholders::_2));
		}

		void Storage::Initialise(const u8* data, u16 size)
		{
			ion::debug::Assert(size < m_memory.size(), "Storage::Initialise() - Buffer overflow");
			ion::memory::MemCopy(m_memory.data(), data, size);
		}

		u8 Storage::Read(u16 address)
		{
			return m_memory[address];
		}

		void Storage::Write(u16 address, u8 value)
		{
			m_memory[address] = value;
		}

		void Storage::WriteError(u16 address, u8 value)
		{
#if defined ION_BUILD_DEBUG
			ion::debug::log << "Write to read-only storage: " << address << " " << value << ion::debug::end;
#endif
		}
	}
}