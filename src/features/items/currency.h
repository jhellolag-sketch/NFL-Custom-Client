#pragma once

#include "../../core/memory.h"
#include "../../core/patterns.h"
#include "../../utils/logger.h"
#include "../../ui/menu.h"

namespace Features {
namespace Items {

class CurrencyEditor {
private:
    uintptr_t currencyAddress = 0;
    
public:
    static CurrencyEditor& GetInstance() {
        static CurrencyEditor instance;
        return instance;
    }

    void Initialize() {
        // Find currency address using pattern
        uintptr_t patternAddress = Patterns::GetPattern("CURRENCY");
        
        if (patternAddress != 0) {
            // Resolve address
            int32_t offset = Memory::Read<int32_t>(patternAddress + 3);
            currencyAddress = patternAddress + 7 + offset;
            
            Logger::Log("[CurrencyEditor] Currency address found: 0x" + std::to_string(currencyAddress));
        } else {
            Logger::Log("[CurrencyEditor] Failed to find currency pattern", Logger::WARN);
        }
    }

    void Update() {
        if (currencyAddress == 0) return;

        // Read and display current currency
        uintptr_t playerBase = Memory::Read<uintptr_t>(currencyAddress);
        if (playerBase != 0) {
            int currentCurrency = Memory::Read<int>(playerBase + 0x50); // Offset example
            UI::FeatureStates::currency = currentCurrency;
        }
    }

    void SetCurrency(int amount) {
        if (currencyAddress == 0) {
            Logger::Log("[CurrencyEditor] Cannot set currency - address not found", Logger::ERROR);
            return;
        }

        uintptr_t playerBase = Memory::Read<uintptr_t>(currencyAddress);
        if (playerBase == 0) {
            Logger::Log("[CurrencyEditor] Cannot set currency - invalid player base", Logger::ERROR);
            return;
        }

        if (Memory::Write<int>(playerBase + 0x50, amount)) {
            UI::FeatureStates::currency = amount;
            Logger::Log("[CurrencyEditor] Currency set to: " + std::to_string(amount));
        } else {
            Logger::Log("[CurrencyEditor] Failed to write currency value", Logger::ERROR);
        }
    }

    int GetCurrentCurrency() {
        if (currencyAddress == 0) return 0;

        uintptr_t playerBase = Memory::Read<uintptr_t>(currencyAddress);
        if (playerBase == 0) return 0;

        return Memory::Read<int>(playerBase + 0x50);
    }

    void AddCurrency(int amount) {
        int current = GetCurrentCurrency();
        SetCurrency(current + amount);
    }
};

// Convenience functions
inline void InitializeCurrencyEditor() {
    CurrencyEditor::GetInstance().Initialize();
}

inline void UpdateCurrencyEditor() {
    CurrencyEditor::GetInstance().Update();
}

inline void SetCurrency(int amount) {
    CurrencyEditor::GetInstance().SetCurrency(amount);
}

inline void AddCurrency(int amount) {
    CurrencyEditor::GetInstance().AddCurrency(amount);
}

inline int GetCurrentCurrency() {
    return CurrencyEditor::GetInstance().GetCurrentCurrency();
}

} // namespace Items
} // namespace Features
