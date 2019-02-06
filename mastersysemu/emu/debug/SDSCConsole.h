#pragma once

#include "../ports/PortController.h"

#include <ion/core/Types.h>

#include <string>

namespace emu
{
	namespace debug
	{
		class SDSCConsole
		{
		public:
			SDSCConsole(ports::Controller& portController);

			u8 Read(u16 address);
			void WriteControl(u16 address, u8 value);
			void WriteData(u16 address, u8 value);

			const std::string& GetBuffer() const { return m_buffer; }

		private:
			void Clear();

			enum Control
			{
				CTRL_NONE = 0,
				CTRL_BREAK = 1,
				CTRL_CLEAR = 2,
				CTRL_SET_ATTR = 3,
				CTRL_SET_ROW = 4,
				CTRL_SET_COL = 5,
			};

			std::string m_buffer;
			u8 m_controlByte;
			u8 m_attribute;
			u8 m_cursorX;
			u8 m_cursorY;
		};
	}
}