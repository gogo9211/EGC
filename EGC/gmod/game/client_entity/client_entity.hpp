#pragma once
#include <Windows.h>
#include <iostream>

#include "../../managers/virtual_functions/virtual_functions.hpp"

#include "../../utils/structs/vector.hpp"

#include "../../utils/structs/matrix.hpp"

namespace egc::game::client_entity
{
	struct collideable
	{
		virtual void* get_entity_handle() = 0;
		virtual const vector& obb_mins() = 0;
		virtual const vector& obb_maxs() = 0;
	};

	struct base_entity
	{
		__forceinline collideable* get_collideable()
		{
			auto func_addr = egc::virtual_functions::get_virtual_function(reinterpret_cast<std::uintptr_t*>(this), 3);
			return reinterpret_cast<collideable*(__thiscall*)(void*)>(func_addr)(this);
		}

		__forceinline vector get_origin()
		{
			return *reinterpret_cast<vector*>(reinterpret_cast<std::uintptr_t>(this) + 0x260); //DT_BaseEntity | m_vecAbsOrigin
		}

		__forceinline matrix3x4& get_rotation()
		{
			return *reinterpret_cast<matrix3x4*>(reinterpret_cast<std::uintptr_t>(this) + 0x308); //DT_BaseEntity | m_rgflCoordinateFrame
		}

		__forceinline std::uint32_t get_health()
		{
			return *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uintptr_t>(this) + 0x90); //DT_BaseEntity | m_iHealth
		}

		__forceinline std::uint32_t get_max_health()
		{
			return *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uintptr_t>(this) + 0x94); //DT_BaseEntity | m_iMaxHealth
		}

		__forceinline bool is_dormant()
		{
			return *reinterpret_cast<bool*>(reinterpret_cast<std::uintptr_t>(this) + 0x17E); //DT_BasePlayer | m_bDormant
		}
	};
}