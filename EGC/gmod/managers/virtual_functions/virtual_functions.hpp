#pragma once
#include <Windows.h>
#include <iostream>

namespace egc
{
	namespace virtual_functions
	{
		std::uintptr_t get_virtual_function(std::uintptr_t* obj, std::int16_t index);

		namespace hook
		{
			template<typename def>
			def replace_vtable_function_pointer(std::uintptr_t* vtable, std::uint16_t index, std::uintptr_t new_pointer)
			{
				DWORD old_protection;

				VirtualProtect(&vtable[index], sizeof(std::uintptr_t), PAGE_EXECUTE_READWRITE, &old_protection);

				def old_func = reinterpret_cast<def>(vtable[index]);
				vtable[index] = new_pointer;

				VirtualProtect(&vtable[index], sizeof(std::uintptr_t), old_protection, &old_protection);
				return old_func;
			}
		}
	}
}