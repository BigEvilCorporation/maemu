#include "PortController.h"

#include <ion/core/debug/Debug.h>

namespace emu
{
	namespace ports
	{
		Controller::Controller()
		{

		}

		void Controller::AddHandler(u16 address, OnRead const& reader, OnWrite const& writer)
		{
			if (m_portMap.size() <= address)
			{
				m_portMap.resize(address + 1);
			}

			m_portMap[address] = { reader, writer };
		}

		u8 Controller::Read(u16 address)
		{
			if (MappedPort* port = FindPort(address))
			{
				if (port->reader)
				{
					return port->reader(address);
				}
			}

			ion::debug::log << "ports::Controller::Read() - Read from unknown port " << address << ion::debug::end;

			return 0;
		}

		void Controller::Write(u16 address, u8 value)
		{
			if (MappedPort* port = FindPort(address))
			{
				if (port->writer)
				{
					port->writer(address, value);
					return;
				}
				
			}
			
			ion::debug::log << "ports::Controller::Write() - Write to unknown port " << address << ion::debug::end;
		}

		Controller::MappedPort* Controller::FindPort(u16 address)
		{
			if (address < m_portMap.size())
			{
				return &m_portMap[address];
			}

			return nullptr;
		}
	}
}