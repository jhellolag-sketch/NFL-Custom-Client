#pragma once

#include "../utils/logger.h"
#include "player/godmode.h"
#include "movement/speed.h"
#include "movement/teleport.h"
#include "items/currency.h"

namespace Features {

class FeatureManager {
private:
    bool initialized = false;

public:
    static FeatureManager& GetInstance() {
        static FeatureManager instance;
        return instance;
    }

    void Initialize() {
        if (initialized) return;

        Logger::Log("[FeatureManager] Initializing all features...");

        // Initialize player features
        Player::InitializeGodMode();

        // Initialize movement features
        Movement::InitializeSpeedModifier();
        Movement::InitializeTeleporter();

        // Initialize item features
        Items::InitializeCurrencyEditor();

        initialized = true;
        Logger::Log("[FeatureManager] All features initialized");
    }

    void Update() {
        if (!initialized) return;

        // Update player features
        Player::UpdateGodMode();

        // Update movement features
        Movement::UpdateSpeedModifier();
        Movement::UpdateTeleporter();

        // Update item features
        Items::UpdateCurrencyEditor();
    }

    void Shutdown() {
        if (!initialized) return;

        Logger::Log("[FeatureManager] Shutting down features...");

        // Reset any modified values
        Movement::ResetSpeed();

        initialized = false;
        Logger::Log("[FeatureManager] Features shut down");
    }
};

// Convenience functions
inline void InitializeFeatures() {
    FeatureManager::GetInstance().Initialize();
}

inline void UpdateFeatures() {
    FeatureManager::GetInstance().Update();
}

inline void ShutdownFeatures() {
    FeatureManager::GetInstance().Shutdown();
}

} // namespace Features
