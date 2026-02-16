# Usage Guide

Complete user manual for NFL Custom Client.

## Table of Contents

1. [Quick Start](#quick-start)
2. [Installation](#installation)
3. [Loading the DLL](#loading-the-dll)
4. [Menu Navigation](#menu-navigation)
5. [Feature Usage](#feature-usage)
6. [Configuration](#configuration)
7. [Hotkeys](#hotkeys)
8. [Tips & Tricks](#tips--tricks)
9. [FAQ](#faq)
10. [Troubleshooting](#troubleshooting)

---

## Quick Start

**5-Minute Setup:**

1. Build or download `NFL-Custom-Client.dll`
2. Launch FANTASY LIFE i game
3. Inject DLL using your preferred injector
4. Press `INSERT` to open menu
5. Enable desired features
6. Press `END` to unload when done

---

## Installation

### Prerequisites

- Windows 10/11 (64-bit)
- FANTASY LIFE i: The Girl Who Steals Time (installed and working)
- DLL injector (see recommendations below)

### Files You Need

- `NFL-Custom-Client.dll` - The main DLL file

### Recommended Injectors

**Option 1: Extreme Injector v3**
- Free, open-source
- Download: [GitHub](https://github.com/master131/ExtremeInjector)
- Easy to use, good for beginners

**Option 2: Process Hacker 2**
- Free, open-source
- Download: [Official Site](https://processhacker.sourceforge.io/)
- Advanced features, more control

**Option 3: Xenos Injector**
- Free
- Multiple injection methods
- Advanced users

---

## Loading the DLL

### Method 1: Using Extreme Injector

1. Launch FANTASY LIFE i game
2. Run Extreme Injector as Administrator
3. In "Process" dropdown, select game process (usually `NF1.exe` or similar)
4. Click "Add DLL" and browse to `NFL-Custom-Client.dll`
5. Select injection method: "Standard Injection"
6. Click "Inject"
7. Status should show "Injected successfully"

### Method 2: Using Process Hacker

1. Launch FANTASY LIFE i game
2. Open Process Hacker as Administrator
3. Find game process in list (right-click → Properties to verify)
4. Right-click process → Miscellaneous → Inject DLL
5. Browse to `NFL-Custom-Client.dll`
6. Click "Inject"

### Method 3: Manual Loader (Coming Soon)

A dedicated loader application will be provided in future updates.

### Verification

After injection, check for successful load:

1. Press `INSERT` - Menu should appear
2. Check log file: `%USERPROFILE%\Documents\NFL-Custom-Client\log.txt`
3. Look for initialization messages

**Example log output:**
```
[2026-02-16 15:30:00] [INFO] === NFL Custom Client Logger Initialized ===
[2026-02-16 15:30:00] [INFO] [+] NFL Custom Client v1.0 loaded
[2026-02-16 15:30:01] [INFO] [+] All systems initialized successfully
[2026-02-16 15:30:01] [INFO] [*] Press INSERT to open menu
```

---

## Menu Navigation

### Opening the Menu

- Press `INSERT` key
- Menu appears as an overlay on game screen
- Press `INSERT` again to close

### Menu Layout

The menu consists of 8 main tabs:

1. **Player** - God mode, stamina, stats
2. **Combat** - Damage modifiers, one-hit kill
3. **Movement** - Speed, flight, teleport
4. **Items** - Item spawner, currency
5. **World** - Time, weather control
6. **Visual** - ESP, FOV, camera
7. **Advanced** - Console, scanner, scripts
8. **Settings** - Hotkeys, config, about

### Controls

- **Mouse**: Click to interact with UI elements
- **Keyboard**: Type in input fields
- **Tab**: Navigate between elements (when supported)
- **Escape**: Does NOT close menu (prevents accidental closes)
- **INSERT**: Toggle menu visibility

### UI Elements

**Checkboxes**: Click to toggle features on/off  
**Sliders**: Click and drag to adjust values  
**Buttons**: Click to perform actions  
**Input Fields**: Click and type values  
**Dropdowns**: Click to show options, click option to select  

---

## Feature Usage

### Basic Features

#### Enabling God Mode

1. Open menu (`INSERT`)
2. Click "Player" tab
3. Check "God Mode"
4. You are now invincible

#### Changing Movement Speed

1. Open menu (`INSERT`)
2. Click "Movement" tab
3. Drag "Speed Multiplier" slider
4. Move around to test

#### Modifying Currency

1. Open menu (`INSERT`)
2. Click "Items" tab
3. Enter amount in "Currency Amount" field
4. Click "Set Currency"
5. Open game inventory to verify

### Advanced Features

#### Using Teleportation

**Quick Save/Load:**
1. Stand at location you want to save
2. Press `F5` (or click "Save Position" in Movement tab)
3. Move somewhere else
4. Press `F6` (or click "Load Position") to return

**Manual Coordinates:**
1. Open menu → Movement tab
2. Enter X, Y, Z coordinates
3. Click "Teleport to Coordinates"
4. Character instantly moves to that location

**Tips:**
- Save multiple positions by noting down coordinates
- Use with No-Clip to explore unreachable areas
- Combine with Flight for safety

#### Spawning Items

1. Open menu → Items tab
2. Find Item ID (see [Finding Item IDs](#finding-item-ids))
3. Enter Item ID in field
4. Enter quantity (1-999)
5. Click "Spawn Item"
6. Check inventory

#### Time Control

**Freeze Time:**
1. Open menu → World tab
2. Check "Freeze Time"
3. Time stops (useful for timed puzzles)

**Speed Up Time:**
1. Open menu → World tab
2. Click "Fast (5x)" or "Very Fast (10x)"
3. Time moves faster

**Custom Speed:**
1. Use "Time Speed" slider for precise control
2. Values below 1.0 slow down time
3. Values above 1.0 speed up time

---

## Configuration

### Config File Location

```
%USERPROFILE%\Documents\NFL-Custom-Client\config.json
```

Example path: `C:\Users\YourName\Documents\NFL-Custom-Client\config.json`

### Config Structure

```json
{
  "ui": {
    "theme": "dark",
    "show_fps": false,
    "opacity": 0.95
  },
  "hotkeys": {
    "toggle_menu": 45,
    "teleport_save": 116,
    "teleport_load": 117,
    "unload": 35
  },
  "features": {
    "god_mode": false,
    "infinite_stamina": false,
    "speed_multiplier": 1.0,
    "damage_multiplier": 1.0
  },
  "teleport": {
    "saved_positions": []
  }
}
```

### Saving Configuration

**Automatic:**
- Config auto-saves when you unload DLL (press `END`)

**Manual:**
- Open menu → Click "Save Config" button
- Or press "Save Config" in Settings tab

### Loading Configuration

**Automatic:**
- Config auto-loads when DLL is injected

**Manual:**
- Open menu → Click "Load Config" button

### Resetting Configuration

1. Close game and unload DLL
2. Delete `config.json` file
3. Reload DLL - default config will be created

### Config Backup

Recommended: Keep backups of your config

```powershell
# Backup
copy "%USERPROFILE%\Documents\NFL-Custom-Client\config.json" "%USERPROFILE%\Documents\NFL-Custom-Client\config.backup.json"

# Restore
copy "%USERPROFILE%\Documents\NFL-Custom-Client\config.backup.json" "%USERPROFILE%\Documents\NFL-Custom-Client\config.json"
```

---

## Hotkeys

### Default Hotkeys

| Key | Function | Customizable |
|-----|----------|--------------|
| `INSERT` | Toggle Menu | ✅ Yes |
| `F5` | Save Teleport Position | ✅ Yes |
| `F6` | Load Teleport Position | ✅ Yes |
| `END` | Unload DLL | ✅ Yes |

### Customizing Hotkeys

**Method 1: Edit config.json**

```json
"hotkeys": {
  "toggle_menu": 45,      // INSERT (VK_INSERT)
  "teleport_save": 116,   // F5 (VK_F5)
  "teleport_load": 117,   // F6 (VK_F6)
  "unload": 35            // END (VK_END)
}
```

**Virtual Key Codes:**
- INSERT: 45 (VK_INSERT)
- DELETE: 46 (VK_DELETE)
- HOME: 36 (VK_HOME)
- END: 35 (VK_END)
- F1-F12: 112-123 (VK_F1 to VK_F12)
- Full list: [Microsoft Docs](https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes)

**Method 2: Settings Tab (Future)**

UI for hotkey customization will be added in future versions.

---

## Tips & Tricks

### General Tips

1. **Start Small**: Enable one feature at a time to understand what each does
2. **Save Config**: Use "Save Config" before testing risky features
3. **Check Logs**: If something doesn't work, check the log file
4. **Backup Saves**: Always backup game saves before using cheats

### Feature Combinations

**Ultimate Power Setup:**
- God Mode + Infinite Stamina + One-Hit Kill = Unstoppable

**Fast Exploration:**
- Flight Mode + Speed 5x + No-Clip = Quickly explore anywhere

**Screenshot Mode:**
- Free Camera + Hide HUD + Custom FOV = Perfect cinematic shots

**Resource Farming:**
- Speed 10x + One-Hit Kill = Fast enemy farming

### Performance Optimization

If experiencing lag:

1. Disable ESP/Wallhack
2. Close menu when not in use
3. Reduce damage/speed multipliers
4. Don't use multiple intensive features together

### Safety Tips

1. **Save Often**: Game saves with modified stats might behave unexpectedly
2. **Test in Safe Area**: Try new features in a safe location first
3. **Disable for Important Events**: Turn off cheats for story cutscenes
4. **Use Responsibly**: This is for learning and personal use only

---

## FAQ

### General Questions

**Q: Is this safe to use?**  
A: The client includes safety checks for memory operations. However, as with any memory manipulation tool, use at your own risk. Always backup your save files.

**Q: Will I get banned?**  
A: This game is single-player, so bans don't apply. However, respect the game's terms of service.

**Q: Does this work with all game versions?**  
A: Memory patterns are version-specific and need updates when the game updates.

### Technical Questions

**Q: Can I use this with other mods?**  
A: Generally yes, but conflicts may occur depending on what the other mods modify.

**Q: Why doesn't feature X work?**  
A: Check logs. Feature might not be implemented yet or patterns need updating for your game version.

**Q: Can I run multiple instances?**  
A: No, the DLL is designed for single-instance use per game process.

### Usage Questions

**Q: How do I find item IDs?**  
A: Use memory scanner, reverse engineering tools, or check game files/wikis.

**Q: My teleport position keeps resetting**  
A: Save positions to config file by clicking "Save Config" after setting them.

**Q: Speed multiplier makes me stuck**  
A: Try values between 1.5x-3x for stable gameplay. Very high values cause physics issues.

---

## Troubleshooting

### DLL Won't Inject

**Symptoms**: Injector shows error or "Injection failed"

**Solutions:**
1. Run injector as Administrator
2. Make sure game is running
3. Verify DLL is for correct architecture (x64)
4. Check antivirus isn't blocking
5. Try different injection method

### Menu Doesn't Appear

**Symptoms**: Press INSERT but no menu shows

**Solutions:**
1. Check if DLL actually injected (look for log file)
2. Try pressing INSERT multiple times
3. Verify hotkey in config.json
4. Check game window is in focus
5. Look for errors in log file

### Features Not Working

**Symptoms**: Feature enabled but no effect

**Solutions:**
1. Check feature is actually toggled on
2. Verify game state (not in cutscene/menu)
3. Check logs for pattern scanning errors
4. Game might need pattern updates
5. Try reinjecting DLL

### Game Crashes

**Symptoms**: Game closes unexpectedly

**Solutions:**
1. Disable all features and enable one at a time
2. Check for game updates
3. Verify DLL matches game version
4. Look for crash info in log file
5. Try clean injection (restart game)

### Performance Issues

**Symptoms**: Game lags or FPS drops

**Solutions:**
1. Close menu when not needed
2. Disable ESP if enabled
3. Reduce multiplier values
4. Check system resources
5. Disable other overlays (Discord, etc.)

### Can't Unload DLL

**Symptoms**: END key doesn't unload

**Solutions:**
1. Press and hold END for 2-3 seconds
2. Check hotkey hasn't been changed in config
3. Use injector to unload (if supported)
4. Restart game as last resort

---

## Finding Item IDs

Item IDs are game-specific and must be discovered through reverse engineering.

### Method 1: Memory Scanner

1. Open Advanced tab → Memory Scanner
2. Search for known item quantity
3. Change item quantity in game
4. Refine search
5. Find item structure
6. Locate ID field nearby

### Method 2: Cheat Engine

1. Open game in Cheat Engine
2. Search for item quantity (exact value)
3. Use/drop item to change quantity
4. Rescan for new value
5. Repeat until you find the address
6. Examine nearby memory for ID

### Method 3: Game Files

Some games store item definitions in readable formats:
- JSON files
- XML files
- Database files (.db, .sqlite)

Check game installation folder for data files.

---

## Getting Help

### Log Files

Always check logs first:
```
%USERPROFILE%\Documents\NFL-Custom-Client\log.txt
```

Logs contain:
- Initialization messages
- Feature activation/deactivation
- Errors and warnings
- Pattern scanning results

### Reporting Issues

When reporting issues, include:

1. Game version
2. NFL Custom Client version
3. Log file contents
4. Steps to reproduce
5. Expected vs actual behavior

### Community Support

- GitHub Issues: [Report bugs/request features](https://github.com/jhellolag-sketch/NFL-Custom-Client/issues)
- Check existing issues for solutions

---

## Best Practices

### Do's ✅

- Backup save files regularly
- Test features in safe areas first
- Save config after finding good settings
- Check logs when something doesn't work
- Start with low multiplier values
- Unload DLL gracefully (END key)

### Don'ts ❌

- Don't use extreme values immediately
- Don't use in multiplayer (if game has it)
- Don't ignore errors in logs
- Don't inject multiple times without restarting
- Don't forget to save your game
- Don't use on games you don't own

---

## Advanced Usage

### Custom Scripts (When Available)

Future versions will support Lua scripting:

```lua
-- Example script
function onLoad()
    Player.SetHealth(9999)
    Player.SetSpeed(2.0)
    log("Custom script loaded!")
end
```

### Memory Scanning

Use built-in scanner or Cheat Engine:

1. Find value you want to modify
2. Note the address
3. Create custom feature using address
4. Test thoroughly

### Pattern Updating

If patterns stop working after game update:

1. Use x64dbg or similar debugger
2. Find new function addresses
3. Create new byte patterns
4. Update `src/core/patterns.h`
5. Rebuild DLL

---

## Keyboard Shortcuts (In Menu)

| Key | Action |
|-----|--------|
| `Tab` | Next UI element |
| `Shift+Tab` | Previous UI element |
| `Space` | Toggle checkbox/button |
| `Arrow Keys` | Navigate dropdowns |
| `Enter` | Confirm input |

---

*Last Updated: 2026-02-16*  
*Version: 1.0*
