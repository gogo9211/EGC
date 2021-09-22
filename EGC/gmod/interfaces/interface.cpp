#include "interface.hpp"

egc::game::lua::lua_shared* egc::interfaces::gmod::lua;
egc::game::engine::engine_client* egc::interfaces::gmod::engine;
egc::game::surface::system_surface* egc::interfaces::gmod::surface;
egc::game::entity_list::client_entity_list* egc::interfaces::gmod::entity_list;

void egc::interfaces::init()
{
	const auto client_module = GetModuleHandleA("client.dll");
	const auto engine_module = GetModuleHandleA("engine.dll");
	const auto lua_shared_module = GetModuleHandleA("lua_shared.dll");
	const auto surface_module = GetModuleHandleA("vguimatsurface.dll");

	egc::interfaces::gmod::lua = get_interface<egc::game::lua::lua_shared*>(lua_shared_module, "LUASHARED");
	egc::interfaces::gmod::engine = get_interface<egc::game::engine::engine_client*>(engine_module, "VEngineClient");
	egc::interfaces::gmod::surface = get_interface<egc::game::surface::system_surface*>(surface_module, "VGUI_Surface");
	egc::interfaces::gmod::entity_list = get_interface<egc::game::entity_list::client_entity_list*>(client_module, "VClientEntityList");
}