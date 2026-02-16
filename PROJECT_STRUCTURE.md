# Project Structure

Comprehensive overview of the NFL Custom Client codebase architecture.

## Directory Structure

```
NFL-Custom-Client/
├── .git/                      # Git repository data
├── .vs/                       # Visual Studio cache (gitignored)
├── bin/                       # Build output (gitignored)
│   └── Release/
│       └── NFL-Custom-Client.dll
├── obj/                       # Intermediate build files (gitignored)
├── docs/                      # Documentation
│   ├── BUILDING.md           # Build instructions
│   ├── FEATURES.md           # Feature documentation
│   └── USAGE.md              # User manual
├── loader/                    # DLL loader application
│   └── main.cpp              # Console-based injector
├── src/                       # Source code
│   ├── core/                 # Core systems
│   │   ├── hooks.h/cpp       # Function hooking (MinHook)
│   │   ├── memory.h          # Memory operations
│   │   ├── patterns.h        # Pattern scanning
│   │   └── unreal.h          # Unreal Engine utilities
│   ├── features/             # Feature implementations
│   │   ├── feature_manager.h # Centralized feature control
│   │   ├── player/           # Player-related features
│   │   │   └── godmode.h    # God mode implementation
│   │   ├── combat/           # Combat features (planned)
│   │   ├── movement/         # Movement features
│   │   │   ├── speed.h      # Speed modifier
│   │   │   ├── teleport.h   # Teleportation system
│   │   │   ├── jump.h       # Jump height (planned)
│   │   │   ├── flight.h     # Flight mode (planned)
│   │   │   └── noclip.h     # No-clip mode (planned)
│   │   ├── items/            # Item features
│   │   │   ├── currency.h   # Currency editor
│   │   │   ├── spawner.h    # Item spawner (planned)
│   │   │   └── inventory.h  # Inventory mods (planned)
│   │   ├── world/            # World features (planned)
│   │   ├── visual/           # Visual features (planned)
│   │   └── advanced/         # Advanced features (planned)
│   ├── ui/                   # User interface
│   │   ├── overlay.h         # DirectX 11 overlay
│   │   ├── menu.h            # ImGui menu system
│   │   └── themes.h          # UI themes (integrated)
│   ├── utils/                # Utility modules
│   │   ├── logger.h          # Logging system
│   │   ├── config.h          # Configuration management
│   │   └── hotkeys.h         # Hotkey system
│   └── dllmain.cpp           # Main entry point
├── vcpkg_installed/          # vcpkg dependencies (gitignored)
├── .gitignore                # Git ignore rules
├── config.example.json       # Example configuration
├── CONTRIBUTING.md           # Contribution guidelines
├── LICENSE                   # MIT License
├── NFL-Custom-Client.sln     # Visual Studio solution
├── NFL-Custom-Client.vcxproj # Visual Studio project
├── QUICKSTART.md             # Quick start guide
├── README.md                 # Main documentation
└── vcpkg.json                # vcpkg manifest
```

## Core Modules

### 1. Core Systems (`src/core/`)

#### `hooks.h` / `hooks.cpp`
**Purpose**: Function hooking using MinHook library.

**Key Components**:
- `Initialize()` - Initialize MinHook
- `Shutdown()` - Cleanup hooks
- `HookDirectX11()` - Hook D3D11 Present function
- `hkPresent()` - Present hook detour
- `hkResizeBuffers()` - ResizeBuffers hook detour

**Dependencies**: MinHook, DirectX 11

**Pattern**:
```cpp
namespace Hooks {
    inline bool Initialize();
    inline void Shutdown();
    inline bool HookDirectX11();
    
    HRESULT STDMETHODCALLTYPE hkPresent(...);
}
```

#### `memory.h`
**Purpose**: Safe memory operations and pattern scanning.

**Key Functions**:
- `Read<T>()` - Safe memory read with type
- `Write<T>()` - Safe memory write with protection
- `PatternScan()` - Find byte patterns in memory
- `PatternScanIDA()` - Scan with IDA-style patterns
- `FollowPointerChain()` - Resolve pointer chains
- `GetModuleBaseAddress()` - Get module base

**Pattern**:
```cpp
namespace Memory {
    template<typename T> T Read(uintptr_t address);
    template<typename T> bool Write(uintptr_t address, T value);
    uintptr_t PatternScanIDA(const std::string& pattern);
}
```

#### `patterns.h`
**Purpose**: Centralized pattern management.

**Key Components**:
- `GamePatterns` - Pattern definitions
- `FindPattern()` - Scan and cache pattern
- `GetPattern()` - Retrieve cached pattern
- `InitializePatterns()` - Scan all patterns

**Pattern Cache**: Stores found addresses to avoid repeated scanning.

#### `unreal.h`
**Purpose**: Unreal Engine specific utilities.

**Key Components**:
- `UObject` - Basic UE object structure
- `FName`, `FString` - UE string types
- `GetGObjects()` - Get global objects array
- `GetGNames()` - Get global names array
- `FindObject()` - Find UE object by name

