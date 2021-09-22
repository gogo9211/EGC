#pragma once
#include <Windows.h>
#include <iostream>

#include "../structs/vector.hpp"

namespace egc::math
{
	bool world_to_screen(vector in, vector& out);
}