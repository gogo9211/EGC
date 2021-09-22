#pragma once
#include <math.h>
#include <algorithm>

class vector
{
public:
	float x;
	float y;
	float z;

	vector() { x = 0; y = 0; z = 0; }
	vector(float ix, float iy, float iz) { x = ix; y = iy; z = iz; }

	void Clamp()
	{
		x = std::clamp(remainderf(x, 360.0f), -89.0f, 89.0f);
		y = std::clamp(remainderf(y, 360.0f), -180.0f, 180.0f);
	}

	auto Clamped() {
		vector tmp = *this;
		tmp.Clamp();
		return tmp;
	}

	void Normalize()
	{
		if (x > 180)
			x -= 360.0f;
		if (x < 180)
			x += 360.0f;
		if (y > 180)
			y -= 360.0f;
		if (y < 180)
			y += 360.0f;
	}

	vector Normalized() {
		vector tmp = *this;
		tmp.Normalize();
		return tmp;
	}

	vector operator-(vector angle)
	{
		return vector(x - angle.x, y - angle.y, z - angle.z);
	}

	vector operator+(vector angle)
	{
		return vector(x + angle.x, y + angle.y, z + angle.z);
	}

	vector operator*(float f)
	{
		return vector(x * f, y * f, z * f);
	}

	vector operator/(vector angle)
	{
		return vector(x / angle.x, y / angle.y, z / angle.z);
	}

	vector operator/(const float& f)
	{
		return vector(x / f, y / f, z / f);
	}

	vector operator/=(float& f)
	{
		return vector(x / f, y / f, z / f);
	}

	bool operator==(vector v)
	{
		return (v.x == x && v.y == y && v.z == z);
	}

	bool operator!=(vector v)
	{
		return(v.x != x || v.y != y || v.z != z);
	}

	friend vector operator* (float lhs, vector rhs) {
		return rhs * lhs;
	}


	bool IsNan()
	{
		if (isnan(x) || isnan(y) || isnan(z))
			return true;

		return false;
	}

	auto LengthSqr() const {
		return (x * x + y * y + z * z);
	}

	auto Length2DSqr() const {
		return (x * x + y * y);
	}

	auto Length() const {
		return sqrt(LengthSqr());
	}

	auto Length2D() const {
		return sqrt(Length2DSqr());
	}

	constexpr auto notNull() const noexcept
	{
		return x || y || z;
	}

	bool isNull()
	{
		return (x < 1 && y < 1 && z < 1);
	}

	vector ToRGB(vector& in)
	{
		return in = in * 255;
	}

	vector ToDRGB(vector& in)
	{
		return in = in / 255;
	}

	vector FloatToColor(float* color)
	{
		return vector(color[0], color[1], color[2]);
	}

	float dot_product(const vector& vec)
	{
		return (this->x * vec.x + this->y * vec.y + this->z * vec.z);
	}
};