**Note**: Requires game-specific implementation.

### 2. UI System (`src/ui/`)

#### `overlay.h`
**Purpose**: DirectX 11 overlay with ImGui rendering.

**Key Components**:
- `Initialize()` - Setup ImGui with D3D11
- `Render()` - Render loop
- `ToggleMenu()` - Show/hide menu
- `HandleResize()` - Handle window resize
- `SetupStyle()` - Apply UI theme

**Lifecycle**:
1. Present hook calls Initialize() on first frame
2. Every frame calls Render()
3. Render() draws menu and overlays
4. Shutdown() cleans up resources

#### `menu.h`
**Purpose**: Main menu interface with all features.

**Structure**:
- 8 tabs (Player, Combat, Movement, Items, World, Visual, Advanced, Settings)
- Feature toggles and sliders
- Configuration save/load
- About dialog

**Feature States**: Global state variables in `UI::FeatureStates` namespace.

### 3. Utilities (`src/utils/`)

#### `logger.h`
**Purpose**: File-based logging system.

**Features**:
- Log levels (DEBUG, INFO, WARN, ERROR)
- Timestamps on all log entries
- Thread-safe logging
- Auto-creates log directory
- Outputs to `%USERPROFILE%\Documents\NFL-Custom-Client\log.txt`

**Usage**:
```cpp
Logger::Log("Message", Logger::INFO);
Logger::Log("Error occurred", Logger::ERROR);
```

#### `config.h`
**Purpose**: JSON configuration management.

**Features**:
- Load/save JSON config
- Type-safe get/set operations
- Default config generation
- Thread-safe access
- Stores to `%USERPROFILE%\Documents\NFL-Custom-Client\config.json`

**Usage**:
```cpp
Config::Load();
float value = Config::Get("key", defaultValue);
Config::Set("key", value);
Config::Save();
```

#### `hotkeys.h`
**Purpose**: Customizable hotkey system.

**Features**:
- Register key callbacks
- Cooldown prevention
- Thread-safe processing
- Virtual key code support

**Usage**:
```cpp
Hotkeys::Register(VK_F5, []() {
    // Callback when F5 pressed
});
Hotkeys::Process(); // Call in main loop
```

### 4. Features (`src/features/`)

#### Architecture Pattern

All features follow this pattern:

```cpp
namespace Features {
namespace Category {

class FeatureName {
private:
    uintptr_t targetAddress = 0;
    bool isActive = false;
    
public:
    static FeatureName& GetInstance();
    
    void Initialize();  // Find patterns, setup
    void Update();      // Called every frame
    void Enable();      // Activate feature
    void Disable();     // Deactivate feature
};

// Convenience functions
inline void InitializeFeatureName();
inline void UpdateFeatureName();

} // namespace Category
} // namespace Features
```

#### `feature_manager.h`
**Purpose**: Centralized feature coordination.

**Responsibilities**:
- Initialize all features
- Update loop for active features
- Clean shutdown
- Coordination between features

**Usage**:
```cpp
Features::InitializeFeatures();  // Setup
Features::UpdateFeatures();      // Main loop
Features::ShutdownFeatures();    // Cleanup
```

#### Example: `player/godmode.h`

**Flow**:
1. `Initialize()` - Find health pattern, resolve address
2. `Update()` - Check if health decreased, restore if needed
3. `Enable()/Disable()` - Toggle feature on/off

**Integration**:
- Reads pattern from `Patterns::GetPattern("PLAYER_HEALTH")`
- Updates `UI::FeatureStates::godMode` for UI sync
- Logs all actions to logger

### 5. Main Entry Point

#### `dllmain.cpp`
**Purpose**: DLL entry point and initialization sequence.

**Initialization Order**:
1. Logger initialization
2. Config loading
3. Memory system setup
4. Pattern scanning
5. Unreal Engine interface
6. Hook initialization
7. DirectX 11 hooking
8. Feature initialization
9. Hotkey registration

**Main Loop**:
- Process hotkeys
- Update features
- Sleep to prevent CPU spinning

**Cleanup Order**:
1. Shutdown features
2. Save configuration
3. Shutdown UI
4. Clear hotkeys
5. Remove hooks
6. Close logger

### 6. Loader Application

#### `loader/main.cpp`
**Purpose**: Console-based DLL injector.

**Features**:
- Auto-detect game process
- Manual process selection
- CreateRemoteThread injection
- Error handling and status messages

**Flow**:
1. Find DLL in same directory
2. Find target process
3. Allocate memory in target
4. Write DLL path
5. Create remote thread with LoadLibraryW
6. Wait for completion

## Data Flow

### Feature Activation Flow

```
User clicks checkbox in UI
    ↓
UI updates FeatureStates
    ↓
Feature Update() detects state change
    ↓
Feature Enable() called
    ↓
Feature finds memory address (pattern)
    ↓
Feature modifies game memory
    ↓
Logs action to file
```

### Pattern Scanning Flow

