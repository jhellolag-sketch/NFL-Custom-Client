#pragma once

#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include <MinHook.h>
#include "../utils/logger.h"

namespace Hooks {

// DirectX 11 function pointers
using PresentFn = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, UINT, UINT);
using ResizeBuffersFn = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);

// Original function pointers
inline PresentFn oPresent = nullptr;
inline ResizeBuffersFn oResizeBuffers = nullptr;

// DirectX 11 objects
inline ID3D11Device* g_pd3dDevice = nullptr;
inline ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
inline IDXGISwapChain* g_pSwapChain = nullptr;

// Hooks state
inline bool g_hooksInitialized = false;

// Forward declarations for detour functions
HRESULT STDMETHODCALLTYPE hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
HRESULT STDMETHODCALLTYPE hkResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, 
    UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);

// Initialize MinHook
inline bool Initialize() {
    if (g_hooksInitialized) return true;

    Logger::Log("[Hooks] Initializing MinHook...");
    
    MH_STATUS status = MH_Initialize();
    if (status != MH_OK && status != MH_ERROR_ALREADY_INITIALIZED) {
        Logger::Log("[Hooks] Failed to initialize MinHook: " + std::to_string(status), Logger::ERROR);
        return false;
    }

    g_hooksInitialized = true;
    Logger::Log("[Hooks] MinHook initialized successfully");
    return true;
}

// Shutdown MinHook
inline void Shutdown() {
    if (!g_hooksInitialized) return;

    Logger::Log("[Hooks] Shutting down hooks...");
    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();
    g_hooksInitialized = false;
    Logger::Log("[Hooks] Hooks shut down");
}

// Hook DirectX 11 Present function
inline bool HookDirectX11() {
    Logger::Log("[Hooks] Attempting to hook DirectX 11...");

    // Create a dummy D3D11 device to get the VTable
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0 };
    
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 1;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = GetForegroundWindow();
    sd.SampleDesc.Count = 1;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    IDXGISwapChain* pSwapChain = nullptr;
    ID3D11Device* pDevice = nullptr;
    ID3D11DeviceContext* pContext = nullptr;

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0,
        featureLevels,
        2,
        D3D11_SDK_VERSION,
        &sd,
        &pSwapChain,
        &pDevice,
        &featureLevel,
        &pContext
    );

    if (FAILED(hr)) {
        Logger::Log("[Hooks] Failed to create dummy D3D11 device", Logger::ERROR);
        return false;
    }

    // Get VTable
    void** pVTable = *reinterpret_cast<void***>(pSwapChain);
    void* pPresentAddr = pVTable[8];  // Present is at index 8
    void* pResizeBuffersAddr = pVTable[13]; // ResizeBuffers is at index 13

    // Hook Present
    MH_STATUS status = MH_CreateHook(pPresentAddr, &hkPresent, reinterpret_cast<void**>(&oPresent));
    if (status != MH_OK) {
        Logger::Log("[Hooks] Failed to create Present hook: " + std::to_string(status), Logger::ERROR);
        pSwapChain->Release();
        pDevice->Release();
        pContext->Release();
        return false;
    }

    // Hook ResizeBuffers
    status = MH_CreateHook(pResizeBuffersAddr, &hkResizeBuffers, reinterpret_cast<void**>(&oResizeBuffers));
    if (status != MH_OK) {
        Logger::Log("[Hooks] Failed to create ResizeBuffers hook: " + std::to_string(status), Logger::ERROR);
    }

    // Enable hooks
    MH_EnableHook(pPresentAddr);
    MH_EnableHook(pResizeBuffersAddr);

    // Cleanup dummy objects
    pSwapChain->Release();
    pDevice->Release();
    pContext->Release();

    Logger::Log("[Hooks] DirectX 11 hooks installed successfully");
    return true;
}

// Create hook for any function
template<typename T>
inline bool CreateHook(void* pTarget, void* pDetour, T** ppOriginal) {
    if (!g_hooksInitialized) {
        Logger::Log("[Hooks] Cannot create hook: MinHook not initialized", Logger::ERROR);
        return false;
    }

    MH_STATUS status = MH_CreateHook(pTarget, pDetour, reinterpret_cast<void**>(ppOriginal));
    if (status != MH_OK) {
        Logger::Log("[Hooks] Failed to create hook: " + std::to_string(status), Logger::ERROR);
        return false;
    }

    status = MH_EnableHook(pTarget);
    if (status != MH_OK) {
        Logger::Log("[Hooks] Failed to enable hook: " + std::to_string(status), Logger::ERROR);
        return false;
    }

    return true;
}

// Disable a hook
inline bool DisableHook(void* pTarget) {
    MH_STATUS status = MH_DisableHook(pTarget);
    return status == MH_OK;
}

// Enable a hook
inline bool EnableHook(void* pTarget) {
    MH_STATUS status = MH_EnableHook(pTarget);
    return status == MH_OK;
}

} // namespace Hooks
