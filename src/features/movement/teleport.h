#pragma once

#include "../../core/memory.h"
#include "../../core/patterns.h"
#include "../../utils/logger.h"
#include "../../ui/menu.h"
#include <vector>
#include <string>

namespace Features {
namespace Movement {

struct TeleportPosition {
    float x, y, z;
    std::string name;
};

class Teleporter {
private:
    uintptr_t positionAddress = 0;
    TeleportPosition savedPosition;
    std::vector<TeleportPosition> waypoints;
    
public:
    static Teleporter& GetInstance() {
        static Teleporter instance;
        return instance;
    }

    void Initialize() {
        // Find player position address
        uintptr_t patternAddress = Patterns::GetPattern("PLAYER_POSITION");
        
        if (patternAddress != 0) {
            // Resolve address
            int32_t offset = Memory::Read<int32_t>(patternAddress + 4);
            positionAddress = patternAddress + 8 + offset;
            
            Logger::Log("[Teleporter] Position address found: 0x" + std::to_string(positionAddress));
        } else {
            Logger::Log("[Teleporter] Failed to find position pattern", Logger::WARN);
        }
    }

    void Update() {
        if (positionAddress == 0) return;

        // Update current position display in UI
        uintptr_t playerBase = Memory::Read<uintptr_t>(positionAddress);
        if (playerBase != 0) {
            UI::FeatureStates::teleportX = Memory::Read<float>(playerBase + 0x120);
            UI::FeatureStates::teleportY = Memory::Read<float>(playerBase + 0x124);
            UI::FeatureStates::teleportZ = Memory::Read<float>(playerBase + 0x128);
        }
    }

    void SaveCurrentPosition() {
        if (positionAddress == 0) {
            Logger::Log("[Teleporter] Cannot save - position address not found", Logger::ERROR);
            return;
        }

        uintptr_t playerBase = Memory::Read<uintptr_t>(positionAddress);
        if (playerBase == 0) {
            Logger::Log("[Teleporter] Cannot save - invalid player base", Logger::ERROR);
            return;
        }

        savedPosition.x = Memory::Read<float>(playerBase + 0x120);
        savedPosition.y = Memory::Read<float>(playerBase + 0x124);
        savedPosition.z = Memory::Read<float>(playerBase + 0x128);
        savedPosition.name = "Quick Save";

        Logger::Log("[Teleporter] Position saved: (" + 
            std::to_string(savedPosition.x) + ", " +
            std::to_string(savedPosition.y) + ", " +
            std::to_string(savedPosition.z) + ")");
    }

    void LoadSavedPosition() {
        if (positionAddress == 0) {
            Logger::Log("[Teleporter] Cannot load - position address not found", Logger::ERROR);
            return;
        }

        TeleportTo(savedPosition.x, savedPosition.y, savedPosition.z);
        Logger::Log("[Teleporter] Teleported to saved position");
    }

    void TeleportTo(float x, float y, float z) {
        if (positionAddress == 0) {
            Logger::Log("[Teleporter] Cannot teleport - position address not found", Logger::ERROR);
            return;
        }

        uintptr_t playerBase = Memory::Read<uintptr_t>(positionAddress);
        if (playerBase == 0) {
            Logger::Log("[Teleporter] Cannot teleport - invalid player base", Logger::ERROR);
            return;
        }

        // Write new position
        bool success = true;
        success &= Memory::Write<float>(playerBase + 0x120, x);
        success &= Memory::Write<float>(playerBase + 0x124, y);
        success &= Memory::Write<float>(playerBase + 0x128, z);

        if (success) {
            Logger::Log("[Teleporter] Teleported to (" + 
                std::to_string(x) + ", " +
                std::to_string(y) + ", " +
                std::to_string(z) + ")");
        } else {
            Logger::Log("[Teleporter] Failed to write position", Logger::ERROR);
        }
    }

    void TeleportToUICoordinates() {
        TeleportTo(
            UI::FeatureStates::teleportX,
            UI::FeatureStates::teleportY,
            UI::FeatureStates::teleportZ
        );
    }

    void AddWaypoint(const std::string& name, float x, float y, float z) {
        TeleportPosition waypoint;
        waypoint.name = name;
        waypoint.x = x;
        waypoint.y = y;
        waypoint.z = z;
        waypoints.push_back(waypoint);
        
        Logger::Log("[Teleporter] Waypoint added: " + name);
    }

    void TeleportToWaypoint(size_t index) {
        if (index >= waypoints.size()) {
            Logger::Log("[Teleporter] Invalid waypoint index", Logger::ERROR);
            return;
        }

        const TeleportPosition& wp = waypoints[index];
        TeleportTo(wp.x, wp.y, wp.z);
        Logger::Log("[Teleporter] Teleported to waypoint: " + wp.name);
    }

    const std::vector<TeleportPosition>& GetWaypoints() const {
        return waypoints;
    }
};

// Convenience functions
inline void InitializeTeleporter() {
    Teleporter::GetInstance().Initialize();
}

inline void UpdateTeleporter() {
    Teleporter::GetInstance().Update();
}

inline void SaveTeleportPosition() {
    Teleporter::GetInstance().SaveCurrentPosition();
}

inline void LoadTeleportPosition() {
    Teleporter::GetInstance().LoadSavedPosition();
}

inline void TeleportToCoordinates(float x, float y, float z) {
    Teleporter::GetInstance().TeleportTo(x, y, z);
}

inline void TeleportToUICoordinates() {
    Teleporter::GetInstance().TeleportToUICoordinates();
}

} // namespace Movement
} // namespace Features
