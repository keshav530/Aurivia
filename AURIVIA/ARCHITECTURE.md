# AURIVIA Engine Architecture

## System Design Overview

```
┌─────────────────────────────────────────────────────────────┐
│                   APPLICATION LAYER                         │
│  (User Game, Editor, Tools)                                │
└─────────────────────────────────────────────────────────────┘
                           ↓
┌─────────────────────────────────────────────────────────────┐
│                 SCRIPTING SYSTEM (C#)                       │
│  P/Invoke ↔ Native C++ Bindings                            │
└─────────────────────────────────────────────────────────────┘
                           ↓
┌───────────────┬──────────────┬────────────┬────────────────┐
│  RENDERER     │   PHYSICS    │   AUDIO    │    EVENTS      │
│  (3D + 2D)    │              │            │                │
└───────────────┴──────────────┴────────────┴────────────────┘
                           ↓
┌───────────────┬──────────────┬────────────────────────────┐
│   WINDOW      │   INPUT      │   SCENE MANAGER            │
│  (GLFW)       │  (Keyboard,  │   (Game Objects,           │
│               │   Mouse,     │    Components)             │
│               │   Gamepad)   │                            │
└───────────────┴──────────────┴────────────────────────────┘
                           ↓
┌──────────────────────────────────────────────────────────┐
│              GRAPHICS API (OpenGL 4.3+)                  │
└──────────────────────────────────────────────────────────┘
                           ↓
┌──────────────────────────────────────────────────────────┐
│         HARDWARE (GPU, CPU, Audio Card)                  │
└──────────────────────────────────────────────────────────┘
```

## Component Breakdown

### 1. Engine Core (`engine/core/`)
- **engine.h/cpp**: Main engine class, lifecycle management
- **window.h/cpp**: Window creation and management (GLFW)
- **logger.h/cpp**: Logging system with levels

Responsibilities:
- Game loop execution (Update → Render cycle)
- Subsystem initialization and shutdown
- Frame timing and FPS tracking
- Application lifecycle management

### 2. Renderer (`engine/renderer/`)
- **renderer.h/cpp**: Main rendering system
- **shader.h/cpp**: Shader compilation and management

Features:
- 3D shape rendering (cube, sphere, plane)
- 2D quad and line drawing
- Material system (TODO)
- Lighting (basic Phong)
- Camera management

**Key Methods**:
```cpp
DrawCube(position, scale, color)
DrawSphere(position, radius, color)
DrawQuad(position, size, color)
SetViewMatrix(matrix)
SetProjectionMatrix(matrix)
```

### 3. Input System (`engine/input/`)
- **input_manager.h/cpp**: Input polling and state management

Supports:
- Keyboard (GLFW key codes)
- Mouse (position, buttons, scroll)
- Gamepad (future)

**Key Methods**:
```cpp
IsKeyPressed(KeyCode)
IsMouseButtonDown(MouseButton)
GetMousePosition()
GetMouseDelta()
```

### 4. Physics System (`engine/physics/`)
- **physics_system.h/cpp**: Physics simulation (placeholder)

Planned:
- Rigid body dynamics
- Collision detection
- Raycast queries
- Constraint solving

**Key Methods**:
```cpp
CreateRigidBody(position, scale, mass)
Update(deltaTime)
SetGravity(gravity)
```

### 5. Audio System (`engine/audio/`)
- **audio_system.h/cpp**: Audio playback (stub)

Planned:
- Sound effect playback
- Music streaming
- 3D spatial audio
- Volume management

**Key Methods**:
```cpp
LoadSound(filepath)
PlaySound(soundID, volume)
SetListenerPosition(position)
SetSoundPosition(soundID, position)
```

### 6. Editor (`editor/`)
- **main.cpp**: Editor entry point
- **ui/editor_window.h/cpp**: Editor UI panels

Features (placeholders):
- Scene hierarchy
- Inspector panel
- Play/Stop controls
- Asset browser

