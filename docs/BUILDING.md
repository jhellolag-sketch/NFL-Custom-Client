# Building Guide

Complete guide to building NFL Custom Client from source.

## Table of Contents

1. [Prerequisites](#prerequisites)
2. [Setting Up vcpkg](#setting-up-vcpkg)
3. [Cloning the Repository](#cloning-the-repository)
4. [Building with Visual Studio](#building-with-visual-studio)
5. [Building with MSBuild (Command Line)](#building-with-msbuild-command-line)
6. [Common Build Issues](#common-build-issues)
7. [Build Configuration](#build-configuration)

---

## Prerequisites

### Required Software

- **Windows 10/11** (64-bit)
- **Visual Studio 2022** (or later)
  - Workload: "Desktop development with C++"
  - Individual components:
    - MSVC v143 or later
    - Windows 10 SDK (10.0.19041.0 or later)
    - C++ CMake tools for Windows (optional)

- **vcpkg** - Package manager for C++ libraries
- **Git** - Version control

### Optional Software

- **Visual Studio Code** - Alternative editor
- **CMake** (if using CMake build system)

---

## Setting Up vcpkg

vcpkg is required to automatically install dependencies (ImGui, MinHook, nlohmann-json).

### 1. Install vcpkg

```powershell
# Clone vcpkg repository
git clone https://github.com/Microsoft/vcpkg.git C:\vcpkg

# Navigate to vcpkg directory
cd C:\vcpkg

# Bootstrap vcpkg
.\bootstrap-vcpkg.bat

# Integrate with Visual Studio (requires admin)
.\vcpkg integrate install
```

### 2. Verify Installation

```powershell
.\vcpkg version
```

You should see vcpkg version information.

### 3. Set Environment Variable (Optional)

Add vcpkg to your PATH for easier access:

```powershell
setx VCPKG_ROOT "C:\vcpkg"
setx PATH "%PATH%;C:\vcpkg"
```

---

## Cloning the Repository

### Using Git Command Line

```bash
# Clone the repository
git clone https://github.com/jhellolag-sketch/NFL-Custom-Client.git

# Navigate to project directory
cd NFL-Custom-Client
```

### Using Visual Studio

1. Open Visual Studio 2022
2. Click "Clone a repository"
3. Enter repository URL: `https://github.com/jhellolag-sketch/NFL-Custom-Client.git`
4. Choose local path
5. Click "Clone"

---

## Building with Visual Studio

### Method 1: Using Visual Studio IDE

1. **Open Solution**
   - Double-click `NFL-Custom-Client.sln`
   - Or open Visual Studio → File → Open → Project/Solution

2. **Configure Build**
   - Select **Release** configuration (dropdown at top)
   - Select **x64** platform (dropdown at top)

3. **Restore Dependencies**
   - vcpkg will automatically restore dependencies on first build
   - This may take 5-10 minutes for first build
   - Dependencies are cached for subsequent builds

4. **Build Solution**
   - Click Build → Build Solution (or press F7)
   - Or right-click solution in Solution Explorer → Build

5. **Locate Output**
   - Built DLL: `bin\Release\NFL-Custom-Client.dll`
   - Build logs: `obj\Release\`

### Method 2: Using Developer Command Prompt

1. **Open Developer Command Prompt**
   - Start Menu → Visual Studio 2022 → Developer Command Prompt for VS 2022

2. **Navigate to Project**
   ```powershell
   cd C:\path\to\NFL-Custom-Client
   ```

3. **Build**
   ```powershell
   msbuild NFL-Custom-Client.sln /p:Configuration=Release /p:Platform=x64
   ```

---

## Building with MSBuild (Command Line)

### Prerequisites

Ensure MSBuild is in your PATH or use Developer Command Prompt.

### Build Commands

```powershell
# Clean build
msbuild NFL-Custom-Client.sln /t:Clean /p:Configuration=Release /p:Platform=x64

# Build solution
msbuild NFL-Custom-Client.sln /t:Build /p:Configuration=Release /p:Platform=x64

# Rebuild (clean + build)
msbuild NFL-Custom-Client.sln /t:Rebuild /p:Configuration=Release /p:Platform=x64

# Verbose output
msbuild NFL-Custom-Client.sln /t:Build /p:Configuration=Release /p:Platform=x64 /v:detailed

# Parallel build (faster)
msbuild NFL-Custom-Client.sln /t:Build /p:Configuration=Release /p:Platform=x64 /m
```

### Build Output

Successful build output will be in:
- **DLL**: `bin\Release\NFL-Custom-Client.dll`
- **Intermediate files**: `obj\Release\`

---

## Common Build Issues

### Issue 1: vcpkg Integration Not Found

**Error:**
```
Could not find vcpkg integration
```

**Solution:**
```powershell
cd C:\vcpkg
.\vcpkg integrate install
```

### Issue 2: Missing Dependencies

**Error:**
```
Cannot open include file: 'imgui.h'
Cannot open include file: 'MinHook.h'
Cannot open include file: 'nlohmann/json.hpp'
```

**Solution:**

vcpkg should auto-install dependencies. If not, manually install:

```powershell
cd C:\vcpkg
.\vcpkg install imgui[dx11-binding,win32-binding]:x64-windows
.\vcpkg install minhook:x64-windows
.\vcpkg install nlohmann-json:x64-windows
```

### Issue 3: Platform Toolset Not Found

**Error:**
```
The build tools for v143 cannot be found
```

**Solution:**

1. Open Visual Studio Installer
2. Modify Visual Studio 2022
3. Install "MSVC v143 - VS 2022 C++ x64/x86 build tools"

### Issue 4: Windows SDK Not Found

**Error:**
```
Windows SDK version 10.0 not found
```

**Solution:**

1. Open Visual Studio Installer
2. Modify Visual Studio 2022
3. Install "Windows 10 SDK (10.0.19041.0)" or later

### Issue 5: LNK2001 Unresolved External Symbol

**Error:**
```
LNK2001: unresolved external symbol
```

**Solution:**

1. Ensure all required .lib files are linked in project settings
2. Check that vcpkg dependencies are installed correctly
3. Verify Platform (x64) matches your dependencies

Required libraries in project:
- d3d11.lib
- dxgi.lib
- d3dcompiler.lib
- user32.lib
- kernel32.lib
- shlwapi.lib
- shell32.lib
- Psapi.lib

### Issue 6: C2039 or C2065 Compiler Errors

**Error:**
```
C2039: identifier is not a member of
C2065: undeclared identifier
```

**Solution:**

1. Check include paths in project properties
2. Verify C++ Language Standard is set to C++17
3. Ensure all header files are included in proper order

### Issue 7: Access Denied During Build

**Error:**
```
Cannot write to output file
Access is denied
```

**Solution:**

1. Close any programs that might be using the DLL
2. Disable antivirus temporarily
3. Run Visual Studio as Administrator
4. Check file/folder permissions

---

## Build Configuration

### Project Properties

To view/modify build settings:

1. Right-click project in Solution Explorer
2. Select "Properties"

### Important Settings

**General**
- Configuration Type: Dynamic Library (.dll)
- Platform Toolset: Visual Studio 2022 (v143)
- C++ Language Standard: ISO C++17

**C/C++ → General**
- Additional Include Directories:
  - `$(ProjectDir)include`
  - `$(ProjectDir)src`
  - `%(AdditionalIncludeDirectories)`

**C/C++ → Preprocessor**
- Preprocessor Definitions:
  - `WIN32`
  - `NDEBUG`
  - `_WINDOWS`
  - `_USRDLL`
  - `NFLCUSTOMCLIENT_EXPORTS`

**C/C++ → Code Generation**
- Runtime Library: Multi-threaded (/MT)
- Enable Function-Level Linking: Yes

**C/C++ → Optimization** (Release)
- Optimization: Maximize Speed (/O2)
- Inline Function Expansion: Any Suitable (/Ob2)
- Enable Intrinsic Functions: Yes

**Linker → General**
- Output File: `$(OutDir)NFL-Custom-Client.dll`
- Additional Library Directories: (auto-configured by vcpkg)

**Linker → Input**
- Additional Dependencies:
  - d3d11.lib
  - dxgi.lib
  - d3dcompiler.lib
  - user32.lib
  - kernel32.lib
  - shlwapi.lib
  - shell32.lib
  - Psapi.lib

**vcpkg**
- Use Vcpkg Manifest: Yes
- Vcpkg Configuration: Release
- Vcpkg Target Triplet: x64-windows

---

## Customizing the Build

### Changing Output Directory

Edit `NFL-Custom-Client.vcxproj`:

```xml
<PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|x64'">
  <OutDir>$(SolutionDir)custom\output\path\</OutDir>
  <IntDir>$(SolutionDir)custom\intermediate\path\</IntDir>
</PropertyGroup>
```

### Adding Debug Configuration

Currently, the project only has Release configuration. To add Debug:

1. Configuration Manager → New Solution Configuration
2. Name: Debug
3. Copy settings from: Release
4. Modify for debug:
   - Runtime Library: Multi-threaded Debug (/MTd)
   - Optimization: Disabled (/Od)
   - Generate Debug Information: Yes

### Adding Additional Source Files

Edit `NFL-Custom-Client.vcxproj`:

```xml
<ItemGroup>
  <ClCompile Include="src\your_new_file.cpp" />
</ItemGroup>

<ItemGroup>
  <ClInclude Include="src\your_new_file.h" />
</ItemGroup>
```

Or use Visual Studio:
1. Right-click project → Add → New Item
2. Select C++ File (.cpp) or Header File (.h)

---

## Verifying the Build

### 1. Check File Size

The built DLL should be approximately:
- Release: 500KB - 2MB (depending on dependencies)

### 2. Check Dependencies

Use [Dependencies Walker](https://www.dependencywalker.com/) or `dumpbin`:

```powershell
dumpbin /dependents bin\Release\NFL-Custom-Client.dll
```

Expected dependencies:
- KERNEL32.dll
- USER32.dll
- d3d11.dll
- dxgi.dll

### 3. Test Injection

Before testing on the game:

1. Use a test application
2. Inject the DLL
3. Check for crashes or errors
4. Verify logs in `%USERPROFILE%\Documents\NFL-Custom-Client\log.txt`

---

## Build Performance Tips

### 1. Parallel Build

Enable parallel compilation:
- Project Properties → C/C++ → General
- Multi-processor Compilation: Yes (/MP)

### 2. Incremental Linking

For faster Debug builds:
- Project Properties → Linker → General
- Enable Incremental Linking: Yes (/INCREMENTAL)

### 3. Precompiled Headers

To speed up compilation, add precompiled headers:

1. Create `pch.h` and `pch.cpp`
2. Enable in project properties:
   - C/C++ → Precompiled Headers
   - Precompiled Header: Use (/Yu)
   - Precompiled Header File: pch.h

### 4. Caching

vcpkg caches compiled libraries. First build is slow, subsequent builds are fast.

---

## Continuous Integration (CI)

### GitHub Actions Example

Create `.github/workflows/build.yml`:

```yaml
name: Build

on: [push, pull_request]

jobs:
  build:
    runs-on: windows-latest
    
    steps:
    - uses: actions/checkout@v2
    
    - name: Setup vcpkg
      run: |
        git clone https://github.com/Microsoft/vcpkg.git
        .\vcpkg\bootstrap-vcpkg.bat
        .\vcpkg\vcpkg integrate install
    
    - name: Setup MSBuild
      uses: microsoft/setup-msbuild@v1
    
    - name: Build
      run: msbuild NFL-Custom-Client.sln /p:Configuration=Release /p:Platform=x64
    
    - name: Upload Artifact
      uses: actions/upload-artifact@v2
      with:
        name: NFL-Custom-Client
        path: bin/Release/NFL-Custom-Client.dll
```

---

## Additional Resources

- [Visual Studio Documentation](https://docs.microsoft.com/en-us/visualstudio/)
- [vcpkg Documentation](https://vcpkg.io/en/docs/README.html)
- [MSBuild Reference](https://docs.microsoft.com/en-us/visualstudio/msbuild/)
- [C++17 Standard](https://en.cppreference.com/w/cpp/17)

---

*Last Updated: 2026-02-16*  
*Version: 1.0*
