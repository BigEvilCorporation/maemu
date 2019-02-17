#include "SDSCConsole.h"

#include "../Constants.h"

#include <ion/core/debug/Debug.h>
#include <ion/maths/Maths.h>

namespace emu
{
	namespace debug
	{
		SDSCConsole::SDSCConsole(ports::Controller& portController)
		{
			m_controlByte = 0;
			m_attribute = 0;
			m_cursorX = 0;
			m_cursorY = 0;

			//Connect ports
			portController.AddHandler(PORT_SDSC_CTRL, std::bind(&SDSCConsole::Read, this, std::placeholders::_1), std::bind(&SDSCConsole::WriteControl, this, std::placeholders::_1, std::placeholders::_2));
			portController.AddHandler(PORT_SDSC_DATA, std::bind(&SDSCConsole::Read, this, std::placeholders::_1), std::bind(&SDSCConsole::WriteData, this, std::placeholders::_1, std::placeholders::_2));

			Clear();
		}

		void SDSCConsole::Clear()
		{
			m_buffer.clear();
			//m_buffer.resize(SDSC_CONSOLE_WIDTH * SDSC_CONSOLE_HEIGHT);
			//
			////Fill with spaces, rather than 0
			//for (int i = 0; i < m_buffer.size(); i++)
			//{
			//	m_buffer[i] = ' ';
			//}
		}

		u8 SDSCConsole::Read(u16 address)
		{
			//Console is write only
			ion::debug::Log("SDSCConsole::Read() - Attempted to read from SDSC console");
			return 0;
		}

		void SDSCConsole::WriteControl(u16 address, u8 value)
		{
			switch (value)
			{
				//Immediate control actions
				case CTRL_BREAK:
				{
					//TODO: Break emulator
				}
				case CTRL_CLEAR:
				{
					//Clear text
					Clear();
				}

				//Subsequent control actions
				default:
				{
					switch (m_controlByte)
					{
						case CTRL_SET_ATTR:
						{
							//Value is attribute
							m_attribute = value;

							//Done setting attr
							value = CTRL_NONE;
						}
						case CTRL_SET_ROW:
						{
							//Value is row
							m_cursorY = ion::maths::Clamp(value, 0, SDSC_CONSOLE_HEIGHT);

							//Expecting col value next
							value = CTRL_SET_COL;
						}
						case CTRL_SET_COL:
						{
							//Value is col
							m_cursorX = ion::maths::Clamp(value, 0, SDSC_CONSOLE_WIDTH);

							//Done setting row/col
							value = CTRL_NONE;
						}
					}
				}
			}

			m_controlByte = value;
		}

		void SDSCConsole::WriteData(u16 address, u8 value)
		{
			if (value < 10)
			{
				value += '0';
			}

			m_buffer.push_back(value);

			/*
			if (value == '\n')
			{
				m_cursorX = SDSC_CONSOLE_WIDTH;
			}
			else
			{
				//Write to buffer
				m_buffer[(m_cursorY * SDSC_CONSOLE_WIDTH) + m_cursorX] = value;

				//Next X
				m_cursorX++;
			}

			if (m_cursorX == SDSC_CONSOLE_WIDTH)
			{
				//Next Y
				m_cursorX = 0;
				m_cursorY++;

				if (m_cursorY == SDSC_CONSOLE_HEIGHT)
				{
					//TODO: Scroll up
					m_cursorY = SDSC_CONSOLE_HEIGHT - 1;
				}
			}
			*/
		}
	}
}