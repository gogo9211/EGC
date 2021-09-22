#include "virtual_functions.hpp"

std::uintptr_t egc::virtual_functions::get_virtual_function(std::uintptr_t* obj, std::int16_t index)
{
	const auto vtable = *reinterpret_cast<std::uintptr_t**>(obj);

	return vtable[index];
}