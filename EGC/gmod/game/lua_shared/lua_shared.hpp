#pragma once
#include <Windows.h>
#include <iostream>

#include "../../managers/virtual_functions/virtual_functions.hpp"

namespace egc::game::lua
{
	enum class state_t : std::uint8_t
	{
		client = 0,
		server = 1,
		menu = 2
	};

	struct lua_interface
	{
		void run_string(const char* name, const char* path, const char* script, bool run, bool errors)
		{
			auto func_addr = egc::virtual_functions::get_virtual_function(reinterpret_cast<std::uintptr_t*>(this), 111);
			return reinterpret_cast<void(__thiscall*)(void*, const char*, const char*, const char*, bool, bool, bool, bool)>(func_addr)(this, name, path, script, run, errors, true, true);
		}
	};

	struct lua_shared
	{
		lua_interface* get_lua_interface(state_t state)
		{
			auto func_addr = egc::virtual_functions::get_virtual_function(reinterpret_cast<std::uintptr_t*>(this), 6);
			return reinterpret_cast<lua_interface*(__thiscall*)(void*, state_t)>(func_addr)(this, state);
		}

		lua_interface* get_active_lua_interface()
		{
			auto ret = get_lua_interface(state_t::client);

			if (!ret)
				ret = get_lua_interface(state_t::menu);

			return ret;
		}
	};
}