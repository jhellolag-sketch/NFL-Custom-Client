#pragma once

#include "../../core/memory.h"
#include "../../core/patterns.h"
#include "../../utils/logger.h"
#include "../../ui/menu.h"

namespace Features {
namespace Player {

class GodMode {
private:
    bool isActive = false;
    uintptr_t healthAddress = 0;
    float originalHealth = 100.0f;
    
public:
    static GodMode& GetInstance() {
        static GodMode instance;
        return instance;
    }

    void Initialize() {
        // Find health address using pattern
        uintptr_t patternAddress = Patterns::GetPattern("PLAYER_HEALTH");
        
        if (patternAddress != 0) {
            // Resolve RIP-relative address (example for x64)
            // Pattern: 48 8B 05 ?? ?? ?? ?? (mov rax, [rip + offset])
            int32_t offset = Memory::Read<int32_t>(patternAddress + 3);
            healthAddress = patternAddress + 7 + offset;
            
            Logger::Log("[GodMode] Health address found: 0x" + std::to_string(healthAddress));
        } else {
            Logger::Log("[GodMode] Failed to find health pattern", Logger::WARN);
        }
    }

    void Update() {
        if (!isActive) return;
        if (healthAddress == 0) return;

        // Get player health pointer
        uintptr_t playerBase = Memory::Read<uintptr_t>(healthAddress);
        if (playerBase == 0) return;

        // Read current health
        float currentHealth = Memory::Read<float>(playerBase + 0x100); // Offset example
        
        // If health is decreasing, restore it
        if (currentHealth < originalHealth) {
            Memory::Write<float>(playerBase + 0x100, originalHealth);
        }
    }

    void Enable() {
        if (healthAddress == 0) {
            Logger::Log("[GodMode] Cannot enable - health address not found", Logger::ERROR);
            return;
        }

        isActive = true;
        UI::FeatureStates::godMode = true;
        
        // Store original health
        uintptr_t playerBase = Memory::Read<uintptr_t>(healthAddress);
        if (playerBase != 0) {
            originalHealth = Memory::Read<float>(playerBase + 0x100);
        }

        Logger::Log("[GodMode] Enabled");
    }

    void Disable() {
        isActive = false;
        UI::FeatureStates::godMode = false;
        Logger::Log("[GodMode] Disabled");
    }

    void Toggle() {
        if (isActive) {
            Disable();
        } else {
            Enable();
        }
    }

    bool IsActive() const {
        return isActive;
    }
};

// Convenience functions
inline void InitializeGodMode() {
    GodMode::GetInstance().Initialize();
}

inline void UpdateGodMode() {
    GodMode::GetInstance().Update();
}

inline void ToggleGodMode() {
    GodMode::GetInstance().Toggle();
}

} // namespace Player
} // namespace Features
