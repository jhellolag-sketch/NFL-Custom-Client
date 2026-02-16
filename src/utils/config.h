#pragma once

#include <string>
#include <fstream>
#include <mutex>
#include <nlohmann/json.hpp>
#include <Windows.h>
#include <Shlobj.h>

namespace Config {

class ConfigManager {
private:
    nlohmann::json config;
    std::mutex configMutex;
    std::string configPath;
    bool initialized = false;

public:
    bool Load() {
        std::lock_guard<std::mutex> lock(configMutex);

        // Get user's Documents folder
        char path[MAX_PATH];
        if (SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, 0, path) != S_OK) {
            return false;
        }

        std::string dirPath = std::string(path) + "\\NFL-Custom-Client";
        CreateDirectoryA(dirPath.c_str(), NULL);
        
        configPath = dirPath + "\\config.json";

        // Try to load existing config
        std::ifstream file(configPath);
        if (file.is_open()) {
            try {
                file >> config;
                file.close();
                initialized = true;
                return true;
            } catch (...) {
                file.close();
            }
        }

        // Create default config
        CreateDefaultConfig();
        initialized = true;
        return Save();
    }

    bool Save() {
        std::lock_guard<std::mutex> lock(configMutex);

        if (!initialized) return false;

        try {
            std::ofstream file(configPath);
            if (!file.is_open()) return false;
            
            file << config.dump(4);
            file.close();
            return true;
        } catch (...) {
            return false;
        }
    }

    nlohmann::json& GetConfig() {
        std::lock_guard<std::mutex> lock(configMutex);
        return config;
    }

    template<typename T>
    T Get(const std::string& key, const T& defaultValue) {
        std::lock_guard<std::mutex> lock(configMutex);
        
        try {
            if (config.contains(key)) {
                return config[key].get<T>();
            }
        } catch (...) {}
        
        return defaultValue;
    }

    template<typename T>
    void Set(const std::string& key, const T& value) {
        std::lock_guard<std::mutex> lock(configMutex);
        config[key] = value;
    }

private:
    void CreateDefaultConfig() {
        // UI Settings
        config["ui"]["theme"] = "dark";
        config["ui"]["show_fps"] = false;
        config["ui"]["opacity"] = 0.95f;

        // Hotkeys
        config["hotkeys"]["toggle_menu"] = VK_INSERT;
        config["hotkeys"]["teleport_save"] = VK_F5;
        config["hotkeys"]["teleport_load"] = VK_F6;
        config["hotkeys"]["unload"] = VK_END;

        // Player Features
        config["features"]["god_mode"] = false;
        config["features"]["infinite_stamina"] = false;
        config["features"]["infinite_mana"] = false;

        // Combat Features
        config["features"]["one_hit_kill"] = false;
        config["features"]["damage_multiplier"] = 1.0f;

        // Movement Features
        config["features"]["speed_multiplier"] = 1.0f;
        config["features"]["jump_multiplier"] = 1.0f;
        config["features"]["flight_mode"] = false;
        config["features"]["noclip_mode"] = false;

        // Visual Features
        config["features"]["esp_enabled"] = false;
        config["features"]["fov"] = 90.0f;
        config["features"]["free_camera"] = false;

        // Teleport positions
        config["teleport"]["saved_positions"] = nlohmann::json::array();
    }
};

// Global instance
inline ConfigManager& GetConfigManager() {
    static ConfigManager manager;
    return manager;
}

// Convenience functions
inline bool Load() {
    return GetConfigManager().Load();
}

inline bool Save() {
    return GetConfigManager().Save();
}

inline nlohmann::json& GetConfig() {
    return GetConfigManager().GetConfig();
}

template<typename T>
inline T Get(const std::string& key, const T& defaultValue) {
    return GetConfigManager().Get(key, defaultValue);
}

template<typename T>
inline void Set(const std::string& key, const T& value) {
    GetConfigManager().Set(key, value);
}

} // namespace Config
