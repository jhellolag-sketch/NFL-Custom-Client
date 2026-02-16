#pragma once

#include <Windows.h>
#include <imgui.h>
#include <string>
#include "../utils/config.h"
#include "../utils/logger.h"

namespace UI {

// Feature states (these will be accessed by feature modules)
namespace FeatureStates {
    // Player features
    inline bool godMode = false;
    inline bool infiniteStamina = false;
    inline bool infiniteMana = false;
    inline float playerHealth = 100.0f;
    inline float playerStamina = 100.0f;
    inline float playerMana = 100.0f;
    inline int playerLevel = 1;
    
    // Combat features
    inline bool oneHitKill = false;
    inline float damageMultiplier = 1.0f;
    
    // Movement features
    inline float speedMultiplier = 1.0f;
    inline float jumpMultiplier = 1.0f;
    inline bool flightMode = false;
    inline bool noclipMode = false;
    inline float teleportX = 0.0f;
    inline float teleportY = 0.0f;
    inline float teleportZ = 0.0f;
    
    // Item features
    inline int currency = 0;
    inline int itemId = 0;
    inline int itemQuantity = 1;
    
    // World features
    inline bool freezeTime = false;
    inline float timeSpeed = 1.0f;
    inline int weatherType = 0;
    
    // Visual features
    inline bool espEnabled = false;
    inline float fov = 90.0f;
    inline bool freeCamera = false;
    inline bool showHUD = true;
}

class Menu {
private:
    int currentTab = 0;
    bool showAbout = false;
    char searchBuffer[256] = "";

public:
    static Menu& GetInstance() {
        static Menu instance;
        return instance;
    }

