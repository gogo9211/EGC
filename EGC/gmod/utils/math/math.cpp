#include "math.hpp"

#include "../structs/matrix.hpp"

#include "../../interfaces/interface.hpp"

#include "../../../rendering/renderer.hpp"

bool screen_transform(vector in, vector& out)
{
	const auto& matrix = egc::interfaces::gmod::engine->get_view_matrix();

	out.x = matrix[0][0] * in.x + matrix[0][1] * in.y + matrix[0][2] * in.z + matrix[0][3];
	out.y = matrix[1][0] * in.x + matrix[1][1] * in.y + matrix[1][2] * in.z + matrix[1][3];
	out.z = 0.0f;

	float w = matrix[3][0] * in.x + matrix[3][1] * in.y + matrix[3][2] * in.z + matrix[3][3];

	if (w < 0.001f)
	{
		out.x *= 100000;
		out.y *= 100000;

		return false;
	}

	out.x /= w;
	out.y /= w;

	return true;
}


bool egc::math::world_to_screen(vector in, vector& out)
{
	std::uint32_t w, h;

	w = egc::renderer::get_w();
	h = egc::renderer::get_h();

	if (screen_transform(in, out))
	{
		out.x = (w / 2.0f) + (out.x * w) / 2.0f;
		out.y = (h / 2.0f) - (out.y * h) / 2.0f;

		if (out.x > w || out.y > h || out.x < 0.f || out.y < 0.f)
			return false;

		return true;
	}

	return false;
}