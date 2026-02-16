#pragma once

#include <Windows.h>
#include <functional>
#include <unordered_map>
#include <mutex>
#include <chrono>

namespace Hotkeys {

struct HotkeyInfo {
    std::function<void()> callback;
    bool wasPressed = false;
    std::chrono::steady_clock::time_point lastTrigger;
    int cooldownMs = 200; // Default cooldown to prevent spam
};

class HotkeyManager {
private:
    std::unordered_map<int, HotkeyInfo> hotkeys;
    std::mutex hotkeyMutex;

public:
    void Register(int vk, std::function<void()> callback, int cooldownMs = 200) {
        std::lock_guard<std::mutex> lock(hotkeyMutex);
        
        HotkeyInfo info;
        info.callback = callback;
        info.cooldownMs = cooldownMs;
        info.lastTrigger = std::chrono::steady_clock::now();
        
        hotkeys[vk] = info;
    }

    void Unregister(int vk) {
        std::lock_guard<std::mutex> lock(hotkeyMutex);
        hotkeys.erase(vk);
    }

    void Process() {
        std::lock_guard<std::mutex> lock(hotkeyMutex);
        
        auto now = std::chrono::steady_clock::now();

        for (auto& [vk, info] : hotkeys) {
            bool isPressed = (GetAsyncKeyState(vk) & 0x8000) != 0;

            if (isPressed && !info.wasPressed) {
                // Key just pressed
                auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                    now - info.lastTrigger).count();

                if (elapsed >= info.cooldownMs) {
                    if (info.callback) {
                        info.callback();
                    }
                    info.lastTrigger = now;
                }
            }

            info.wasPressed = isPressed;
        }
    }

    void Clear() {
        std::lock_guard<std::mutex> lock(hotkeyMutex);
        hotkeys.clear();
    }
};

// Global instance
inline HotkeyManager& GetHotkeyManager() {
    static HotkeyManager manager;
    return manager;
}

// Convenience functions
inline void Register(int vk, std::function<void()> callback, int cooldownMs = 200) {
    GetHotkeyManager().Register(vk, callback, cooldownMs);
}

inline void Unregister(int vk) {
    GetHotkeyManager().Unregister(vk);
}

inline void Process() {
    GetHotkeyManager().Process();
}

inline void Clear() {
    GetHotkeyManager().Clear();
}

} // namespace Hotkeys