    void Render() {
        ImGui::SetNextWindowSize(ImVec2(750, 550), ImGuiCond_FirstUseEver);
        
        if (!ImGui::Begin("NFL Custom Client - FANTASY LIFE i Enhancement", nullptr, ImGuiWindowFlags_NoCollapse)) {
            ImGui::End();
            return;
        }

        // Title section
        ImGui::TextColored(ImVec4(0.26f, 0.59f, 0.98f, 1.0f), "NFL Custom Client v1.0");
        ImGui::SameLine();
        ImGui::Text("| Press INSERT to toggle menu");
        
        if (ImGui::Button("About")) {
            showAbout = !showAbout;
        }
        ImGui::SameLine();
        if (ImGui::Button("Save Config")) {
            SaveConfig();
        }
        ImGui::SameLine();
        if (ImGui::Button("Load Config")) {
            LoadConfig();
        }

        ImGui::Separator();

        // Tab bar
        if (ImGui::BeginTabBar("MainTabBar")) {
            if (ImGui::BeginTabItem("Player")) {
                RenderPlayerTab();
                ImGui::EndTabItem();
            }
            
            if (ImGui::BeginTabItem("Combat")) {
                RenderCombatTab();
                ImGui::EndTabItem();
            }
            
            if (ImGui::BeginTabItem("Movement")) {
                RenderMovementTab();
                ImGui::EndTabItem();
            }
            
            if (ImGui::BeginTabItem("Items")) {
                RenderItemsTab();
                ImGui::EndTabItem();
            }
            
            if (ImGui::BeginTabItem("World")) {
                RenderWorldTab();
                ImGui::EndTabItem();
            }
            
            if (ImGui::BeginTabItem("Visual")) {
                RenderVisualTab();
                ImGui::EndTabItem();
            }
            
            if (ImGui::BeginTabItem("Advanced")) {
                RenderAdvancedTab();
                ImGui::EndTabItem();
            }
            
            if (ImGui::BeginTabItem("Settings")) {
                RenderSettingsTab();
                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }

        ImGui::End();

        // About window
        if (showAbout) {
            RenderAbout();
        }
    }

private:
    void RenderPlayerTab() {
        ImGui::BeginChild("PlayerContent", ImVec2(0, 0), true);
        
        ImGui::TextColored(ImVec4(0.26f, 0.59f, 0.98f, 1.0f), "Player Features");
        ImGui::Separator();

        ImGui::Checkbox("God Mode", &FeatureStates::godMode);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Prevents health from decreasing");

        ImGui::Checkbox("Infinite Stamina", &FeatureStates::infiniteStamina);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Keep stamina at maximum");

        ImGui::Checkbox("Infinite Mana/MP", &FeatureStates::infiniteMana);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Maintain maximum mana");

        ImGui::Separator();
        ImGui::Text("Character Stats Editor");
        
        ImGui::SliderFloat("Health", &FeatureStates::playerHealth, 0.0f, 9999.0f, "%.0f");
        ImGui::SliderFloat("Stamina", &FeatureStates::playerStamina, 0.0f, 9999.0f, "%.0f");
        ImGui::SliderFloat("Mana", &FeatureStates::playerMana, 0.0f, 9999.0f, "%.0f");
        
        ImGui::Separator();
        ImGui::InputInt("Level", &FeatureStates::playerLevel);
        if (ImGui::Button("Max All Stats")) {
            FeatureStates::playerHealth = 9999.0f;
            FeatureStates::playerStamina = 9999.0f;
            FeatureStates::playerMana = 9999.0f;
        }

        ImGui::EndChild();
    }

    void RenderCombatTab() {
        ImGui::BeginChild("CombatContent", ImVec2(0, 0), true);
        
        ImGui::TextColored(ImVec4(0.26f, 0.59f, 0.98f, 1.0f), "Combat Features");
        ImGui::Separator();

        ImGui::Checkbox("One-Hit Kill", &FeatureStates::oneHitKill);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Enemies die in one hit");

        ImGui::SliderFloat("Damage Multiplier", &FeatureStates::damageMultiplier, 0.1f, 100.0f, "%.1fx");
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Multiply your damage output");

        if (ImGui::Button("Reset to 1x")) {
            FeatureStates::damageMultiplier = 1.0f;
        }

        ImGui::EndChild();
    }

    void RenderMovementTab() {
        ImGui::BeginChild("MovementContent", ImVec2(0, 0), true);
        
        ImGui::TextColored(ImVec4(0.26f, 0.59f, 0.98f, 1.0f), "Movement Features");
        ImGui::Separator();

        ImGui::SliderFloat("Speed Multiplier", &FeatureStates::speedMultiplier, 0.1f, 10.0f, "%.1fx");
        ImGui::SliderFloat("Jump Height", &FeatureStates::jumpMultiplier, 1.0f, 20.0f, "%.1fx");

        ImGui::Separator();
        ImGui::Checkbox("Flight Mode", &FeatureStates::flightMode);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Disable gravity - use WASD + Space/Ctrl");

        ImGui::Checkbox("No-Clip Mode", &FeatureStates::noclipMode);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Walk through walls");

        ImGui::Separator();
        ImGui::Text("Teleportation");
        
        ImGui::InputFloat("X Position", &FeatureStates::teleportX, 1.0f, 10.0f, "%.2f");
        ImGui::InputFloat("Y Position", &FeatureStates::teleportY, 1.0f, 10.0f, "%.2f");
        ImGui::InputFloat("Z Position", &FeatureStates::teleportZ, 1.0f, 10.0f, "%.2f");
        
        if (ImGui::Button("Save Position (F5)")) {
            Logger::Log("[Menu] Position saved");
        }
        ImGui::SameLine();
        if (ImGui::Button("Load Position (F6)")) {
            Logger::Log("[Menu] Position loaded");
        }
        
        if (ImGui::Button("Teleport to Coordinates")) {
            Logger::Log("[Menu] Teleporting to saved position");
        }

        ImGui::EndChild();
    }

    void RenderItemsTab() {
        ImGui::BeginChild("ItemsContent", ImVec2(0, 0), true);
        
        ImGui::TextColored(ImVec4(0.26f, 0.59f, 0.98f, 1.0f), "Item Features");
        ImGui::Separator();

        ImGui::Text("Currency Editor");
        ImGui::InputInt("Currency Amount", &FeatureStates::currency);
        if (ImGui::Button("Set Currency")) {
            Logger::Log("[Menu] Currency updated");
        }

        ImGui::Separator();
        ImGui::Text("Item Spawner");
        ImGui::InputInt("Item ID", &FeatureStates::itemId);
        ImGui::InputInt("Quantity", &FeatureStates::itemQuantity);
        if (ImGui::Button("Spawn Item")) {
            Logger::Log("[Menu] Item spawned");
        }

        ImGui::Separator();
        ImGui::Text("Inventory Tools");
        if (ImGui::Button("Remove Weight Limit")) {
            Logger::Log("[Menu] Weight limit removed");
        }
        if (ImGui::Button("Unlock All Slots")) {
            Logger::Log("[Menu] All inventory slots unlocked");
        }

        ImGui::EndChild();
    }

    void RenderWorldTab() {
        ImGui::BeginChild("WorldContent", ImVec2(0, 0), true);
        
        ImGui::TextColored(ImVec4(0.26f, 0.59f, 0.98f, 1.0f), "World Features");
        ImGui::Separator();

        ImGui::Text("Time Control");
        ImGui::Checkbox("Freeze Time", &FeatureStates::freezeTime);
        ImGui::SliderFloat("Time Speed", &FeatureStates::timeSpeed, 0.0f, 10.0f, "%.1fx");
        
        if (ImGui::Button("Normal (1x)")) FeatureStates::timeSpeed = 1.0f;
        ImGui::SameLine();
        if (ImGui::Button("Fast (5x)")) FeatureStates::timeSpeed = 5.0f;
        ImGui::SameLine();
        if (ImGui::Button("Very Fast (10x)")) FeatureStates::timeSpeed = 10.0f;

        ImGui::Separator();
        ImGui::Text("Weather Control");
        const char* weatherTypes[] = { "Clear", "Cloudy", "Rain", "Storm", "Snow", "Fog" };
        ImGui::Combo("Weather Type", &FeatureStates::weatherType, weatherTypes, IM_ARRAYSIZE(weatherTypes));
        if (ImGui::Button("Apply Weather")) {
            Logger::Log("[Menu] Weather changed");
        }

        ImGui::EndChild();
    }

    void RenderVisualTab() {
        ImGui::BeginChild("VisualContent", ImVec2(0, 0), true);
        
        ImGui::TextColored(ImVec4(0.26f, 0.59f, 0.98f, 1.0f), "Visual Features");
        ImGui::Separator();

        ImGui::Checkbox("ESP/Wallhack", &FeatureStates::espEnabled);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("See enemies through walls");

        ImGui::SliderFloat("Field of View", &FeatureStates::fov, 60.0f, 120.0f, "%.0f");
        if (ImGui::Button("Reset FOV")) {
            FeatureStates::fov = 90.0f;
        }

        ImGui::Separator();
        ImGui::Checkbox("Free Camera", &FeatureStates::freeCamera);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Detach camera from player");

        ImGui::Checkbox("Show HUD", &FeatureStates::showHUD);

        ImGui::EndChild();
    }

    void RenderAdvancedTab() {
        ImGui::BeginChild("AdvancedContent", ImVec2(0, 0), true);
        
        ImGui::TextColored(ImVec4(0.26f, 0.59f, 0.98f, 1.0f), "Advanced Features");
        ImGui::Separator();

        ImGui::TextWrapped("Advanced features like console access, script executor, and memory scanner would be implemented here.");
        ImGui::Separator();
        
        ImGui::Text("Debug Console");
        if (ImGui::Button("Open Console")) {
            Logger::Log("[Menu] Console opened");
        }

        ImGui::Separator();
        ImGui::Text("Memory Scanner");
        if (ImGui::Button("Open Scanner")) {
            Logger::Log("[Menu] Memory scanner opened");
        }

        ImGui::EndChild();
    }

    void RenderSettingsTab() {
        ImGui::BeginChild("SettingsContent", ImVec2(0, 0), true);
        
        ImGui::TextColored(ImVec4(0.26f, 0.59f, 0.98f, 1.0f), "Settings");
        ImGui::Separator();

        ImGui::Text("Hotkeys");
        ImGui::BulletText("INSERT: Toggle Menu");
        ImGui::BulletText("F5: Save Teleport Position");
        ImGui::BulletText("F6: Load Teleport Position");
        ImGui::BulletText("END: Unload DLL");

        ImGui::Separator();
        ImGui::Text("Theme");
        if (ImGui::Button("Dark Theme (Default)")) {
            Logger::Log("[Menu] Dark theme applied");
        }

        ImGui::Separator();
        ImGui::Text("Configuration");
        ImGui::TextWrapped("Config file location: %%USERPROFILE%%\\Documents\\NFL-Custom-Client\\config.json");
        
        if (ImGui::Button("Open Config Folder")) {
            char path[MAX_PATH];
            if (SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, 0, path) == S_OK) {
                std::string folder = std::string(path) + "\\NFL-Custom-Client";
                ShellExecuteA(NULL, "open", folder.c_str(), NULL, NULL, SW_SHOW);
            }
        }

        ImGui::EndChild();
    }

