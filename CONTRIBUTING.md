# Contributing to NFL Custom Client

Thank you for your interest in contributing! This document provides guidelines for contributing to the NFL Custom Client project.

## Table of Contents

1. [Code of Conduct](#code-of-conduct)
2. [Getting Started](#getting-started)
3. [Development Setup](#development-setup)
4. [How to Contribute](#how-to-contribute)
5. [Coding Standards](#coding-standards)
6. [Pull Request Process](#pull-request-process)
7. [Feature Requests](#feature-requests)
8. [Bug Reports](#bug-reports)

## Code of Conduct

### Our Standards

- Be respectful and inclusive
- Use welcoming and constructive language
- Accept constructive criticism gracefully
- Focus on what's best for the project
- Show empathy towards other contributors

### Unacceptable Behavior

- Harassment or discriminatory language
- Trolling or insulting comments
- Publishing others' private information
- Any unethical or unprofessional conduct

## Getting Started

### Prerequisites

Before contributing, ensure you have:

- Visual Studio 2022 installed
- vcpkg package manager set up
- Git configured on your system
- Basic understanding of C++17
- Familiarity with game hacking concepts (optional but helpful)

### Fork and Clone

1. Fork the repository on GitHub
2. Clone your fork locally:
   ```bash
   git clone https://github.com/YOUR_USERNAME/NFL-Custom-Client.git
   cd NFL-Custom-Client
   ```
3. Add upstream remote:
   ```bash
   git remote add upstream https://github.com/jhellolag-sketch/NFL-Custom-Client.git
   ```

## Development Setup

### Build the Project

```powershell
# Open in Visual Studio
start NFL-Custom-Client.sln

# Or build with MSBuild
msbuild NFL-Custom-Client.sln /p:Configuration=Release /p:Platform=x64
```

### Run Tests

Currently, there are no automated tests. Manual testing is required:
1. Build the DLL
2. Inject into a test application or game
3. Verify features work as expected
4. Check logs for errors

## How to Contribute

### Types of Contributions

We welcome:

1. **Bug Fixes** - Fix issues listed in GitHub Issues
2. **New Features** - Add new enhancement features
3. **Documentation** - Improve or add documentation
4. **Code Quality** - Refactoring, optimization, cleanup
5. **Patterns** - Update memory patterns for game versions

### Contribution Workflow

1. **Check Existing Issues**
   - Look for existing issues or discussions
   - Comment on the issue if you plan to work on it

2. **Create a Branch**
   ```bash
   git checkout -b feature/your-feature-name
   # or
   git checkout -b fix/issue-number-description
   ```

3. **Make Changes**
   - Follow coding standards (see below)
   - Add comments explaining complex logic
   - Update documentation if needed

4. **Test Your Changes**
   - Build successfully
   - Test functionality manually
   - Check for memory leaks
   - Verify logs show no errors

5. **Commit Changes**
   ```bash
   git add .
   git commit -m "Clear, descriptive commit message"
   ```

6. **Push to Your Fork**
   ```bash
   git push origin feature/your-feature-name
   ```

7. **Create Pull Request**
   - Open PR on GitHub
   - Fill out PR template
   - Link related issues
   - Wait for review

## Coding Standards

### C++ Style Guidelines

#### Naming Conventions

```cpp
// Classes: PascalCase
class FeatureManager { };

// Functions: PascalCase
void InitializeFeatures() { }

// Variables: camelCase
int playerHealth = 100;

// Constants: UPPER_SNAKE_CASE
const int MAX_HEALTH = 9999;

// Namespaces: PascalCase
namespace Features { }

// Files: lowercase with underscores or descriptive names
// godmode.h, feature_manager.h
```

#### Code Organization

```cpp
// Header file structure
#pragma once

#include <system_headers>
#include "project_headers.h"

namespace YourNamespace {

class YourClass {
private:
    // Private members
    
public:
    // Public interface
    static YourClass& GetInstance();
    
    void Initialize();
    void Update();
    void Shutdown();
};

// Convenience functions (optional)
inline void InitializeYourClass() {
    YourClass::GetInstance().Initialize();
}

} // namespace YourNamespace
```

#### Best Practices

1. **Use Modern C++17 Features**
   ```cpp
   // Use auto for complex types
   auto& config = Config::GetConfig();
   
   // Use range-based for loops
   for (const auto& item : items) { }
   
   // Use nullptr instead of NULL
   void* ptr = nullptr;
   ```

2. **RAII for Resource Management**
   ```cpp
   // Good: Automatic cleanup
   {
       std::lock_guard<std::mutex> lock(mutex);
       // Critical section
   } // lock automatically released
   ```

3. **Const Correctness**
   ```cpp
   // Mark const methods
   bool IsActive() const { return active; }
   
   // Use const references for parameters
   void SetName(const std::string& name);
   ```

4. **Error Handling**
   ```cpp
   // Check return values
   if (!Initialize()) {
       Logger::Log("Initialization failed", Logger::ERROR);
       return false;
   }
   
   // Use try-catch for exceptions
   try {
       // Risky operation
   } catch (const std::exception& e) {
       Logger::Log("Exception: " + std::string(e.what()), Logger::ERROR);
   }
   ```

5. **Logging**
   ```cpp
   // Log important events
   Logger::Log("[YourFeature] Initialized successfully");
   Logger::Log("[YourFeature] Error occurred", Logger::ERROR);
   ```

### Documentation

#### Code Comments

```cpp
// Brief function description
// @param x: Description of parameter
// @return: Description of return value
float CalculateDamage(float x) {
    // Implementation
}

// Complex logic should have explanatory comments
// Resolve RIP-relative address (x64 instruction encoding)
int32_t offset = Memory::Read<int32_t>(address + 3);
uintptr_t resolved = address + 7 + offset;
```

#### File Headers

```cpp
/*
 * Feature Name
 * Description of what this file does
 * 
 * Author: Your Name (optional)
 * Date: YYYY-MM-DD (optional)
 */
```

## Pull Request Process

### PR Title Format

Use clear, descriptive titles:
- `Add: New god mode feature`
- `Fix: Memory leak in speed modifier`
- `Update: Documentation for teleporter`
- `Refactor: Cleanup hooks implementation`

### PR Description Template

```markdown
## Description
Brief description of changes

## Type of Change
- [ ] Bug fix
- [ ] New feature
- [ ] Documentation update
- [ ] Code refactoring

## Testing
- How you tested the changes
- Test results

## Checklist
- [ ] Code builds without errors
- [ ] Code follows project style guidelines
- [ ] Comments added for complex logic
- [ ] Documentation updated if needed
- [ ] No memory leaks introduced
- [ ] Logs show no errors

## Related Issues
Fixes #123
```

### Review Process

1. Maintainer reviews code
2. Feedback provided via comments
3. Make requested changes
4. Re-request review
5. Once approved, PR is merged

### Merge Criteria

PRs will be merged if:
- Code builds successfully
- Follows coding standards
- Includes adequate documentation
- Passes manual testing
- No conflicts with main branch

## Feature Requests

### Suggesting New Features

Open an issue with:
- **Title**: Clear feature name
- **Description**: What the feature does
- **Use Case**: Why it's useful
- **Implementation Ideas**: (Optional) How it could work

### Feature Priority

Features are prioritized based on:
- Usefulness to users
- Implementation complexity
- Alignment with project goals
- Community interest

## Bug Reports

### Reporting Bugs

Include:

1. **Description**: What went wrong
2. **Steps to Reproduce**:
   ```
   1. Start game
   2. Enable feature X
   3. Observe crash
   ```
3. **Expected Behavior**: What should happen
4. **Actual Behavior**: What actually happened
5. **Environment**:
   - Game version
   - DLL version
   - Windows version
6. **Logs**: Attach log file
7. **Additional Context**: Screenshots, etc.

### Bug Report Template

```markdown
**Describe the bug**
A clear description of the bug.

**To Reproduce**
Steps to reproduce the behavior.

**Expected behavior**
What you expected to happen.

**Screenshots/Logs**
If applicable, add screenshots or log excerpts.

**Environment:**
- Game Version: [e.g., 1.0.3]
- DLL Version: [e.g., 1.0]
- Windows Version: [e.g., Windows 11]

**Additional context**
Any other relevant information.
```

## Development Guidelines

### Memory Safety

Always use safe memory operations:
```cpp
// Check for null before dereferencing
if (address != 0) {
    value = Memory::Read<int>(address);
}

// Use IsBadReadPtr/IsBadWritePtr checks (Windows-specific)
if (!IsBadReadPtr((void*)address, sizeof(int))) {
    // Safe to read
}
```

### Thread Safety

Use mutexes for shared resources:
```cpp
std::lock_guard<std::mutex> lock(mutex);
// Access shared resource
```

### Performance

- Avoid polling in tight loops
- Cache frequently accessed values
- Use appropriate data structures
- Profile before optimizing

## Questions?

- Open a [Discussion](https://github.com/jhellolag-sketch/NFL-Custom-Client/discussions)
- Comment on an existing Issue
- Check existing documentation

---

Thank you for contributing to NFL Custom Client! 🎉

*Last Updated: 2026-02-16*
