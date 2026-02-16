#pragma once

#include "../../core/memory.h"
#include "../../core/patterns.h"
#include "../../utils/logger.h"
#include "../../ui/menu.h"

namespace Features {
namespace Movement {

class SpeedModifier {
private:
    bool isActive = false;
    uintptr_t speedAddress = 0;
    float originalSpeed = 1.0f;
    float currentMultiplier = 1.0f;
    
public:
    static SpeedModifier& GetInstance() {
        static SpeedModifier instance;
        return instance;
    }

    void Initialize() {
        // Find speed address using pattern
        uintptr_t patternAddress = Patterns::GetPattern("MOVEMENT_SPEED");
        
        if (patternAddress != 0) {
            // Resolve address (example)
            int32_t offset = Memory::Read<int32_t>(patternAddress + 4);
            speedAddress = patternAddress + 8 + offset;
            
            Logger::Log("[SpeedModifier] Speed address found: 0x" + std::to_string(speedAddress));
            
            // Read original speed
            originalSpeed = Memory::Read<float>(speedAddress);
        } else {
            Logger::Log("[SpeedModifier] Failed to find speed pattern", Logger::WARN);
        }
    }

    void Update() {
        if (speedAddress == 0) return;

        // Get multiplier from UI
        float targetMultiplier = UI::FeatureStates::speedMultiplier;
        
        if (targetMultiplier != currentMultiplier) {
            SetMultiplier(targetMultiplier);
        }
    }

    void SetMultiplier(float multiplier) {
        if (speedAddress == 0) {
            Logger::Log("[SpeedModifier] Cannot set speed - address not found", Logger::ERROR);
            return;
        }

        currentMultiplier = multiplier;
        float newSpeed = originalSpeed * multiplier;
        
        if (Memory::Write<float>(speedAddress, newSpeed)) {
            Logger::Log("[SpeedModifier] Speed set to " + std::to_string(multiplier) + "x");
        } else {
            Logger::Log("[SpeedModifier] Failed to write speed value", Logger::ERROR);
        }
    }

    void Reset() {
        if (speedAddress == 0) return;
        
        Memory::Write<float>(speedAddress, originalSpeed);
        currentMultiplier = 1.0f;
        UI::FeatureStates::speedMultiplier = 1.0f;
        
        Logger::Log("[SpeedModifier] Speed reset to normal");
    }
};

// Convenience functions
inline void InitializeSpeedModifier() {
    SpeedModifier::GetInstance().Initialize();
}

inline void UpdateSpeedModifier() {
    SpeedModifier::GetInstance().Update();
}

inline void SetSpeedMultiplier(float multiplier) {
    SpeedModifier::GetInstance().SetMultiplier(multiplier);
}

inline void ResetSpeed() {
    SpeedModifier::GetInstance().Reset();
}

} // namespace Movement
} // namespace Features