```
InitializePatterns() called
    ↓
For each pattern in GamePatterns
    ↓
PatternScanIDA() scans memory
    ↓
Address resolved (RIP-relative, etc.)
    ↓
Address cached in g_patternCache
    ↓
Features query GetPattern()
```

### Rendering Flow

```
Game calls Present()
    ↓
Hook intercepts hkPresent()
    ↓
Initialize overlay (first call)
    ↓
ImGui NewFrame()
    ↓
Render menu (if visible)
    ↓
Render overlays (FPS, etc.)
    ↓
ImGui Render()
    ↓
Call original Present()
```

## Dependencies

### vcpkg Packages

1. **imgui[dx11-binding,win32-binding]**
   - Version: Latest
   - Purpose: UI rendering
   - Files: `imgui.h`, `imgui_impl_dx11.h`, `imgui_impl_win32.h`

2. **minhook**
   - Version: Latest
   - Purpose: Function hooking
   - Files: `MinHook.h`

3. **nlohmann-json**
   - Version: Latest
   - Purpose: JSON parsing
   - Files: `nlohmann/json.hpp`

### System Libraries

- `d3d11.lib` - DirectX 11
- `dxgi.lib` - DirectX Graphics Infrastructure
- `d3dcompiler.lib` - Shader compiler
- `user32.lib` - Windows user interface
- `kernel32.lib` - Windows kernel
- `shlwapi.lib` - Shell lightweight API
- `shell32.lib` - Windows shell
- `Psapi.lib` - Process status API

## Build Configuration

### Compiler Settings

- **Standard**: C++17 (`/std:c++17`)
- **Runtime**: Multi-threaded (`/MT`)
- **Optimization**: Maximize Speed (`/O2`)
- **Platform**: x64 only
- **Subsystem**: Windows

### Output

- **Type**: Dynamic Link Library (`.dll`)
- **Location**: `bin/Release/NFL-Custom-Client.dll`
- **Architecture**: x64 (64-bit)

## Memory Layout (Game-Specific)

### Player Structure (Example)
```
PlayerBase + 0x000: VTable
PlayerBase + 0x100: Health (float)
PlayerBase + 0x104: Max Health (float)
PlayerBase + 0x108: Stamina (float)
PlayerBase + 0x10C: Mana (float)
PlayerBase + 0x120: Position X (float)
PlayerBase + 0x124: Position Y (float)
PlayerBase + 0x128: Position Z (float)
```

**Note**: These offsets are examples and must be found for the actual game.

## Extension Points

### Adding New Features

1. Create header in appropriate `features/` subdirectory
2. Follow the standard feature pattern (see above)
3. Add to `feature_manager.h`
4. Add UI elements to `menu.h`
5. Update documentation

### Adding New Patterns

1. Find pattern in game using x64dbg/Cheat Engine
2. Add to `GamePatterns` struct in `patterns.h`
3. Add to `InitializePatterns()` function
4. Use in feature: `Patterns::GetPattern("PATTERN_NAME")`

### Adding New UI Tabs

1. Add tab button in `menu.h` `Render()`:
   ```cpp
   if (ImGui::BeginTabItem("TabName")) {
       RenderTabName();
       ImGui::EndTabItem();
   }
   ```
2. Implement `RenderTabName()` method
3. Add feature states to `UI::FeatureStates`

## Testing Strategy

### Manual Testing Checklist

- [ ] DLL builds without errors
- [ ] DLL injects successfully
- [ ] Menu opens with INSERT key
- [ ] All tabs render correctly
- [ ] Features toggle on/off
- [ ] Config saves and loads
- [ ] Hotkeys work
- [ ] Logs write correctly
- [ ] DLL unloads cleanly (END key)
- [ ] No memory leaks (check Task Manager)

### Debug Techniques

1. **Check Logs**: First step for any issue
2. **Output Debug String**: Use `OutputDebugStringA()` for real-time debug
3. **Breakpoints**: Attach Visual Studio debugger to game process
4. **Memory Dumps**: Use Process Hacker to examine memory

## Performance Considerations

### Critical Path

- Feature `Update()` loops run every ~10ms
- Keep operations lightweight
- Cache frequently accessed values
- Avoid allocations in hot paths

### Memory Usage

- Pattern cache: ~10KB
- ImGui state: ~1-2MB
- Total DLL size: ~500KB-2MB

## Security Considerations

### Memory Safety

- All memory reads/writes include null checks
- VirtualProtect used before writing
- IsBadReadPtr/IsBadWritePtr validation

### Thread Safety

- Mutexes used for shared resources
- Logger is thread-safe
- Config is thread-safe
- Hotkeys use mutex

## Future Improvements

### Planned Features

- Lua script executor
- Memory scanner (Cheat Engine-like)
- Auto-updater for patterns
- GUI loader application
- Multi-profile support
- Network sync (careful with this)

### Code Quality

- Add unit tests
- Add automated build CI
- Add code coverage
- Improve error handling
- Add more documentation

---

*Last Updated: 2026-02-16*  
*Version: 1.0*
