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

	enum class class_ids : std::uint8_t
	{
		gmod_player = 70,
		base_npc = 1
	};

	struct client_class
	{
		std::uintptr_t create_fn;
		std::uintptr_t create_event_fn;
		std::uintptr_t network_name;
		std::uintptr_t recv_table;
		client_class* next_class;
		class_ids class_id;
	};

	struct base_entity
	{
		//8 = IClientNetworkable
	    //4 = IClientRenderable
	    //0 = C_Base* 

		__forceinline collideable* get_collideable()
		{
			auto func_addr = egc::virtual_functions::get_virtual_function(reinterpret_cast<std::uintptr_t*>(this), 3);
			return reinterpret_cast<collideable*(__thiscall*)(void*)>(func_addr)(this);
		}

		__forceinline client_class* get_client_class()
		{
			auto func_addr = egc::virtual_functions::get_virtual_function(reinterpret_cast<std::uintptr_t*>(this + 8), 2);
			return reinterpret_cast<client_class*(__thiscall*)(void*)>(func_addr)(this + 8);
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