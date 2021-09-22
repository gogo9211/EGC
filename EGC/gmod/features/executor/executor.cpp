#include "executor.hpp"

#include "../../interfaces/interface.hpp"

void egc::features::executor::execute(std::string script)
{
	const auto lua_interface = egc::interfaces::gmod::lua->get_active_lua_interface();

	if (!lua_interface)
		std::printf("[+] Execution Error!\n");

	lua_interface->run_string(".egc", "", script.c_str(), true, true);
}