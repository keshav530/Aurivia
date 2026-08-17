# AURIVIA Game Engine - Development Guide

## Quick Start

### Windows Setup

1. **Prerequisites**
   ```powershell
   # Visual Studio 2022 with C++ development tools
   # CMake 3.16+
   # GLFW (will be fetched by CMake)
   ```

2. **Build the Engine**
   ```powershell
   mkdir build
   cd build
   cmake ..
   cmake --build . --config Release
   ```

3. **Run the Editor**
   ```powershell
   ./bin/aurivia_editor.exe
   ```

4. **Run Sample**
   ```powershell
   ./bin/cube_demo.exe
   ```

## Engine Architecture

### Core Subsystems

```
Engine (Main Loop)
├── Window System (GLFW)
│   └── OpenGL Context
├── Renderer (3D + 2D Graphics)
│   ├── Shader System
│   ├── Mesh Management
│   ├── Material System
│   └── Lighting
├── Physics Engine (Placeholder)
├── Audio System (Stub)
├── Input Manager
│   ├── Keyboard
│   ├── Mouse
│   └── Gamepad (Future)
└── Script System (C# Interop)
```

## Creating Your First Game

### C# Example

```csharp
using Aurivia;

public class PlayerController : MonoBehavior
{
    public float moveSpeed = 5f;
    public Rigidbody rigidbody;
    
    void Start()
    {
        rigidbody = GetComponent<Rigidbody>();
    }
    
    void Update()
    {
        float moveX = Input.GetAxis("Horizontal");
        float moveY = Input.GetAxis("Vertical");
        
        Vector3 movement = new Vector3(moveX, 0, moveY) * moveSpeed * Time.deltaTime;
        transform.position += movement;
        
        if (Input.GetKeyDown(KeyCode.Space))
        {
            Jump();
        }
    }
    
    void Jump()
    {
        rigidbody.AddForce(new Vector3(0, 10, 0), ForceMode.Impulse);
    }
    
    void OnCollisionEnter(Collider other)
    {
        Debug.Log("Collided with: " + other.gameObject.name);
    }
}
```

## File Structure Reference

```
AURIVIA/
├── engine/
│   ├── core/           # Engine core: lifecycle, window, logging
│   ├── renderer/       # Graphics rendering system
│   ├── physics/        # Physics simulation
│   ├── audio/          # Audio playback
│   ├── input/          # Input handling
│   └── scripting/      # C# bindings
├── editor/
│   ├── ui/            # Editor UI panels (ImGui)
│   └── projects/      # Project management
├── bindings/
│   └── csharp/        # C# language bindings (P/Invoke)
├── samples/
│   ├── cube_demo/     # Simple demo scene
│   └── (future demos)
└── docs/              # Documentation
```

## API Examples

### Engine Initialization

```cpp
Aurivia::Engine engine("My Game", 1920, 1080);

if (engine.Initialize())
{
    while (engine.IsRunning())
    {
        engine.Update(deltaTime);
        engine.Render();
    }
}
```

### Rendering

```cpp
Renderer* renderer = engine.GetRenderer();

// Setup camera
glm::mat4 view = glm::lookAt(
    glm::vec3(0, 0, 5),
    glm::vec3(0, 0, 0),
    glm::vec3(0, 1, 0)
);
renderer->SetViewMatrix(view);

// Draw primitives
renderer->DrawCube(glm::vec3(0), glm::vec3(1), glm::vec3(1, 0, 0));
renderer->DrawSphere(glm::vec3(3, 0, 0), 0.5f, glm::vec3(0, 1, 0));
```

### Input Handling

```cpp
InputManager* input = engine.GetInputManager();

if (input->IsKeyDown(KeyCode::W))
{
    // Move forward
}

if (input->IsMouseButtonPressed(MouseButton::Left))
{
    // Fire weapon
}

glm::vec2 mousePos = input->GetMousePosition();
```

### Physics

```cpp
// Create a rigid body
uint32_t sphere = physicsSystem->CreateRigidBody(
    glm::vec3(0, 5, 0),  // Position
    glm::vec3(1, 1, 1),  // Scale
    1.0f                 // Mass
);

// Update physics each frame
physicsSystem->Update(deltaTime);
```

## Performance Considerations

### Memory Management
- Use object pooling for frequently created/destroyed objects
- Pre-allocate renderer buffers where possible
- Monitor physics body count (target: < 1000 for 60 FPS)

### Rendering Optimization
- Batch draw calls (combine meshes with same material)
- Use LOD (Level of Detail) for distant objects
- Implement frustum culling
- Profile with NSight or RenderDoc

### Physics Optimization
- Reduce collision checking frequency for non-critical objects
- Use simple collision shapes (boxes, spheres)
- Limit simulation iterations

## Future Roadmap

### Phase 1 (Current)
- ✅ Basic engine structure
- ✅ Window/graphics context
- ✅ Simple 3D renderer
- [ ] Complete physics integration
- [ ] Music/sound playback

### Phase 2
- [ ] Asset pipeline (models, textures)
- [ ] Animation system
- [ ] Particle effects
- [ ] Terrain support
- [ ] Advanced lighting

### Phase 3
- [ ] Network/Multiplayer
- [ ] Mobile support
- [ ] Performance profiler
- [ ] Visual debugger
- [ ] Hot reload support

## Debugging

### Enable Debug Logging

```cpp
Logger::SetLevel(LogLevel::Debug);
AV_LOG_DEBUG("Debug message");
AV_LOG_ERROR("Error occurred");
```

### Using RenderDoc

1. Launch RenderDoc
2. Select AURIVIA executable
3. Capture frame
4. Inspect draw calls and shaders

### Profiling

Use `get_timeline()` API to profile frame time:
```cpp
auto start = std::chrono::high_resolution_clock::now();
// ... do work ...
auto elapsed = std::chrono::duration<float>(
    std::chrono::high_resolution_clock::now() - start
).count();
```

## Contributing

### Code Style
- Use camelCase for variables/functions
- Use PascalCase for classes
- Prefix member variables with `m_`
- Add documentation comments for public APIs

### Submitting Changes
1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests
5. Submit PR with description

## License

MIT License - See LICENSE file for full details

## Support & Community

- **Documentation**: [docs/](./docs/)
- **Issues**: GitHub Issues
- **Discord**: [Join our server](DISCORD_LINK)
- **Forum**: [Community Board](FORUM_LINK)

---

**Current Version**: 0.1.0 (MVP)  
**Last Updated**: 2026-04-14
