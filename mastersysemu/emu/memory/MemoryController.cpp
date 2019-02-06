#include "MemoryController.h"

#include <ion/core/debug/Debug.h>

namespace emu
{
	namespace memory
	{
		Controller::Controller()
		{

		}

		void Controller::AddHandler(u16 mapStart, u16 mapEnd, OnRead const& reader, OnWrite const& writer)
		{
			ion::debug::Assert(!FindMappedArea(mapStart, mapEnd), "Controller::AddHandler() - Memory in this range already mapped");

			MappedMemory area =
			{
				mapStart,
				mapEnd,
				reader,
				writer
			};

			//TODO: Insert sorted
			m_memoryMap.push_back(area);
		}

		u8 Controller::ReadMemory(u16 address)
		{
			if (MappedMemory* area = FindMappedArea(address))
			{
				return area->reader(address - area->mapStart);
			}
			else
			{
				ion::debug::log << "Controller::ReadMemory() Could not read from unmapped address: " << address << ion::debug::end;
			}

			return 0;
		}

		void Controller::WriteMemory(u16 address, u8 value)
		{
			if (MappedMemory* area = FindMappedArea(address))
			{
				area->writer(address - area->mapStart, value);
			}
			else
			{
				ion::debug::log << "Controller::ReadMemory() Could not write to unmapped address: " << address << ion::debug::end;
			}
		}

		Controller::MappedMemory* Controller::FindMappedArea(u16 address)
		{
			for (int i = 0; i < m_memoryMap.size(); i++)
			{
				MappedMemory& area = m_memoryMap[i];

				if (address >= area.mapStart && address < area.mapEnd)
				{
					return &area;
				}
			}

			return nullptr;
		}

		Controller::MappedMemory* Controller::FindMappedArea(u16 mapStart, u16 mapEnd)
		{
			//TODO
			return nullptr;
		}
	}
}