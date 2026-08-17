# AURIVIA Project Structure

Complete file and directory tree for the game engine.

```
AURIVIA/
│
├── CMakeLists.txt                    [Build configuration]
├── build.ps1                         [PowerShell build script]
├── .gitignore                        [Git ignore rules]
│
├── README.md                         [Main documentation]
├── DEVELOPMENT.md                    [Development guide]
├── ARCHITECTURE.md                   [Technical architecture]
├── CONTRIBUTING.md                   [Contribution guidelines]
├── PROJECT_SUMMARY.md                [Quick reference]
├── LICENSE                           [MIT License]
│
├── engine/                           [Core engine - C++]
│   ├── core/
│   │   ├── include/
│   │   │   └── aurivia/
│   │   │       ├── engine.h          [Main engine class]
│   │   │       ├── window.h          [Window management]
│   │   │       └── logger.h          [Logging system]
│   │   └── src/
│   │       ├── engine.cpp            [Engine implementation]
│   │       ├── window.cpp            [GLFW window impl]
│   │       └── logger.cpp            [Logger impl]
│   │
│   ├── renderer/
│   │   ├── include/
│   │   │   └── aurivia/
│   │   │       ├── renderer.h        [3D/2D rendering]
│   │   │       └── shader.h          [Shader utilities]
│   │   └── src/
│   │       ├── renderer.cpp          [Renderer impl]
│   │       └── shader.cpp            [Shader impl]
│   │
│   ├── physics/
│   │   ├── include/
│   │   │   └── aurivia/
│   │   │       └── physics_system.h  [Physics interface]
│   │   └── src/                      [To be implemented]
│   │
│   ├── audio/
│   │   ├── include/
│   │   │   └── aurivia/
│   │   │       └── audio_system.h    [Audio interface]
│   │   └── src/
│   │       └── audio_system.cpp      [Stub implementation]
│   │
│   ├── input/
│   │   ├── include/
│   │   │   └── aurivia/
│   │   │       └── input_manager.h   [Input handling]
│   │   └── src/
│   │       └── input_manager.cpp     [Input impl]
│   │
│   └── scripting/                    [C# interop - to be populated]
│
├── editor/                           [Editor application - C#]
│   ├── main.cpp                      [Editor entry point]
│   ├── projects/                     [Project management - TODO]
│   └── ui/
│       ├── editor_window.h           [Editor UI interface]
│       └── editor_window.cpp         [Editor UI impl]
│
├── bindings/
│   └── csharp/
│       └── Aurivia.NET.cs            [Complete C# API bindings]
│
├── samples/                          [Example projects]
│   ├── cube_demo/
│   │   └── main.cpp                  [Rotating cube demo]
│   └── [Future samples]
│
├── assets/                           [Engine assets & resources]
│   ├── shaders/                      [GLSL shader files - TODO]
│   ├── textures/                     [Texture assets - TODO]
│   └── models/                       [Model assets - TODO]
│
└── build/                            [Build output (generated)]
    ├── bin/                          [Executables]
    │   ├── aurivia_editor.exe
    │   └── cube_demo.exe
    └── lib/                          [Libraries]
        └── aurivia_engine.lib
```

## File Statistics

### Header Files (8)
- `engine.h` - Main engine interface
- `window.h` - Window management
- `logger.h` - Logging utilities
- `renderer.h` - 3D/2D graphics
- `shader.h` - Shader utilities
- `input_manager.h` - Input handling
- `audio_system.h` - Audio interface
- `physics_system.h` - Physics interface

### Implementation Files (7)
- `engine.cpp` - ~200 lines
- `window.cpp` - ~100 lines
- `logger.cpp` - ~5 lines (mostly headers)
- `renderer.cpp` - ~400 lines
- `shader.cpp` - ~5 lines
- `input_manager.cpp` - ~50 lines
- `audio_system.cpp` - ~60 lines

### Documentation Files (5)
- README.md - Feature overview
- DEVELOPMENT.md - Development guide
- ARCHITECTURE.md - Technical details
- CONTRIBUTING.md - Contribution guide
- PROJECT_SUMMARY.md - Quick reference

### Configuration Files (3)
- CMakeLists.txt - Build system
- build.ps1 - Build script
- .gitignore - VCS ignore rules

### Application Files (3)
- editor/main.cpp - Editor launcher
- samples/cube_demo/main.cpp - Demo app
- bindings/csharp/Aurivia.NET.cs - C# API

## Build Targets

```
CMake Targets:
├── aurivia_engine      (Static Library)
│   └── Linked by: editor, cube_demo
├── aurivia_editor      (Executable)
│   └── Input: editor/main.cpp, editor/ui/*.cpp
└── cube_demo           (Executable)
    └── Input: samples/cube_demo/main.cpp
```

## Dependencies

### External
- **GLFW3** - Window creation
- **OpenGL 4.3+** - Graphics API
- **GLM** - Math library
- **.NET 6.0+** (optional) - C# support

### Internal
- All components are self-contained

## Code Organization

### Namespacing
```
namespace Aurivia {
    // Core engine classes
    class Engine { ... }
    class Window { ... }
    class Renderer { ... }
    
    // Enums and utilities
    enum class KeyCode { ... }
    enum class LogLevel { ... }
}
```

### Naming Conventions
- **Classes**: PascalCase (e.g., `InputManager`)
- **Functions**: camelCase (e.g., `IsKeyPressed`)
- **Variables**: camelCase (e.g., `deltaTime`)
- **Members**: m_ prefix (e.g., `m_isRunning`)
- **Constants**: UPPER_CASE (future)

## Module Responsibilities

### Core (`engine/core/`)
- Application lifecycle
- Window creation and event handling
- System logging
- Subsystem orchestration

### Renderer (`engine/renderer/`)
- Graphics rendering (3D and 2D)
- Shader management
- Camera control
- Lighting and materials

### Input (`engine/input/`)
- Keyboard input polling
- Mouse tracking
- Gamepad enumeration
- Input event buffering

### Physics (`engine/physics/`)
- Rigid body simulation
- Collision detection
- Physics queries (raycasting)
- Constraint solving

### Audio (`engine/audio/`)
- Sound effect playback
- Music streaming
- 3D spatial audio
- Volume management

### Scripting (`bindings/csharp/`)
- P/Invoke wrapper generation
- C# API exposure
- MonoBehavior simulation
- Event marshalling

## Extension Points

### Add New Renderer Primitive
1. Add method to `Renderer` class
2. Implement mesh generation
3. Add draw call in render loop

### Add Physics Feature
1. Extend `PhysicsSystem` class
2. Wrap Rapier3D/Bullet3 API
3. Expose via C# bindings

### Add Audio Feature
1. Extend `AudioSystem` class
2. Integrate OpenAL calls
3. Update input/output channels

## Build Flow

```
CMakeLists.txt
    ↓
cmake .. (Configure)
    ↓
Generate Visual Studio Solution
    ↓
cmake --build . (Compile)
    ↓
Link executable/library
    ↓
Output: bin/ and lib/ directories
```

## Git Structure

```
.git/
├── .gitignore
├── Tracked files
│   ├── CMakeLists.txt
│   ├── *.md files
│   ├── engine/
│   ├── editor/
│   ├── bindings/
│   └── samples/
└── Ignored files
    ├── build/
    ├── bin/
    ├── .vs/
    └── *.exe
```

---

**Total Statistics**:
- **Directories**: 25+
- **Header Files**: 8
- **Source Files**: 7
- **Documentation**: 5 files
- **Lines of Code**: ~2,500
- **Build Artifacts**: Excluded

---

Generated on April 14, 2026
