#pragma once

#include <string>
#include <unordered_map>
#include "../core/memory.h"
#include "../utils/logger.h"

namespace Patterns {

// Pattern cache
inline std::unordered_map<std::string, uintptr_t> g_patternCache;

// Game-specific patterns (these need to be updated for the actual game)
struct GamePatterns {
    // Player patterns
    static constexpr const char* PLAYER_HEALTH = "48 8B 05 ?? ?? ?? ?? 48 85 C0 74 ?? F3 0F 10 80";
    static constexpr const char* PLAYER_STAMINA = "F3 0F 10 05 ?? ?? ?? ?? F3 0F 59 C1 F3 0F 11 05";
    static constexpr const char* PLAYER_MANA = "F3 0F 10 0D ?? ?? ?? ?? F3 0F 5C C8 F3 0F 11 0D";
    static constexpr const char* PLAYER_POSITION = "F3 0F 10 80 ?? ?? ?? ?? F3 0F 11 45 ?? F3 0F 10";
    
    // Movement patterns
    static constexpr const char* MOVEMENT_SPEED = "F3 0F 59 0D ?? ?? ?? ?? F3 0F 11 4D ?? F3 0F 10";
    static constexpr const char* JUMP_HEIGHT = "F3 0F 10 05 ?? ?? ?? ?? F3 0F 59 C1 F3 0F 58 C2";
    static constexpr const char* GRAVITY = "F3 0F 10 05 ?? ?? ?? ?? F3 0F 59 C9 F3 0F 58 C8";
    
    // Combat patterns
    static constexpr const char* DAMAGE_OUTPUT = "F3 0F 59 05 ?? ?? ?? ?? F3 0F 11 45 ?? 48 8B 45";
    static constexpr const char* ENEMY_HEALTH = "48 8B 05 ?? ?? ?? ?? 48 85 C0 74 ?? F3 0F 10 88";
    
    // Item patterns
    static constexpr const char* CURRENCY = "48 8B 05 ?? ?? ?? ?? 48 85 C0 74 ?? 8B 80 ?? ??";
    static constexpr const char* INVENTORY_BASE = "48 8B 0D ?? ?? ?? ?? 48 85 C9 74 ?? 48 8B 01 48";
    
    // Visual patterns
    static constexpr const char* FOV = "F3 0F 10 0D ?? ?? ?? ?? 0F 2F CF 76 ?? F3 0F 10";
    static constexpr const char* CAMERA_POSITION = "F3 0F 10 05 ?? ?? ?? ?? F3 0F 11 87 ?? ?? ?? ??";
};

// Find and cache a pattern
inline uintptr_t FindPattern(const std::string& name, const std::string& pattern) {
    // Check cache first
    auto it = g_patternCache.find(name);
    if (it != g_patternCache.end() && it->second != 0) {
        return it->second;
    }

    // Scan for pattern
    Logger::Log("[Patterns] Scanning for pattern: " + name);
    uintptr_t address = Memory::PatternScanIDA(pattern);
    
    if (address != 0) {
        Logger::Log("[Patterns] Found pattern '" + name + "' at: 0x" + 
            std::to_string(address), Logger::INFO);
        g_patternCache[name] = address;
    } else {
        Logger::Log("[Patterns] Failed to find pattern: " + name, Logger::WARN);
        g_patternCache[name] = 0;
    }

    return address;
}

// Get cached pattern
inline uintptr_t GetPattern(const std::string& name) {
    auto it = g_patternCache.find(name);
    if (it != g_patternCache.end()) {
        return it->second;
    }
    return 0;
}

// Initialize all patterns
inline void InitializePatterns() {
    Logger::Log("[Patterns] Initializing pattern database...");
    
    // Player patterns
    FindPattern("PLAYER_HEALTH", GamePatterns::PLAYER_HEALTH);
    FindPattern("PLAYER_STAMINA", GamePatterns::PLAYER_STAMINA);
    FindPattern("PLAYER_MANA", GamePatterns::PLAYER_MANA);
    FindPattern("PLAYER_POSITION", GamePatterns::PLAYER_POSITION);
    
    // Movement patterns
    FindPattern("MOVEMENT_SPEED", GamePatterns::MOVEMENT_SPEED);
    FindPattern("JUMP_HEIGHT", GamePatterns::JUMP_HEIGHT);
    FindPattern("GRAVITY", GamePatterns::GRAVITY);
    
    // Combat patterns
    FindPattern("DAMAGE_OUTPUT", GamePatterns::DAMAGE_OUTPUT);
    FindPattern("ENEMY_HEALTH", GamePatterns::ENEMY_HEALTH);
    
    // Item patterns
    FindPattern("CURRENCY", GamePatterns::CURRENCY);
    FindPattern("INVENTORY_BASE", GamePatterns::INVENTORY_BASE);
    
    // Visual patterns
    FindPattern("FOV", GamePatterns::FOV);
    FindPattern("CAMERA_POSITION", GamePatterns::CAMERA_POSITION);
    
    Logger::Log("[Patterns] Pattern initialization complete");
}

// Clear pattern cache
inline void ClearCache() {
    g_patternCache.clear();
}

} // namespace Patterns