### 7. C# Bindings (`bindings/csharp/`)
- **Aurivia.NET.cs**: P/Invoke bindings for C#

Exports:
- Engine management
- MonoBehavior component system
- GameObject and Transform
- Input handling (C# API)
- Debug logging

## Data Flow

### Frame Execution

```
┌──────────────────────────────┐
│   Engine::Run()              │
└──────────────────────────────┘
        ↓
┌──────────────────────────────┐
│   Main Loop                  │
│   - Calculate deltaTime      │
│   - Call Update()            │
│   - Call Render()            │
│   - Swap buffers             │
└──────────────────────────────┘
        ↓
┌──────────────────────────────┐
│   Update Phase               │
│   - Poll input               │
│   - Update game logic (C#)   │
│   - Update physics           │
│   - Update audio listeners   │
└──────────────────────────────┘
        ↓
┌──────────────────────────────┐
│   Render Phase               │
│   - Clear buffers            │
│   - Set camera (view/proj)   │
│   - Draw all objects         │
│   - EndFrame (submit commands)│
└──────────────────────────────┘
        ↓
┌──────────────────────────────┐
│   SwapBuffers()              │
│   (Display to screen)        │
└──────────────────────────────┘
```

## Memory Model

### Stack Allocation (Frame-based)
- Temporary matrices, vectors
- Frame-local state

### Heap Allocation
- Engine subsystems (unique_ptr)
- Game objects and components
- Render buffers (VAO, VBO, textures)
- Physics bodies

### Object Lifetimes
```
Engine Created
    ↓
Subsystems Initialized
    ↓
Game Objects Created (C#)
    ↓
Main Loop (continuous)
    ↓
Game Objects Destroyed
    ↓
Subsystems Shutdown
    ↓
Engine Destroyed
```

## Threading Model

**Current**: Single-threaded
- All systems run on main thread
- Frame execution is synchronous

**Future**: Multi-threaded
- Render thread separate from update
- Physics on worker thread
- Audio on dedicated thread

## Extension Points

### Add a New Renderer Primitive

1. Add method to `Renderer` class:
```cpp
void DrawCapsule(glm::vec3 pos, float height, float radius, glm::vec3 color);
```

2. Create mesh in `CreateCapsuleMesh()`:
```cpp
void Renderer::CreateCapsuleMesh() {
    // Generate capsule geometry
    // Create VAO/VBO
    m_capsuleVAO = ...
}
```

3. Implement draw method:
```cpp
void Renderer::DrawCapsule(...) {
    m_basicShader->Use();
    // Set uniforms
    glBindVertexArray(m_capsuleVAO);
    glDrawElements(GL_TRIANGLES, m_capsuleIndexCount, GL_UNSIGNED_INT, nullptr);
}
```

### Add C# Component

1. Create class inheriting `MonoBehavior`:
```csharp
public class MyComponent : MonoBehavior {
    public void Start() { }
    public void Update() { }
}
```

2. Attach to GameObject:
```csharp
var player = new GameObject("Player");
var controller = player.AddComponent<PlayerController>();
```

## Performance Targets

| Metric | Target | Notes |
|--------|--------|-------|
| Frame Time | 16ms @ 60 FPS | Desktop |
| Mobile Frame Time | 33ms @ 30 FPS | Mobile target |
| Physics Bodies | < 1000 | Rigid bodies |
| Draw Calls | < 500/frame | Batching recommended |
| Memory | < 512MB | Runtime |
| GPU VRAM | < 2GB | Textures + buffers |

## Platform Support

### Windows
- Visual Studio 2022
- CMake 3.16+
- OpenGL 4.3+

### Linux (Planned)
- GCC/Clang
- Same OpenGL requirement

### Mobile (Planned)
- Android (OpenGL ES 3.2)
- iOS (Metal → OpenGL)

### Web (Future)
- Emscripten
- WebGL 2.0

---

**Last Updated**: April 14, 2026  
**Version**: 0.1.0 (MVP)
