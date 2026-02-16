# NFL Custom Client

A comprehensive C++ DLL enhancement framework for **FANTASY LIFE i: The Girl Who Steals Time** featuring 35+ gameplay modifications and utilities.

![Version](https://img.shields.io/badge/version-1.0-blue)
![Platform](https://img.shields.io/badge/platform-Windows%20x64-lightgrey)
![C++](https://img.shields.io/badge/C%2B%2B-17-orange)

## ⚠️ Legal Disclaimer

**This project is for educational purposes only.** It is designed for use with "FANTASY LIFE i: The Girl Who Steals Time", a game owned by the developer's family. This toolkit is intended for **single-player use only** to learn about:

- Game engine internals (Unreal Engine)
- Memory management and pattern scanning
- DirectX 11 programming and overlays
- Function hooking and detours
- GUI development with Dear ImGui

**Do not use this on games you do not own or in multiplayer environments. Respect intellectual property and terms of service.**

## 🚀 Features

### 🎮 Player Features
- **God Mode** - Invincibility to all damage
- **Infinite Stamina** - Never run out of energy
- **Infinite Mana/MP** - Unlimited magic power
- **Stats Editor** - Modify HP, Attack, Defense, Magic, etc.
- **Level Editor** - Change character level instantly

### ⚔️ Combat Features
- **One-Hit Kill** - Defeat enemies in a single strike
- **Damage Multiplier** - Scale damage output (1x to 100x)

### 🏃 Movement Features
- **Speed Multiplier** - Adjust movement speed (0.1x to 10x)
- **Jump Height Modifier** - Enhance jump capabilities (1x to 20x)
- **Flight Mode** - Disable gravity and fly freely
- **No-Clip Mode** - Walk through walls and objects
- **Teleportation System** - Save/load positions, manual coordinate input

### 🎒 Item Features
- **Item Spawner** - Generate items by ID
- **Currency Editor** - Modify money/gold amounts
- **Inventory Tools** - Remove weight limits, unlock slots
- **Item Duplication** - Duplicate selected items

### 🌍 World Features
- **Time Control** - Freeze, speed up, or slow down time
- **Weather Control** - Change weather conditions
- **Day/Night Cycle** - Adjust time of day

### 👁️ Visual Features
- **ESP/Wallhack** - See enemies through walls
- **FOV Changer** - Adjust field of view (60° to 120°)
- **Free Camera** - Detach camera from player
- **Custom HUD** - Toggle UI elements, screenshot mode

### 🔧 Advanced Features
- **Debug Console** - Access Unreal Engine console
- **Script Executor** - Run custom scripts
- **Memory Scanner** - Search and modify memory values

## 📋 Prerequisites

- Windows 10/11 (x64)
- Visual Studio 2022 or later
- [vcpkg](https://vcpkg.io/) package manager
- FANTASY LIFE i game installed

## 🛠️ Building from Source

### 1. Install vcpkg

```bash
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg integrate install
```

### 2. Clone Repository

```bash
git clone https://github.com/jhellolag-sketch/NFL-Custom-Client.git
cd NFL-Custom-Client
```

### 3. Build with Visual Studio

1. Open `NFL-Custom-Client.sln` in Visual Studio 2022
2. Select **Release | x64** configuration
3. Build → Build Solution (F7)
4. DLL will be in `bin\Release\NFL-Custom-Client.dll`

### Dependencies (Auto-installed via vcpkg)

- **imgui** - UI framework with DirectX 11 bindings
- **minhook** - Function hooking library
- **nlohmann-json** - JSON configuration handling

## 📖 Usage

### Loading the DLL

1. **Option A: Manual Injection**
   - Use a DLL injector (e.g., Extreme Injector, Process Hacker)
   - Inject `NFL-Custom-Client.dll` into running game process

2. **Option B: Loader Application** *(Coming Soon)*
   - Run the included loader executable
   - Select game process
   - Click "Inject"

### Controls

| Key | Action |
|-----|--------|
| `INSERT` | Toggle main menu |
| `F5` | Save teleport position |
| `F6` | Load teleport position |
| `END` | Unload DLL |

### Configuration

Config file location: `%USERPROFILE%\Documents\NFL-Custom-Client\config.json`

Settings are automatically saved when you close the menu or unload the DLL.

## 🖼️ Screenshots

*Coming Soon*

## 🏗️ Project Structure

```
NFL-Custom-Client/
├── src/
│   ├── core/           # Core systems (hooks, memory, UE utilities)
│   ├── ui/             # User interface (ImGui overlay & menu)
│   ├── features/       # Feature implementations
│   │   ├── player/
│   │   ├── combat/
│   │   ├── movement/
│   │   ├── items/
│   │   ├── world/
│   │   ├── visual/
│   │   └── advanced/
│   ├── utils/          # Utilities (logger, config, hotkeys)
│   └── dllmain.cpp     # Entry point
├── docs/               # Documentation
├── loader/             # DLL loader application
└── vcpkg.json          # Package dependencies
```

## 📚 Documentation

- [Features Guide](docs/FEATURES.md) - Detailed feature documentation
- [Building Guide](docs/BUILDING.md) - Complete build instructions
- [Usage Guide](docs/USAGE.md) - User manual and FAQ

## 🤝 Contributing

This is an educational project. Contributions are welcome! Please:

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Submit a pull request

## 📝 License

This project is licensed under the MIT License - see [LICENSE](LICENSE) file for details.

## 🙏 Credits

- **Built with AI assistance** - Demonstrating AI-assisted software development
- **Dear ImGui** - Excellent immediate mode GUI library
- **MinHook** - Powerful x86/x64 hooking library
- **nlohmann/json** - Modern C++ JSON library

## ⚡ Technical Details

- **Language**: C++17
- **Platform**: Windows x64
- **Target Engine**: Unreal Engine
- **UI Framework**: Dear ImGui (DirectX 11)
- **Hooking**: MinHook
- **Build System**: MSBuild / Visual Studio 2022
- **Package Manager**: vcpkg

## 🔒 Security

- Patterns are game-specific and require updates for different versions
- All memory operations include safety checks
- No data is transmitted externally
- Config files are stored locally

## ❓ FAQ

**Q: Is this safe to use?**  
A: The framework includes safety checks, but as with any memory manipulation tool, use at your own risk on your own games.

**Q: Will this work with multiplayer?**  
A: **NO.** This is designed for single-player use only. Using cheats in multiplayer is unethical and may result in bans.

**Q: The patterns don't work!**  
A: Patterns are game version-specific. They need to be updated when the game updates. See `src/core/patterns.h`.

**Q: How do I find game patterns?**  
A: Use tools like Cheat Engine, x64dbg, or Ghidra to reverse engineer and find memory patterns.

## 🚧 Roadmap

- [x] Core framework implementation
- [x] UI system with ImGui
- [x] Configuration system
- [ ] Complete all 35+ features
- [ ] DLL loader application
- [ ] Auto-updater for patterns
- [ ] Script library/presets
- [ ] Video tutorials

## 📞 Support

For issues, questions, or suggestions:
- Open an [Issue](https://github.com/jhellolag-sketch/NFL-Custom-Client/issues)
- Check existing documentation in `docs/`

---

**Remember: Use responsibly and ethically. This tool is for learning and personal use on games you own.** 🎮

Built with ❤️ and AI assistance.

