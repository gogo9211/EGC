#include "hooks.hpp"

#include "../managers/virtual_functions/virtual_functions.hpp"

#include "../interfaces/interface.hpp"

#include "../../rendering/renderer.hpp"

using lock_cursor_t = void(__thiscall*)(void* surface);
lock_cursor_t lock_cursor = nullptr;

void __fastcall lock_cursor_hook(void* surface, void* edx)
{
	if (render_interface)
	{
		egc::interfaces::gmod::surface->unlock_cursor();

		return;
	}

	lock_cursor(surface);
}

void egc::hooks::init()
{
	lock_cursor = egc::virtual_functions::hook::replace_vtable_function_pointer<lock_cursor_t>(*reinterpret_cast<std::uintptr_t**>(egc::interfaces::gmod::surface), 62, reinterpret_cast<std::uintptr_t>(lock_cursor_hook));
}