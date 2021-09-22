#pragma once
#include "vector.hpp"
class matrix3x4 {
	float mat[3][4];
public:
	constexpr auto operator[](int i) const noexcept { return mat[i]; }
	vector origin() const noexcept {
		return vector(mat[0][3], mat[1][3], mat[2][3]);
	}
};