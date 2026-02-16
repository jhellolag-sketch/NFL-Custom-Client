#pragma once

#include <Windows.h>
#include <d3d11.h>
#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>
#include "../core/hooks.h"
#include "../utils/logger.h"

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace UI {

class Overlay {
private:
    bool initialized = false;
    bool showMenu = false;
    HWND gameWindow = nullptr;
    WNDPROC oWndProc = nullptr;

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        auto& overlay = GetInstance();
        
        if (overlay.showMenu && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
            return true;

        return CallWindowProc(overlay.oWndProc, hWnd, uMsg, wParam, lParam);
    }

public:
    static Overlay& GetInstance() {
        static Overlay instance;
        return instance;
    }

    bool Initialize(IDXGISwapChain* pSwapChain) {
        if (initialized) return true;

        Logger::Log("[Overlay] Initializing ImGui overlay...");

        // Get device and context from swap chain
        if (FAILED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&Hooks::g_pd3dDevice))) {
            Logger::Log("[Overlay] Failed to get D3D11 device", Logger::ERROR);
            return false;
        }

        Hooks::g_pd3dDevice->GetImmediateContext(&Hooks::g_pd3dDeviceContext);
        Hooks::g_pSwapChain = pSwapChain;

        // Get game window
        DXGI_SWAP_CHAIN_DESC sd;
        pSwapChain->GetDesc(&sd);
        gameWindow = sd.OutputWindow;

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.IniFilename = nullptr; // Disable imgui.ini

        // Setup ImGui style
        SetupStyle();

        // Setup Platform/Renderer backends
        ImGui_ImplWin32_Init(gameWindow);
        ImGui_ImplDX11_Init(Hooks::g_pd3dDevice, Hooks::g_pd3dDeviceContext);

        // Hook window procedure for input
        oWndProc = (WNDPROC)SetWindowLongPtr(gameWindow, GWLP_WNDPROC, (LONG_PTR)WndProc);

        initialized = true;
        Logger::Log("[Overlay] ImGui overlay initialized successfully");
        return true;
    }

    void Shutdown() {
        if (!initialized) return;

        Logger::Log("[Overlay] Shutting down ImGui overlay...");

        // Restore original window procedure
        if (oWndProc && gameWindow) {
            SetWindowLongPtr(gameWindow, GWLP_WNDPROC, (LONG_PTR)oWndProc);
        }

        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();

        if (Hooks::g_pd3dDeviceContext) {
            Hooks::g_pd3dDeviceContext->Release();
            Hooks::g_pd3dDeviceContext = nullptr;
        }

        if (Hooks::g_pd3dDevice) {
            Hooks::g_pd3dDevice->Release();
            Hooks::g_pd3dDevice = nullptr;
        }

        initialized = false;
        Logger::Log("[Overlay] ImGui overlay shut down");
    }

    void Render() {
        if (!initialized) return;

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        if (showMenu) {
            RenderMenu();
        }

        RenderOverlays();

        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    }

    void ToggleMenu() {
        showMenu = !showMenu;
        
        ImGuiIO& io = ImGui::GetIO();
        if (showMenu) {
            io.MouseDrawCursor = true;
        } else {
            io.MouseDrawCursor = false;
        }
    }

    bool IsMenuVisible() const {
        return showMenu;
    }

    void HandleResize() {
        if (!initialized) return;
        
        Logger::Log("[Overlay] Handling resize...");
        ImGui_ImplDX11_InvalidateDeviceObjects();
        
        // Device and context will be updated by the ResizeBuffers hook
        
        ImGui_ImplDX11_CreateDeviceObjects();
    }

private:
    void SetupStyle() {
        ImGuiStyle& style = ImGui::GetStyle();
        ImVec4* colors = style.Colors;

        // Dark theme
        colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.95f);
        colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
        colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
        colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.29f, 0.48f, 1.00f);
        colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
        colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);

        style.WindowRounding = 5.0f;
        style.FrameRounding = 3.0f;
        style.GrabRounding = 3.0f;
        style.WindowBorderSize = 1.0f;
    }

    void RenderMenu();      // Forward declaration - implemented in menu.h
    void RenderOverlays();  // Forward declaration - implemented in menu.h
};

// Global instance getter
inline Overlay& GetOverlay() {
    return Overlay::GetInstance();
}

} // namespace UI
