#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <string>
#include <vector>

// Simple console-based DLL loader for NFL Custom Client

class ProcessHelper {
public:
    static DWORD GetProcessIdByName(const std::wstring& processName) {
        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hSnapshot == INVALID_HANDLE_VALUE) {
            return 0;
        }

        PROCESSENTRY32W pe32;
        pe32.dwSize = sizeof(PROCESSENTRY32W);

        if (!Process32FirstW(hSnapshot, &pe32)) {
            CloseHandle(hSnapshot);
            return 0;
        }

        do {
            if (_wcsicmp(pe32.szExeFile, processName.c_str()) == 0) {
                CloseHandle(hSnapshot);
                return pe32.th32ProcessID;
            }
        } while (Process32NextW(hSnapshot, &pe32));

        CloseHandle(hSnapshot);
        return 0;
    }

    static std::vector<std::pair<DWORD, std::wstring>> GetAllProcesses() {
        std::vector<std::pair<DWORD, std::wstring>> processes;
        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        
        if (hSnapshot == INVALID_HANDLE_VALUE) {
            return processes;
        }

        PROCESSENTRY32W pe32;
        pe32.dwSize = sizeof(PROCESSENTRY32W);

        if (Process32FirstW(hSnapshot, &pe32)) {
            do {
                processes.push_back({ pe32.th32ProcessID, pe32.szExeFile });
            } while (Process32NextW(hSnapshot, &pe32));
        }

        CloseHandle(hSnapshot);
        return processes;
    }
};

class DllInjector {
public:
    static bool InjectDLL(DWORD processId, const std::wstring& dllPath) {
        // Open target process
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
        if (!hProcess) {
            std::wcerr << L"Failed to open process. Error: " << GetLastError() << std::endl;
            return false;
        }

        // Allocate memory in target process
        SIZE_T pathSize = (dllPath.length() + 1) * sizeof(wchar_t);
        LPVOID pRemoteMemory = VirtualAllocEx(hProcess, NULL, pathSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        
        if (!pRemoteMemory) {
            std::wcerr << L"Failed to allocate memory in target process. Error: " << GetLastError() << std::endl;
            CloseHandle(hProcess);
            return false;
        }

        // Write DLL path to target process
        if (!WriteProcessMemory(hProcess, pRemoteMemory, dllPath.c_str(), pathSize, NULL)) {
            std::wcerr << L"Failed to write to process memory. Error: " << GetLastError() << std::endl;
            VirtualFreeEx(hProcess, pRemoteMemory, 0, MEM_RELEASE);
            CloseHandle(hProcess);
            return false;
        }

        // Get LoadLibraryW address
        HMODULE hKernel32 = GetModuleHandleW(L"kernel32.dll");
        LPVOID pLoadLibraryW = (LPVOID)GetProcAddress(hKernel32, "LoadLibraryW");

        if (!pLoadLibraryW) {
            std::wcerr << L"Failed to get LoadLibraryW address. Error: " << GetLastError() << std::endl;
            VirtualFreeEx(hProcess, pRemoteMemory, 0, MEM_RELEASE);
            CloseHandle(hProcess);
            return false;
        }

        // Create remote thread
        HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, 
            (LPTHREAD_START_ROUTINE)pLoadLibraryW, pRemoteMemory, 0, NULL);

        if (!hThread) {
            std::wcerr << L"Failed to create remote thread. Error: " << GetLastError() << std::endl;
            VirtualFreeEx(hProcess, pRemoteMemory, 0, MEM_RELEASE);
            CloseHandle(hProcess);
            return false;
        }

        // Wait for thread to complete
        WaitForSingleObject(hThread, INFINITE);

        // Cleanup
        VirtualFreeEx(hProcess, pRemoteMemory, 0, MEM_RELEASE);
        CloseHandle(hThread);
        CloseHandle(hProcess);

        return true;
    }
};

void PrintHeader() {
    std::wcout << L"================================================\n";
    std::wcout << L"       NFL Custom Client - DLL Loader\n";
    std::wcout << L"       FANTASY LIFE i Enhancement Tool\n";
    std::wcout << L"================================================\n\n";
}

