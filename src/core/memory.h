#pragma once

#include <Windows.h>
#include <vector>
#include <string>
#include <sstream>
#include <cstdint>
#include <Psapi.h>

#pragma comment(lib, "Psapi.lib")

namespace Memory {

// Get module base address
inline uintptr_t GetModuleBaseAddress(const char* moduleName = nullptr) {
    if (moduleName == nullptr) {
        return reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr));
    }
    return reinterpret_cast<uintptr_t>(GetModuleHandleA(moduleName));
}

// Get module size
inline SIZE_T GetModuleSize(const char* moduleName = nullptr) {
    HMODULE hModule = moduleName ? GetModuleHandleA(moduleName) : GetModuleHandleA(nullptr);
    if (!hModule) return 0;

    MODULEINFO modInfo;
    if (GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(MODULEINFO))) {
        return modInfo.SizeOfImage;
    }
    return 0;
}

// Safe memory read
template<typename T>
inline T Read(uintptr_t address) {
    if (IsBadReadPtr(reinterpret_cast<void*>(address), sizeof(T))) {
        return T{};
    }
    
    try {
        return *reinterpret_cast<T*>(address);
    } catch (...) {
        return T{};
    }
}

// Safe memory write
template<typename T>
inline bool Write(uintptr_t address, T value) {
    if (IsBadWritePtr(reinterpret_cast<void*>(address), sizeof(T))) {
        return false;
    }

    try {
        DWORD oldProtect;
        if (VirtualProtect(reinterpret_cast<void*>(address), sizeof(T), PAGE_EXECUTE_READWRITE, &oldProtect)) {
            *reinterpret_cast<T*>(address) = value;
            VirtualProtect(reinterpret_cast<void*>(address), sizeof(T), oldProtect, &oldProtect);
            return true;
        }
    } catch (...) {}

    return false;
}

// Pattern scanning
inline uintptr_t PatternScan(const char* signature, const char* mask, uintptr_t startAddress = 0, size_t searchSize = 0) {
    if (startAddress == 0) {
        startAddress = GetModuleBaseAddress();
    }
    
    if (searchSize == 0) {
        searchSize = GetModuleSize();
    }

    size_t patternLength = strlen(mask);
    
    for (size_t i = 0; i < searchSize - patternLength; i++) {
        bool found = true;
        for (size_t j = 0; j < patternLength; j++) {
            if (mask[j] != '?' && signature[j] != Read<char>(startAddress + i + j)) {
                found = false;
                break;
            }
        }
        if (found) {
            return startAddress + i;
        }
    }

    return 0;
}

// Pattern scan with IDA style pattern (e.g., "48 8B 05 ? ? ? ? 48 85 C0")
inline uintptr_t PatternScanIDA(const std::string& pattern, uintptr_t startAddress = 0, size_t searchSize = 0) {
    if (startAddress == 0) {
        startAddress = GetModuleBaseAddress();
    }
    
    if (searchSize == 0) {
        searchSize = GetModuleSize();
    }

    std::vector<uint8_t> bytes;
    std::vector<bool> mask;

    // Parse pattern
    std::istringstream iss(pattern);
    std::string token;
    while (iss >> token) {
        if (token == "??" || token == "?") {
            bytes.push_back(0);
            mask.push_back(false);
        } else {
            bytes.push_back(static_cast<uint8_t>(std::stoul(token, nullptr, 16)));
            mask.push_back(true);
        }
    }

    // Search
    for (size_t i = 0; i < searchSize - bytes.size(); i++) {
        bool found = true;
        for (size_t j = 0; j < bytes.size(); j++) {
            if (mask[j] && bytes[j] != Read<uint8_t>(startAddress + i + j)) {
                found = false;
                break;
            }
        }
        if (found) {
            return startAddress + i;
        }
    }

    return 0;
}

// Follow pointer chain
inline uintptr_t FollowPointerChain(uintptr_t base, const std::vector<uintptr_t>& offsets) {
    uintptr_t address = base;
    
    for (size_t i = 0; i < offsets.size(); i++) {
        address = Read<uintptr_t>(address);
        if (address == 0) return 0;
        
        if (i < offsets.size() - 1 || offsets.size() == 1) {
            address += offsets[i];
        }
    }
    
    return address;
}

// Read string from memory
inline std::string ReadString(uintptr_t address, size_t maxLength = 256) {
    if (IsBadReadPtr(reinterpret_cast<void*>(address), maxLength)) {
        return "";
    }

    std::string result;
    for (size_t i = 0; i < maxLength; i++) {
        char c = Read<char>(address + i);
        if (c == '\0') break;
        result += c;
    }
    return result;
}

// Write string to memory
inline bool WriteString(uintptr_t address, const std::string& str) {
    DWORD oldProtect;
    size_t size = str.length() + 1;
    
    if (VirtualProtect(reinterpret_cast<void*>(address), size, PAGE_EXECUTE_READWRITE, &oldProtect)) {
        memcpy(reinterpret_cast<void*>(address), str.c_str(), size);
        VirtualProtect(reinterpret_cast<void*>(address), size, oldProtect, &oldProtect);
        return true;
    }
    
    return false;
}

// Nop instruction(s)
inline bool Nop(uintptr_t address, size_t size) {
    DWORD oldProtect;
    if (VirtualProtect(reinterpret_cast<void*>(address), size, PAGE_EXECUTE_READWRITE, &oldProtect)) {
        memset(reinterpret_cast<void*>(address), 0x90, size); // 0x90 = NOP
        VirtualProtect(reinterpret_cast<void*>(address), size, oldProtect, &oldProtect);
        return true;
    }
    return false;
}

// Patch bytes
inline bool Patch(uintptr_t address, const std::vector<uint8_t>& bytes) {
    DWORD oldProtect;
    if (VirtualProtect(reinterpret_cast<void*>(address), bytes.size(), PAGE_EXECUTE_READWRITE, &oldProtect)) {
        memcpy(reinterpret_cast<void*>(address), bytes.data(), bytes.size());
        VirtualProtect(reinterpret_cast<void*>(address), bytes.size(), oldProtect, &oldProtect);
        return true;
    }
    return false;
}

} // namespace Memory
