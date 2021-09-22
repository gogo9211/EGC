#pragma once
#include <Windows.h>
#include <iostream>

#include "../../managers/virtual_functions/virtual_functions.hpp"

#include "../../utils/structs/matrix.hpp"

namespace egc::game::engine
{
	struct engine_client
	{
		void get_screen_size(std::uint32_t& width, std::uint32_t& height)
		{
			auto func_addr = egc::virtual_functions::get_virtual_function(reinterpret_cast<std::uintptr_t*>(this), 5);
			return reinterpret_cast<void(__thiscall*)(void*, std::uint32_t&, std::uint32_t&)>(func_addr)(this, width, height);
		}

		bool is_in_game()
		{
			auto func_addr = egc::virtual_functions::get_virtual_function(reinterpret_cast<std::uintptr_t*>(this), 26);
			return reinterpret_cast<bool(__thiscall*)(void*)>(func_addr)(this);
		}

		std::uint32_t get_max_clients()
		{
			auto func_addr = egc::virtual_functions::get_virtual_function(reinterpret_cast<std::uintptr_t*>(this), 21);
			return reinterpret_cast<std::uint32_t(__thiscall*)(void*)>(func_addr)(this);
		}

		matrix3x4& get_view_matrix()
		{
			auto func_addr = egc::virtual_functions::get_virtual_function(reinterpret_cast<std::uintptr_t*>(this), 36);
			return reinterpret_cast<matrix3x4&(__thiscall*)(void*)>(func_addr)(this);
		}
	};
}