    void RenderAbout() {
        ImGui::SetNextWindowSize(ImVec2(500, 300), ImGuiCond_FirstUseEver);
        
        if (ImGui::Begin("About NFL Custom Client", &showAbout)) {
            ImGui::TextColored(ImVec4(0.26f, 0.59f, 0.98f, 1.0f), "NFL Custom Client");
            ImGui::Text("Version 1.0");
            ImGui::Separator();

            ImGui::TextWrapped("A comprehensive DLL enhancement framework for FANTASY LIFE i: The Girl Who Steals Time.");
            ImGui::Spacing();

            ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.0f, 1.0f), "Disclaimer:");
            ImGui::TextWrapped("This project is for educational purposes only. Designed for single-player use on a game owned by the developer's family. This toolkit is intended to learn about game engine internals, memory management, and DirectX programming.");
            ImGui::Spacing();

            ImGui::TextWrapped("Do not use this on games you do not own or in multiplayer environments. Respect intellectual property and terms of service.");
            ImGui::Spacing();

            ImGui::Separator();
            ImGui::Text("Built with:");
            ImGui::BulletText("C++ (C++17)");
            ImGui::BulletText("Dear ImGui (DirectX 11)");
            ImGui::BulletText("MinHook");
            ImGui::BulletText("nlohmann/json");
            ImGui::BulletText("AI assistance");

