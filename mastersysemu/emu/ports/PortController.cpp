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
			if (reader)
			{
				if (m_portReaders.size() <= address)
				{
					m_portReaders.resize(address + 1);
				}

				m_portReaders[address] = reader;
			}

			if (writer)
			{
				if (m_portWriters.size() <= address)
				{
					m_portWriters.resize(address + 1);
				}

				m_portWriters[address] = writer;
			}
		}

		u8 Controller::Read(u16 address)
		{
			if (OnRead* port = FindPortReader(address))
			{
				if (port)
				{
					return (*port)(address);
				}
			}

			ion::debug::log << "ports::Controller::Read() - Read from unknown port " << address << ion::debug::end;

			return 0;
		}

		void Controller::Write(u16 address, u8 value)
		{
			if (OnWrite* port = FindPortWriter(address))
			{
				if (port)
				{
					(*port)(address, value);
					return;
				}
				
			}
			
			ion::debug::log << "ports::Controller::Write() - Write to unknown port " << address << ion::debug::end;
		}

		OnRead* Controller::FindPortReader(u16 address)
		{
			if (address < m_portReaders.size() && m_portReaders[address])
			{
				return &m_portReaders[address];
			}

			return nullptr;
		}

		OnWrite* Controller::FindPortWriter(u16 address)
		{
			if (address < m_portWriters.size() && m_portWriters[address])
			{
				return &m_portWriters[address];
			}

			return nullptr;
		}
	}
}