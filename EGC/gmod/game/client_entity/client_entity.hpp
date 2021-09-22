#pragma once
#include <Windows.h>
#include <iostream>

#include "../../managers/virtual_functions/virtual_functions.hpp"

#include "../../utils/structs/vector.hpp"

namespace egc::game::client_entity
{
	struct base_entity
	{
		__forceinline vector get_origin()
		{
			return *reinterpret_cast<vector*>(reinterpret_cast<std::uintptr_t>(this) + 0x260); //DT_BaseEntity | m_vecAbsOrigin
		}

		__forceinline bool is_dormant()
		{
			return *reinterpret_cast<bool*>(reinterpret_cast<std::uintptr_t>(this) + 0x17E); //DT_BasePlayer | m_bDormant
		}
	};
}