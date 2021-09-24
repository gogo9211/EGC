#pragma once
#include <Windows.h>
#include <cstdint>
#include <string>

#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_impl_dx9.h"
#include "../imgui/imgui_internal.h"

using present_t = HRESULT(__stdcall*)(IDirect3DDevice9* device, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion);
using reset_t = HRESULT(__stdcall*)(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pPresentationParameters);

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

extern bool render_interface;

extern bool esp_enabled;
extern bool esp_draw_over_npcs;
extern bool esp_box;
extern bool esp_tracers;

namespace egc::renderer
{
	void init();

	int get_w();
	int get_h();
}

namespace discord_overlay::addresses
{
	constexpr std::uintptr_t present = 0x14E06C;

	constexpr std::uintptr_t reset = 0x14E0A8;
}