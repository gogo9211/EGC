#include <Windows.h>
#include <thread>

#include "gmod/interfaces/interface.hpp"

#include "gmod/hooks/hooks.hpp"

#include "rendering/renderer.hpp"

void main_d()
{
    AllocConsole();
    FILE* file_stream;

    freopen_s(&file_stream, "CONIN$", "r", stdin);
    freopen_s(&file_stream, "CONOUT$", "w", stdout);
    freopen_s(&file_stream, "CONOUT$", "w", stderr);

    SetConsoleTitleA("EGC");

    egc::interfaces::init();
    egc::renderer::init();
    egc::hooks::init();

    std::printf
    (
        "[+] Lua Shared: 0x%p\n"
        "[+] Engine: 0x%p\n"
        "[+] Surface: 0x%p\n"
        "[+] Entity List: 0x%p\n"
        "[+] Screen Size: %i | %i\n",

        egc::interfaces::gmod::lua,
        egc::interfaces::gmod::engine,
        egc::interfaces::gmod::surface,
        egc::interfaces::gmod::entity_list,
        egc::renderer::get_h(),
        egc::renderer::get_w()
    );
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        std::thread{ main_d }.detach();

    return TRUE;
}