#include "Mapper.h"

#include <ion/core/debug/Debug.h>
#include <ion/core/memory/Memory.h>

#include <functional>

namespace emu
{
	namespace memory
	{
		Mapper::Mapper(Controller& controller)
		{
			controller.AddHandler(0, SMS_MAPPER_START_ADDR - 1, std::bind(&Mapper::ReadVectors, this, std::placeholders::_1), std::bind(&Mapper::WriteError, this, std::placeholders::_1, std::placeholders::_2));
			controller.AddHandler((SMS_MAPPER_BANK_SIZE * 0), (SMS_MAPPER_BANK_SIZE * 1) - 1, std::bind(&Mapper::ReadBank0, this, std::placeholders::_1), std::bind(&Mapper::WriteError, this, std::placeholders::_1, std::placeholders::_2));
			controller.AddHandler((SMS_MAPPER_BANK_SIZE * 1), (SMS_MAPPER_BANK_SIZE * 2) - 1, std::bind(&Mapper::ReadBank1, this, std::placeholders::_1), std::bind(&Mapper::WriteError, this, std::placeholders::_1, std::placeholders::_2));
			controller.AddHandler((SMS_MAPPER_BANK_SIZE * 2), (SMS_MAPPER_BANK_SIZE * 3) - 1, std::bind(&Mapper::ReadBank2, this, std::placeholders::_1), std::bind(&Mapper::WriteError, this, std::placeholders::_1, std::placeholders::_2));
			controller.AddHandler(SMS_MAPPER_REG_STATE, SMS_MAPPER_REG_BANK2, std::bind(&Mapper::ReadRegister, this, std::placeholders::_1), std::bind(&Mapper::WriteRegister, this, std::placeholders::_1, std::placeholders::_2));

			for (int i = 0; i < SMS_MAPPER_NUM_REGS; i++)
			{
				m_registers[i] = 0;
			}
		}

		void Mapper::Initialise(const u8* data, u32 size)
		{
			m_rom.resize(size);
			ion::memory::MemCopy(m_rom.data(), data, size);

			//Map default banks
			if(size > SMS_MAPPER_BANK_SIZE * 0)
				m_mappedBank0 = &m_rom[SMS_MAPPER_BANK_SIZE * 0];
			if (size > SMS_MAPPER_BANK_SIZE * 1)
				m_mappedBank1 = &m_rom[SMS_MAPPER_BANK_SIZE * 1];
			if (size > SMS_MAPPER_BANK_SIZE * 2)
				m_mappedBank2 = &m_rom[SMS_MAPPER_BANK_SIZE * 2];
		}

		u8 Mapper::ReadVectors(u16 address)
		{
			return m_rom[address];
		}

		u8 Mapper::ReadBank0(u16 address)
		{
			return m_mappedBank0[address];
		}

		u8 Mapper::ReadBank1(u16 address)
		{
			return m_mappedBank1[address];
		}

		u8 Mapper::ReadBank2(u16 address)
		{
			return m_mappedBank2[address];
		}

		u8 Mapper::ReadRegister(u16 address)
		{
			return m_registers[address];
		}

		void Mapper::WriteRegister(u16 address, u8 value)
		{
			m_registers[address] = value;

			u16 reg = address + SMS_MAPPER_REG_STATE;

			switch (reg)
			{
			case SMS_MAPPER_REG_BANK0:
				m_mappedBank0 = &m_rom[value * SMS_MAPPER_BANK_SIZE];
				break;
			case SMS_MAPPER_REG_BANK1:
				m_mappedBank1 = &m_rom[value * SMS_MAPPER_BANK_SIZE];
				break;
			case SMS_MAPPER_REG_BANK2:
				m_mappedBank2 = &m_rom[value * SMS_MAPPER_BANK_SIZE];
				break;
			default:
				break;
			}
		}

		void Mapper::WriteError(u16 address, u8 value)
		{
#if defined ION_BUILD_DEBUG
			ion::debug::log << "Mapper::WriteError() - Write to read-only storage: " << address << " " << value << ion::debug::end;
#endif
		}
	}
}