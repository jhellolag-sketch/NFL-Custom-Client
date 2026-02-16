# Quick Start Guide

Get started with NFL Custom Client in 5 minutes!

## Prerequisites

- Windows 10/11 (64-bit)
- FANTASY LIFE i game installed
- Visual Studio 2022 (for building from source)
- OR pre-built DLL (if available)

## Method 1: Using Pre-Built DLL (Easiest)

### Step 1: Download
Download the latest release from [Releases](https://github.com/jhellolag-sketch/NFL-Custom-Client/releases):
- `NFL-Custom-Client.dll`
- `NFL-Loader.exe` (optional)

### Step 2: Launch Game
Start FANTASY LIFE i and get to the main menu or in-game.

### Step 3: Inject DLL

**Option A: Using the Loader (Recommended)**
1. Run `NFL-Loader.exe` as Administrator
2. It will auto-detect the game
3. Press 1 to inject
4. Wait for success message

**Option B: Using Extreme Injector**
1. Download [Extreme Injector](https://github.com/master131/ExtremeInjector)
2. Run as Administrator
3. Select game process from dropdown
4. Browse to `NFL-Custom-Client.dll`
5. Click "Inject"

### Step 4: Use the Menu
1. Press `INSERT` to open menu
2. Enable features you want
3. Press `INSERT` again to close menu
4. Press `END` to unload when done

## Method 2: Building from Source

### Step 1: Install Dependencies

```powershell
# Install vcpkg
git clone https://github.com/Microsoft/vcpkg.git C:\vcpkg
cd C:\vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg integrate install
```

### Step 2: Clone and Build

```powershell
# Clone repository
git clone https://github.com/jhellolag-sketch/NFL-Custom-Client.git
cd NFL-Custom-Client

# Open in Visual Studio
start NFL-Custom-Client.sln

# Or build with MSBuild
msbuild NFL-Custom-Client.sln /p:Configuration=Release /p:Platform=x64
```

### Step 3: Locate DLL
Built DLL will be in: `bin\Release\NFL-Custom-Client.dll`

### Step 4: Inject and Use
Follow steps 2-4 from Method 1 above.

## First-Time Setup

### 1. Test Basic Features
Start with safe features:
- Open menu (`INSERT`)
- Try "Show FPS" in Visual tab
- Adjust FOV slightly (85-95)
- Test speed multiplier at 1.5x

### 2. Save Your Configuration
- Enable features you like
- Click "Save Config" button
- Config saves to `%USERPROFILE%\Documents\NFL-Custom-Client\config.json`

### 3. Check Logs
If something doesn't work:
- Check `%USERPROFILE%\Documents\NFL-Custom-Client\log.txt`
- Look for errors or warnings
- Patterns may need updating for your game version

## Common First-Time Issues

### Menu Doesn't Appear
- Make sure DLL actually injected (check injector status)
- Try pressing INSERT multiple times
- Check if antivirus blocked the DLL
- Run injector as Administrator

### Features Don't Work
- Most features require game-specific patterns
- Check logs for pattern scanning results
- Patterns in code are examples and need updating for your game
- See [Pattern Finding Guide](docs/FEATURES.md#finding-patterns)

### Game Crashes
- Start with one feature at a time
- Avoid extreme multiplier values initially
- Make sure your game version matches expected version
- Check logs before crash

## Recommended First Features to Try

### Safe to Test (Low Risk)
1. **FOV Changer** - Visual only, no game state change
2. **Speed 1.5x** - Slight boost, easy to control
3. **Show FPS** - Display only

### Medium Risk (Save First!)
1. **God Mode** - Prevents death (save game first)
2. **Teleport** - Save position before testing
3. **Currency Edit** - Backup save file first

### Advanced (Experienced Users)
1. **No-Clip** - Can fall through world
2. **Flight Mode** - Can get stuck in geometry
3. **One-Hit Kill** - May break boss fights

## Hotkeys Quick Reference

| Key | Function |
|-----|----------|
| `INSERT` | Toggle Menu |
| `F5` | Save Position |
| `F6` | Load Position |
| `END` | Unload DLL |

## Getting Help

### Check These First
1. **Log File**: `%USERPROFILE%\Documents\NFL-Custom-Client\log.txt`
2. **Config**: `%USERPROFILE%\Documents\NFL-Custom-Client\config.json`
3. **Documentation**: [docs/](docs/) folder

### Still Need Help?
- Read the [Full Usage Guide](docs/USAGE.md)
- Check [FAQ](docs/USAGE.md#faq)
- Review [Features Documentation](docs/FEATURES.md)
- Open an [Issue](https://github.com/jhellolag-sketch/NFL-Custom-Client/issues)

## Tips for Best Experience

### Do's ✅
- Backup game saves before using
- Start with low multiplier values
- Save config after finding good settings
- Check logs when troubleshooting
- Test in safe game areas first

### Don'ts ❌
- Don't use extreme values immediately
- Don't forget to save your game
- Don't ignore errors in logs
- Don't use on games you don't own
- Don't inject multiple times without restarting

## Next Steps

Once you're comfortable with basic usage:

1. **Read Full Docs**: Check [docs/USAGE.md](docs/USAGE.md) for advanced features
2. **Customize**: Edit hotkeys in config.json
3. **Explore**: Try different feature combinations
4. **Contribute**: Report bugs or suggest features

## Need More Info?

- **Full Documentation**: See [docs/](docs/) folder
- **Building Guide**: See [docs/BUILDING.md](docs/BUILDING.md)
- **Feature Details**: See [docs/FEATURES.md](docs/FEATURES.md)
- **Main README**: See [README.md](README.md)

---

**Happy modding! Remember to use responsibly and only on games you own.** 🎮

*Last Updated: 2026-02-16*
