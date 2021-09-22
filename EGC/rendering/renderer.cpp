#include "renderer.hpp"
#include <mutex>

#include "../gmod/interfaces/interface.hpp"

#include "../gmod/features/executor/executor.hpp"

#include "../gmod/features/visuals/visuals.hpp"

#include "../imgui/TextEditor.h"


std::once_flag is_init;

bool render_interface = false;
bool window_selected = true;

std::uint32_t s_w, s_h;

WNDPROC original_wnd_proc;

present_t d3d9_present = nullptr;
reset_t d3d9_reset = nullptr;

TextEditor editor;

LRESULT __stdcall wnd_proc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (render_interface)
		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

	if (render_interface) ImGui::GetIO().MouseDrawCursor = true;
	else ImGui::GetIO().MouseDrawCursor = false;

	switch (uMsg)
	{
	case WM_KILLFOCUS:
		window_selected = false;
		break;

	case WM_SETFOCUS:
		window_selected = true;
		break;

	case WM_KEYDOWN:
		if (wParam == VK_INSERT) render_interface = !render_interface;
		break;
	}

	if (render_interface && window_selected)
		return TRUE;

	return CallWindowProcA(original_wnd_proc, hWnd, uMsg, wParam, lParam);
}

HRESULT __stdcall present_hook(IDirect3DDevice9* device, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
{
	std::call_once(is_init, [&]()
	{
		ImGui::CreateContext();
		ImGuiIO io = ImGui::GetIO();

		ImGui::SetNextWindowPos({ io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f }, ImGuiCond_Once, { 0.5f, 0.5f });
		ImGui_ImplWin32_Init(FindWindowA(nullptr, "Garry's Mod"));
		ImGui_ImplDX9_Init(device);

		const auto lang = TextEditor::LanguageDefinition::LuaLexer;

		editor.SetLanguageDefinition(lang());

		editor.SetShowWhitespaces(false);
	});

	DWORD colorwrite, srgbwrite;

	device->GetRenderState(D3DRS_COLORWRITEENABLE, &colorwrite);
	device->GetRenderState(D3DRS_SRGBWRITEENABLE, &srgbwrite);

	device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);
	device->SetRenderState(D3DRS_SRGBWRITEENABLE, false);

	ImGuiIO io = ImGui::GetIO();

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();

	egc::features::visuals::callback();

	if (render_interface)
	{
		if (ImGui::Begin("EGC", reinterpret_cast<bool*>(0), ImGuiWindowFlags_NoCollapse))
		{
			editor.Render("ScriptBox", { 300.f, 200.f });

			ImGui::Spacing();

			if (ImGui::Button("Execute", { 70, 20 }))
				egc::features::executor::execute(editor.GetText());

			ImGui::SameLine();

			if (ImGui::Button("Clear", { 70, 20 }))
				editor.SetText("");
		}

		ImGui::End();
	}

	ImGui::EndFrame();
	ImGui::Render();

	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	device->SetRenderState(D3DRS_COLORWRITEENABLE, colorwrite);
	device->SetRenderState(D3DRS_SRGBWRITEENABLE, srgbwrite);

	return d3d9_present(device, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

HRESULT __stdcall reset_hook(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	ImGui_ImplDX9_InvalidateDeviceObjects();

	HRESULT ret = d3d9_reset(device, pPresentationParameters);

	ImGui_ImplDX9_CreateDeviceObjects();

	egc::interfaces::gmod::engine->get_screen_size(s_w, s_h);

	return ret;
}

void egc::renderer::init()
{
	const std::uintptr_t base_address = reinterpret_cast<std::uintptr_t>(GetModuleHandleA("DiscordHook.dll"));

	if (base_address)
	{
		const std::uintptr_t present_address = base_address + discord_overlay::addresses::present;
		const std::uintptr_t reset_address = base_address + discord_overlay::addresses::reset;

		egc::interfaces::gmod::engine->get_screen_size(s_w, s_h);

		original_wnd_proc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(FindWindowA(nullptr, "Garry's Mod"), GWL_WNDPROC, reinterpret_cast<LONG_PTR>(wnd_proc)));

		d3d9_present = *reinterpret_cast<decltype(d3d9_present)*>(present_address);
		d3d9_reset = *reinterpret_cast<decltype(d3d9_reset)*>(reset_address);

		*reinterpret_cast<void**>(present_address) = reinterpret_cast<void*>(&present_hook);
		*reinterpret_cast<void**>(reset_address) = reinterpret_cast<void*>(&reset_hook);
	
		std::printf("[+] Discord Overlay Hijacked!\n\n");
	}
	else
	{
		std::printf("[+] Renderer Failed!\n\n");
	}
}

int egc::renderer::get_w()
{
	return s_w;
}

int egc::renderer::get_h()
{
	return s_h;
}