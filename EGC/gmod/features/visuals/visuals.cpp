#include "visuals.hpp"

#include "../../interfaces/interface.hpp"

#include "../../../rendering/renderer.hpp"

#include "../../utils/math/math.hpp"

#include <vector>

void draw_esp(egc::game::client_entity::base_entity* plr)
{
	std::uint32_t w, h;

	w = egc::renderer::get_w();
	h = egc::renderer::get_h();

	matrix3x4& rotations = plr->get_rotation();

	egc::game::client_entity::collideable* collision = plr->get_collideable();

	vector obb_mins = collision->obb_mins();
	vector obb_maxs = collision->obb_maxs();

	const std::vector<vector> body_points = { vector(obb_mins.x, obb_mins.y, obb_mins.z), vector(obb_mins.x, obb_maxs.y, obb_mins.z), vector(obb_maxs.x, obb_maxs.y, obb_mins.z), vector(obb_maxs.x, obb_mins.y, obb_mins.z), vector(obb_maxs.x, obb_maxs.y, obb_maxs.z), vector(obb_mins.x, obb_maxs.y, obb_maxs.z), vector(obb_mins.x, obb_mins.y, obb_maxs.z), vector(obb_maxs.x, obb_mins.y, obb_maxs.z) };

	vector points[8];
	for (auto i = 0u; i < 8; ++i)
	{
		for (int j{ }; j < 3; j++)
			points[i][j] = (body_points[i].x * rotations[j][0] + body_points[i].y * rotations[j][1] + body_points[i].z * rotations[j][2]) + rotations[j][3];
	}

	vector flb, brt, blb, frt, frb, brb, blt, flt;

	if (!egc::math::world_to_screen(points[3], flb) || !egc::math::world_to_screen(points[5], brt) || !egc::math::world_to_screen(points[0], blb) || !egc::math::world_to_screen(points[4], frt) || !egc::math::world_to_screen(points[2], frb) || !egc::math::world_to_screen(points[1], brb) || !egc::math::world_to_screen(points[6], blt) || !egc::math::world_to_screen(points[7], flt))
		return;

	const std::vector<vector> pts = { flb, brt, blb, frt, frb, brb, blt, flt };

	float left = flb.x;
	float top = flb.y;
	float right = flb.x;
	float bottom = flb.y;

	for (auto i = 1u; i < 8; ++i)
	{
		if (left > pts[i].x)
			left = pts[i].x;

		if (top < pts[i].y)
			top = pts[i].y;

		if (right < pts[i].x)
			right = pts[i].x;

		if (bottom > pts[i].y)
			bottom = pts[i].y;
	}

	auto dl = ImGui::GetBackgroundDrawList();

	if (esp_box)
	{
		dl->AddLine({ left, bottom }, { left, top }, ImColor(0, 255, 0));
		dl->AddLine({ left, top }, { right, top }, ImColor(0, 255, 0));
		dl->AddLine({ right, top }, { right, bottom }, ImColor(0, 255, 0));
		dl->AddLine({ right, bottom }, { left, bottom }, ImColor(0, 255, 0));
	}

	if (esp_tracers)
		dl->AddLine({ w / 2.0f, static_cast<float>(h) }, { (left + right) / 2, top }, ImColor(0, 255, 0));
}

void egc::features::visuals::callback()
{
	if (egc::interfaces::gmod::engine->is_in_game())
	{
		ImDrawList* draw_list = ImGui::GetBackgroundDrawList();

		for (auto i = 0u; i < egc::interfaces::gmod::engine->get_max_clients(); ++i)
		{
			const auto entity = egc::interfaces::gmod::entity_list->get_client_entity(i);

			if (!entity || entity->is_dormant())
				continue;

			if (esp_enabled && entity->get_health() > 0)
				draw_esp(entity);
		}
	}
}