#include "hooks.h"
#include "../ui/overlay.h"

namespace Hooks {

// Present hook implementation
HRESULT STDMETHODCALLTYPE hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
    // Initialize overlay on first call
    static bool initialized = false;
    if (!initialized) {
        if (UI::GetOverlay().Initialize(pSwapChain)) {
            initialized = true;
        }
    }

    // Render overlay
    if (initialized) {
        UI::GetOverlay().Render();
    }

    return oPresent(pSwapChain, SyncInterval, Flags);
}

// ResizeBuffers hook implementation
HRESULT STDMETHODCALLTYPE hkResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, 
    UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) {
    
    UI::GetOverlay().HandleResize();

    HRESULT hr = oResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);

    return hr;
}

} // namespace Hooks
