#pragma once

#include <ion/core/Types.h>

#include <functional>
#include <vector>

namespace emu
{
	namespace ports
	{
		typedef std::function<u8(u16 address)> OnRead;
		typedef std::function<void(u16 address, u8 value)> OnWrite;

		class Controller
		{
		public:
			Controller();

			void AddHandler(u16 address, OnRead const& reader, OnWrite const& writer);

			u8 Read(u16 address);
			void Write(u16 address, u8 value);

		private:
			struct MappedPort
			{
				OnRead reader;
				OnWrite writer;
			};

			MappedPort* FindPort(u16 address);

			std::vector<MappedPort> m_portMap;
		};
	}
}