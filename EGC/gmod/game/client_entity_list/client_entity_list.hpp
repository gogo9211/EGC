#pragma once
#include <Windows.h>
#include <iostream>

#include "../../managers/virtual_functions/virtual_functions.hpp"

#include "../client_entity/client_entity.hpp"

namespace egc::game::entity_list
{
	struct client_entity_list
	{
		egc::game::client_entity::base_entity* get_client_entity(std::uint16_t entity_number)
		{
			auto func_addr = egc::virtual_functions::get_virtual_function(reinterpret_cast<std::uintptr_t*>(this), 3);
			return reinterpret_cast<egc::game::client_entity::base_entity*(__thiscall*)(void*, std::uint16_t)>(func_addr)(this, entity_number);
		}
	};
}