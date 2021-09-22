#pragma once
#include <Windows.h>
#include <iostream>

#include "../../managers/virtual_functions/virtual_functions.hpp"

namespace egc::game::surface
{
	struct system_surface
	{
		void unlock_cursor()
		{
			auto func_addr = egc::virtual_functions::get_virtual_function(reinterpret_cast<std::uintptr_t*>(this), 61);
			return reinterpret_cast<void(__thiscall*)(void*)>(func_addr)(this);
		}
	};
}