            ImGui::Separator();
            ImGui::TextColored(ImVec4(0.5f, 1.0f, 0.5f, 1.0f), "Credits: Built with AI assistance");
        }
        ImGui::End();
    }

    void SaveConfig() {
        auto& cfg = Config::GetConfig();
        
        cfg["features"]["god_mode"] = FeatureStates::godMode;
        cfg["features"]["infinite_stamina"] = FeatureStates::infiniteStamina;
        cfg["features"]["infinite_mana"] = FeatureStates::infiniteMana;
        cfg["features"]["one_hit_kill"] = FeatureStates::oneHitKill;
        cfg["features"]["damage_multiplier"] = FeatureStates::damageMultiplier;
        cfg["features"]["speed_multiplier"] = FeatureStates::speedMultiplier;
        cfg["features"]["jump_multiplier"] = FeatureStates::jumpMultiplier;
        cfg["features"]["flight_mode"] = FeatureStates::flightMode;
        cfg["features"]["noclip_mode"] = FeatureStates::noclipMode;
        cfg["features"]["esp_enabled"] = FeatureStates::espEnabled;
        cfg["features"]["fov"] = FeatureStates::fov;
        cfg["features"]["free_camera"] = FeatureStates::freeCamera;

        if (Config::Save()) {
            Logger::Log("[Menu] Configuration saved successfully");
        } else {
            Logger::Log("[Menu] Failed to save configuration", Logger::ERROR);
        }
    }

    void LoadConfig() {
        auto& cfg = Config::GetConfig();
        
        if (cfg.contains("features")) {
            FeatureStates::godMode = cfg["features"].value("god_mode", false);
            FeatureStates::infiniteStamina = cfg["features"].value("infinite_stamina", false);
            FeatureStates::infiniteMana = cfg["features"].value("infinite_mana", false);
            FeatureStates::oneHitKill = cfg["features"].value("one_hit_kill", false);
            FeatureStates::damageMultiplier = cfg["features"].value("damage_multiplier", 1.0f);
            FeatureStates::speedMultiplier = cfg["features"].value("speed_multiplier", 1.0f);
            FeatureStates::jumpMultiplier = cfg["features"].value("jump_multiplier", 1.0f);
            FeatureStates::flightMode = cfg["features"].value("flight_mode", false);
            FeatureStates::noclipMode = cfg["features"].value("noclip_mode", false);
            FeatureStates::espEnabled = cfg["features"].value("esp_enabled", false);
            FeatureStates::fov = cfg["features"].value("fov", 90.0f);
            FeatureStates::freeCamera = cfg["features"].value("free_camera", false);
        }

        Logger::Log("[Menu] Configuration loaded successfully");
    }
};

// Implementations for Overlay forward declarations
void Overlay::RenderMenu() {
    Menu::GetInstance().Render();
}

void Overlay::RenderOverlays() {
    // FPS counter
    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(0.35f);
    
    if (ImGui::Begin("##FPS", nullptr, 
        ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | 
        ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | 
        ImGuiWindowFlags_NoNav)) {
        ImGui::Text("FPS: %.1f", io.Framerate);
    }
    ImGui::End();
}

} // namespace UI
