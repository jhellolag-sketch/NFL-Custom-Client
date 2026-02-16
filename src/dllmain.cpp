#include <Windows.h>
#include <thread>
#include "core/hooks.h"
#include "core/memory.h"
#include "core/unreal.h"
#include "core/patterns.h"
#include "ui/overlay.h"
#include "ui/menu.h"
#include "utils/logger.h"
#include "utils/config.h"
#include "utils/hotkeys.h"
#include "features/feature_manager.h"

DWORD WINAPI MainThread(LPVOID lpParam)
{
    // Initialize logger
    Logger::Init();
    Logger::Log("==============================================");
    Logger::Log("[+] NFL Custom Client v1.0 loaded");
    Logger::Log("[*] FANTASY LIFE i Enhancement Framework");
    Logger::Log("==============================================");
    
    // Load configuration
    Logger::Log("[*] Loading configuration...");
    if (Config::Load()) {
        Logger::Log("[+] Configuration loaded successfully");
    } else {
        Logger::Log("[!] Failed to load configuration, using defaults", Logger::WARN);
    }
    
    // Initialize memory utilities
    Logger::Log("[*] Initializing memory system...");
    uintptr_t baseAddress = Memory::GetModuleBaseAddress();
    Logger::Log("[+] Game base address: 0x" + std::to_string(baseAddress));
    
    // Initialize pattern scanning
    Logger::Log("[*] Scanning for game patterns...");
    Patterns::InitializePatterns();
    
    // Initialize Unreal Engine utilities
    Logger::Log("[*] Initializing Unreal Engine interface...");
    if (Unreal::Initialize()) {
        Logger::Log("[+] Unreal Engine interface initialized");
    } else {
        Logger::Log("[!] Unreal Engine interface initialization skipped", Logger::WARN);
    }
    
    // Initialize hooks
    Logger::Log("[*] Initializing hooks system...");
    if (!Hooks::Initialize()) {
        Logger::Log("[-] Failed to initialize hooks", Logger::ERROR);
        Logger::Shutdown();
        FreeLibraryAndExitThread((HMODULE)lpParam, 1);
        return 1;
    }
    Logger::Log("[+] Hooks system initialized");
    
    // Hook DirectX 11
    Logger::Log("[*] Hooking DirectX 11...");
    if (Hooks::HookDirectX11()) {
        Logger::Log("[+] DirectX 11 hooked successfully");
    } else {
        Logger::Log("[-] Failed to hook DirectX 11", Logger::ERROR);
        Hooks::Shutdown();
        Logger::Shutdown();
        FreeLibraryAndExitThread((HMODULE)lpParam, 1);
        return 1;
    }
    
    // Initialize features
    Logger::Log("[*] Initializing feature modules...");
    Features::InitializeFeatures();
    Logger::Log("[+] Feature modules initialized");
    
    // Register hotkeys
    Logger::Log("[*] Registering hotkeys...");
    Hotkeys::Register(VK_INSERT, []() {
        UI::GetOverlay().ToggleMenu();
        Logger::Log("[Hotkey] Menu toggled");
    });
    
    Hotkeys::Register(VK_F5, []() {
        Features::Movement::SaveTeleportPosition();
    });
    
    Hotkeys::Register(VK_F6, []() {
        Features::Movement::LoadTeleportPosition();
    });
    
    Logger::Log("[+] All systems initialized successfully");
    Logger::Log("==============================================");
    Logger::Log("[*] Press INSERT to open menu");
    Logger::Log("[*] Press F5 to save position");
    Logger::Log("[*] Press F6 to load position");
    Logger::Log("[*] Press END to unload");
    Logger::Log("==============================================");
    
    // Main loop
    while (!(GetAsyncKeyState(VK_END) & 0x8000))
    {
        Hotkeys::Process();
        Features::UpdateFeatures();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    // Cleanup
    Logger::Log("==============================================");
    Logger::Log("[*] Unloading NFL Custom Client...");
    
    Features::ShutdownFeatures();
    Logger::Log("[+] Features shut down");
    
    Config::Save();
    Logger::Log("[+] Configuration saved");
    
    UI::GetOverlay().Shutdown();
    Logger::Log("[+] UI shut down");
    
    Hotkeys::Clear();
    Logger::Log("[+] Hotkeys cleared");
    
    Hooks::Shutdown();
    Logger::Log("[+] Hooks removed");
    
    Logger::Log("[+] NFL Custom Client unloaded successfully");
    Logger::Log("==============================================");
    Logger::Shutdown();
    
    FreeLibraryAndExitThread((HMODULE)lpParam, 0);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, MainThread, hModule, 0, nullptr);
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
