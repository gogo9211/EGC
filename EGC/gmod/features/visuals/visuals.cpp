#include "visuals.hpp"

#include "../../interfaces/interface.hpp"

#include "../../../rendering/renderer.hpp"

#include "../../utils/math/math.hpp"

void egc::features::visuals::callback()
{
	if (egc::interfaces::gmod::engine->is_in_game())
	{
		std::uint32_t w, h;

		w = egc::renderer::get_w();
		h = egc::renderer::get_h();

		ImDrawList* draw_list = ImGui::GetBackgroundDrawList();

		for (auto i = 0u; i < egc::interfaces::gmod::engine->get_max_clients(); ++i)
		{
			const auto entity = egc::interfaces::gmod::entity_list->get_client_entity(i);

			if (!entity || entity->is_dormant())
				continue;

			const auto entity_position = entity->get_origin();

			vector entity_screen_position;

			if (egc::math::world_to_screen(entity_position, entity_screen_position))
				draw_list->AddLine({ static_cast<float>(w) / 2, static_cast<float>(h) }, { entity_screen_position.x, entity_screen_position.y }, ImColor(0, 255, 0));
		}
	}
}