void PrintUsage() {
    std::wcout << L"Usage:\n";
    std::wcout << L"  1. Auto-detect and inject into game\n";
    std::wcout << L"  2. Manual process selection\n";
    std::wcout << L"  3. Exit\n\n";
}

int main() {
    SetConsoleTitleW(L"NFL Custom Client Loader");
    PrintHeader();

    // Get DLL path (assuming it's in the same directory)
    wchar_t dllPath[MAX_PATH];
    GetModuleFileNameW(NULL, dllPath, MAX_PATH);
    std::wstring dllFullPath = dllPath;
    size_t lastSlash = dllFullPath.find_last_of(L"\\/");
    if (lastSlash != std::wstring::npos) {
        dllFullPath = dllFullPath.substr(0, lastSlash + 1);
    }
    dllFullPath += L"NFL-Custom-Client.dll";

    // Check if DLL exists
    if (GetFileAttributesW(dllFullPath.c_str()) == INVALID_FILE_ATTRIBUTES) {
        std::wcerr << L"Error: NFL-Custom-Client.dll not found in the same directory!\n";
        std::wcerr << L"Expected path: " << dllFullPath << L"\n\n";
        std::wcout << L"Press any key to exit...";
        std::cin.get();
        return 1;
    }

    std::wcout << L"DLL Path: " << dllFullPath << L"\n\n";

    while (true) {
        PrintUsage();
        std::wcout << L"Select option: ";
        
        int choice;
        std::wcin >> choice;
        std::wcin.ignore();

        if (choice == 3) {
            std::wcout << L"\nExiting...\n";
            break;
        }

        if (choice == 1) {
            // Auto-detect game process
            std::wcout << L"\nSearching for game process...\n";
            
            // Try common game executable names
            const wchar_t* possibleNames[] = { 
                L"NF1.exe", 
                L"FantasyLife.exe", 
                L"FANTASY_LIFE.exe",
                L"FantasyLifeI.exe"
            };

            DWORD processId = 0;
            std::wstring foundProcess;

            for (const wchar_t* name : possibleNames) {
                processId = ProcessHelper::GetProcessIdByName(name);
                if (processId != 0) {
                    foundProcess = name;
                    break;
                }
            }

            if (processId == 0) {
                std::wcout << L"Game process not found. Please start the game first.\n\n";
                continue;
            }

            std::wcout << L"Found: " << foundProcess << L" (PID: " << processId << L")\n";
            std::wcout << L"Injecting DLL...\n";

            if (DllInjector::InjectDLL(processId, dllFullPath)) {
                std::wcout << L"\n[SUCCESS] DLL injected successfully!\n";
                std::wcout << L"Press INSERT in-game to open menu.\n";
                std::wcout << L"Press END in-game to unload.\n\n";
            } else {
                std::wcerr << L"\n[FAILED] DLL injection failed!\n";
                std::wcerr << L"Make sure you're running this as Administrator.\n\n";
            }

        } else if (choice == 2) {
            // Manual process selection
            std::wcout << L"\nEnter process name (e.g., NF1.exe): ";
            std::wstring processName;
            std::getline(std::wcin, processName);

            DWORD processId = ProcessHelper::GetProcessIdByName(processName);
            
            if (processId == 0) {
                std::wcout << L"Process not found: " << processName << L"\n\n";
                continue;
            }

            std::wcout << L"Found: " << processName << L" (PID: " << processId << L")\n";
            std::wcout << L"Injecting DLL...\n";

            if (DllInjector::InjectDLL(processId, dllFullPath)) {
                std::wcout << L"\n[SUCCESS] DLL injected successfully!\n";
                std::wcout << L"Press INSERT in-game to open menu.\n";
                std::wcout << L"Press END in-game to unload.\n\n";
            } else {
                std::wcerr << L"\n[FAILED] DLL injection failed!\n";
                std::wcerr << L"Make sure you're running this as Administrator.\n\n";
            }

        } else {
            std::wcout << L"Invalid choice. Please try again.\n\n";
        }
    }

    return 0;
}
