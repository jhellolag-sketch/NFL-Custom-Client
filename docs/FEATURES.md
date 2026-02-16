# Features Documentation

Comprehensive guide to all features in NFL Custom Client for FANTASY LIFE i.

## Table of Contents

1. [Player Features](#player-features)
2. [Combat Features](#combat-features)
3. [Movement Features](#movement-features)
4. [Item Features](#item-features)
5. [World Features](#world-features)
6. [Visual Features](#visual-features)
7. [Advanced Features](#advanced-features)
8. [Known Limitations](#known-limitations)

---

## Player Features

### God Mode
**Status**: ✅ Implemented  
**Hotkey**: None (Toggle in menu)

Prevents your character from taking damage. When enabled:
- Health will not decrease from enemy attacks
- Environmental damage is blocked
- Fall damage is negated

**Usage:**
1. Open menu (INSERT)
2. Navigate to "Player" tab
3. Check "God Mode"

**Note:** Some scripted damage events may bypass this protection.

### Infinite Stamina
**Status**: ✅ Implemented  
**Hotkey**: None (Toggle in menu)

Keeps your stamina at maximum at all times. When enabled:
- Running never depletes stamina
- Combat actions don't consume stamina
- Swimming/climbing uses no stamina

**Usage:**
1. Open menu (INSERT)
2. Navigate to "Player" tab
3. Check "Infinite Stamina"

### Infinite Mana/MP
**Status**: ✅ Implemented  
**Hotkey**: None (Toggle in menu)

Maintains your mana/magic points at maximum. When enabled:
- Spell casting doesn't consume MP
- Special abilities are always available
- No need to rest or use mana potions

**Usage:**
1. Open menu (INSERT)
2. Navigate to "Player" tab
3. Check "Infinite Mana/MP"

### Character Stats Editor
**Status**: ✅ Implemented  
**Hotkey**: None

Directly modify your character's stats including HP, Stamina, and Mana values.

**Usage:**
1. Open menu (INSERT)
2. Navigate to "Player" tab
3. Use sliders to adjust Health, Stamina, and Mana
4. Click "Max All Stats" for instant 9999 in all stats

**Available Stats:**
- Health (0-9999)
- Stamina (0-9999)
- Mana (0-9999)

### Level Editor
**Status**: ✅ Implemented  
**Hotkey**: None

Change your character level instantly.

**Usage:**
1. Open menu (INSERT)
2. Navigate to "Player" tab
3. Enter desired level in the "Level" input field
4. Level changes apply immediately

**Note:** This changes the level value but may not grant level-up rewards retroactively.

---

## Combat Features

### One-Hit Kill
**Status**: ✅ Implemented  
**Hotkey**: None (Toggle in menu)

Defeats any enemy in a single hit regardless of their health.

**Usage:**
1. Open menu (INSERT)
2. Navigate to "Combat" tab
3. Check "One-Hit Kill"

**Note:** May not work on bosses with scripted health phases.

### Damage Multiplier
**Status**: ✅ Implemented  
**Hotkey**: None

Multiply your damage output by any value from 0.1x to 100x.

**Usage:**
1. Open menu (INSERT)
2. Navigate to "Combat" tab
3. Adjust "Damage Multiplier" slider
4. Click "Reset to 1x" to return to normal damage

**Recommended Values:**
- 2x-5x: Slight advantage
- 10x: Easy mode
- 50x-100x: Instant kill on most enemies

---

## Movement Features

### Speed Multiplier
**Status**: ✅ Implemented  
**Hotkey**: None

Adjust your movement speed from 0.1x (very slow) to 10x (extremely fast).

**Usage:**
1. Open menu (INSERT)
2. Navigate to "Movement" tab
3. Adjust "Speed Multiplier" slider

**Recommended Values:**
- 1.5x-2x: Comfortable speed increase
- 3x-5x: Fast travel
- 10x: Maximum speed (may cause clipping)

### Jump Height Modifier
**Status**: ✅ Implemented  
**Hotkey**: None

Increase jump height from 1x (normal) to 20x (super jump).

**Usage:**
1. Open menu (INSERT)
2. Navigate to "Movement" tab
3. Adjust "Jump Height" slider

**Note:** Very high values (15x+) may cause fall damage when landing unless God Mode is enabled.

### Flight Mode
**Status**: ✅ Implemented  
**Hotkey**: None (Toggle in menu)

Disables gravity, allowing free flight.

**Controls when Flight is enabled:**
- WASD: Horizontal movement
- Space: Ascend
- Ctrl: Descend

**Usage:**
1. Open menu (INSERT)
2. Navigate to "Movement" tab
3. Check "Flight Mode"

### No-Clip Mode
**Status**: ✅ Implemented  
**Hotkey**: None (Toggle in menu)

Disables collision detection, allowing you to walk through walls and objects.

**Usage:**
1. Open menu (INSERT)
2. Navigate to "Movement" tab
3. Check "No-Clip Mode"

**Warning:** Be careful not to fall through the world. Use with Flight Mode for safety.

### Teleportation System
**Status**: ✅ Implemented  
**Hotkeys**: F5 (Save), F6 (Load)

Save and load your position for quick travel.

**Usage:**

**Method 1: Quick Save/Load**
1. Press F5 to save current position
2. Move anywhere
3. Press F6 to return to saved position

**Method 2: Manual Coordinates**
1. Open menu (INSERT)
2. Navigate to "Movement" tab
3. Enter X, Y, Z coordinates
4. Click "Teleport to Coordinates"

**Method 3: Position Management**
1. Click "Save Position" button to save current location
2. Coordinates are displayed in real-time
3. Click "Load Position" to teleport back

---

## Item Features

### Item Spawner
**Status**: ✅ Implemented  
**Hotkey**: None

Spawn items by their ID.

**Usage:**
1. Open menu (INSERT)
2. Navigate to "Items" tab
3. Enter Item ID
4. Set Quantity
5. Click "Spawn Item"

**Note:** Item IDs must be obtained through reverse engineering or game files.

### Currency Editor
**Status**: ✅ Implemented  
**Hotkey**: None

Modify your in-game currency (money/gold).

**Usage:**
1. Open menu (INSERT)
2. Navigate to "Items" tab
3. Enter desired currency amount
4. Click "Set Currency"

**Note:** Changes apply immediately but may require opening the inventory to see updated value.

### Inventory Tools
**Status**: ✅ Implemented  
**Hotkey**: None

Remove inventory restrictions.

**Available Tools:**
- **Remove Weight Limit**: Carry unlimited items regardless of weight
- **Unlock All Slots**: Access all inventory slots

**Usage:**
1. Open menu (INSERT)
2. Navigate to "Items" tab
3. Click desired button under "Inventory Tools"

---

## World Features

### Time Control
**Status**: ✅ Implemented  
**Hotkey**: None

Manipulate the flow of time in the game world.

**Features:**
- Freeze time completely
- Speed up time (2x, 5x, 10x)
- Slow down time (0.5x, 0.25x)

**Usage:**
1. Open menu (INSERT)
2. Navigate to "World" tab
3. Check "Freeze Time" to stop time
4. Or adjust "Time Speed" slider
5. Or click preset buttons for quick adjustments

**Use Cases:**
- Freeze time during difficult sections
- Speed up time for timed events
- Slow down time for precise actions

### Weather Control
**Status**: ✅ Implemented  
**Hotkey**: None

Change weather conditions instantly.

**Available Weather Types:**
- Clear
- Cloudy
- Rain
- Storm
- Snow
- Fog

**Usage:**
1. Open menu (INSERT)
2. Navigate to "World" tab
3. Select weather type from dropdown
4. Click "Apply Weather"

---

## Visual Features

### ESP/Wallhack
**Status**: ✅ Implemented  
**Hotkey**: None (Toggle in menu)

See enemies through walls with boxes and health bars.

**Features:**
- Draw boxes around enemies
- Show enemy health bars
- Display distance to enemies
- Customizable ESP color

**Usage:**
1. Open menu (INSERT)
2. Navigate to "Visual" tab
3. Check "ESP/Wallhack"

**Performance Note:** May reduce FPS in areas with many enemies.

### FOV Changer
**Status**: ✅ Implemented  
**Hotkey**: None

Adjust your field of view from 60° to 120°.

**Usage:**
1. Open menu (INSERT)
2. Navigate to "Visual" tab
3. Adjust "Field of View" slider
4. Click "Reset FOV" to return to default (90°)

**Recommended Values:**
- 60-80: Narrow FOV (more cinematic)
- 90: Default
- 100-120: Wide FOV (better peripheral vision)

### Free Camera
**Status**: ✅ Implemented  
**Hotkey**: None (Toggle in menu)

Detach camera from player for cinematic shots or exploration.

**Controls when Free Camera is enabled:**
- WASD: Move camera
- Mouse: Look around
- Speed can be adjusted

**Usage:**
1. Open menu (INSERT)
2. Navigate to "Visual" tab
3. Check "Free Camera"

### Custom HUD
**Status**: ✅ Implemented  
**Hotkey**: None

Toggle game HUD elements and add custom overlays.

**Features:**
- Show/hide game HUD
- Display coordinates
- Show movement speed
- FPS counter (always visible)

**Usage:**
1. Open menu (INSERT)
2. Navigate to "Visual" tab
3. Check/uncheck "Show HUD"

---

## Advanced Features

### Debug Console
**Status**: 🚧 Planned  
**Hotkey**: ~ (tilde)

Access Unreal Engine debug console to execute commands.

**Features:**
- Execute console commands
- Command history
- Auto-complete suggestions

**Usage:**
1. Open menu (INSERT)
2. Navigate to "Advanced" tab
3. Click "Open Console"
4. Or press ~ key in-game

### Script Executor
**Status**: 🚧 Planned  
**Hotkey**: None

Execute custom Lua scripts for advanced automation.

**Features:**
- Script editor
- Load/save scripts
- Script library with presets
- Error handling and output console

**Usage:**
1. Open menu (INSERT)
2. Navigate to "Advanced" tab
3. Click "Open Script Executor"

### Memory Scanner
**Status**: 🚧 Planned  
**Hotkey**: None

Search for and modify memory values, similar to Cheat Engine.

**Features:**
- Search for values (exact, range, unknown)
- Filter and refine results
- Modify found values
- Freeze values
- Save addresses for later use

**Usage:**
1. Open menu (INSERT)
2. Navigate to "Advanced" tab
3. Click "Open Memory Scanner"

---

## Known Limitations

### General
- Features require game-specific memory patterns that need updates when the game updates
- Some features may not work during cutscenes or scripted events
- Performance impact may occur with multiple features enabled simultaneously

### Player Features
- God Mode may not protect against instant-kill mechanics
- Stats changes may reset on death or area transitions
- Level changes don't grant retroactive rewards

### Combat Features
- One-Hit Kill may not work on bosses with scripted health phases
- Damage multiplier affects all damage sources (careful with environmental hazards)

### Movement Features
- Extreme speed values (10x+) may cause physics glitches
- No-Clip can cause you to fall through the world
- Teleportation coordinates depend on current map/area

### Item Features
- Invalid Item IDs may crash the game
- Some items may have level or prerequisite requirements
- Currency changes may not reflect immediately in all UI elements

### Visual Features
- ESP may cause performance drops with many enemies
- Extreme FOV values (under 60 or over 120) may cause visual artifacts
- Free Camera may cause camera to get stuck in geometry

### Advanced Features
- Console commands depend on Unreal Engine version
- Scripts require knowledge of Lua and game internals
- Memory Scanner results depend on game state

## Troubleshooting

### Feature Not Working
1. Check that the feature is enabled in the menu
2. Verify game is running (not paused/in menu)
3. Check logs at `%USERPROFILE%\Documents\NFL-Custom-Client\log.txt`
4. Patterns may need updating for your game version

### Game Crashes
1. Disable all features and re-enable one at a time
2. Check if game was recently updated
3. Verify DLL was compiled for correct game version
4. Check logs for error messages

### Performance Issues
1. Disable ESP if enabled
2. Reduce damage/speed multipliers
3. Disable multiple features at once
4. Close menu when not in use

---

*Last Updated: 2026-02-16*  
*Version: 1.0*
