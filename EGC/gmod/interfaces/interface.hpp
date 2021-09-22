#pragma once
#include <Windows.h>
#include <iostream>

#include "../game/lua_shared/lua_shared.hpp"

#include "../game/engine_client/engine_client.hpp"

#include "../game/surface/surface.hpp"

#include "../game/client_entity_list/client_entity_list.hpp"

namespace egc::interfaces
{
	void init();

	/*  Grabs interface by guessing the version, if you pass unexisting interface it returns 0, so we keep going until it return something else  */
	template<typename def>
	def get_interface(HMODULE mod, const char* const version)
	{
		for (auto i = 0u; i < 100; ++i)
		{
			char version_info[30];
			sprintf_s(version_info, "%s%03i", version, i);

			const auto result = reinterpret_cast<def(*)(const char* name, std::uint32_t* retc)>(GetProcAddress(mod, "CreateInterface"))(version_info, nullptr);

			if (result)
				return result;
		}

		return {};
	}

	/*  Grabs interface by hardcoding the versions, some interfaces have multiple versions so gussing it will return old version  */
	template<typename def>
	def get_interface_from_version(HMODULE mod, const char* const version)
	{
		return reinterpret_cast<def(*)(const char* name, std::uint32_t* retc)>(GetProcAddress(mod, "CreateInterface"))(version, nullptr);
	}

	namespace gmod
	{
		extern egc::game::lua::lua_shared* lua;
		extern egc::game::engine::engine_client* engine;
		extern egc::game::surface::system_surface* surface;
		extern egc::game::entity_list::client_entity_list* entity_list;
	}
}