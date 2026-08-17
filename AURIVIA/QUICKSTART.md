# AURIVIA Quick Start Guide

Get your first game running in minutes!

## Step 1: Build the Engine (2 min)

### Windows (Visual Studio 2022)
```powershell
cd C:\Users\Keshav\OneDrive\Desktop\AURIVIA
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

### Or use the build script
```powershell
.\build.ps1 -Configuration Release
```

## Step 2: Run the Demo (1 min)

```powershell
.\bin\Release\cube_demo.exe
```

You should see a rotating blue cube in a window. Congrats! 🎉

## Step 3: Create Your First Game (5 min)

### In C#

Create a file `MyGame.cs`:

```csharp
using Aurivia;

public class MyPlayerController : MonoBehavior
{
    public float speed = 5f;
    private Vector3 velocity;
    
    public void Update()
    {
        // Get input
        float moveZ = 0;
        float moveX = 0;
        
        if (Input.GetKey(KeyCode.W)) moveZ += 1;
        if (Input.GetKey(KeyCode.S)) moveZ -= 1;
        if (Input.GetKey(KeyCode.A)) moveX -= 1;
        if (Input.GetKey(KeyCode.D)) moveX += 1;
        
        // Move
        velocity = new Vector3(moveX, 0, moveZ);
        transform.position += velocity * speed * Time.deltaTime;
        
        Debug.Log($"Position: {transform.position.x}, {transform.position.z}");
    }
}
```

### In C++

Create a simple game scene:

```cpp
#include "aurivia/engine.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace Aurivia;

int main()
{
    Engine engine("My First Game", 1280, 720);
    
    if (!engine.Initialize())
        return -1;
    
    float rotation = 0.0f;
    
    while (engine.IsRunning())
    {
        float dt = engine.GetFrameTime();
        
        // Update
        rotation += 45.0f * dt; // Rotate 45° per second
        
        // Render
        engine.GetRenderer()->Clear();
        engine.GetRenderer()->BeginFrame();
        
        // Draw a rotating cube
        engine.GetRenderer()->DrawCube(
            glm::vec3(0),
            glm::vec3(1),
            glm::vec3(1, 0, 0) // Red
        );
        
        engine.GetRenderer()->EndFrame();
    }
    
    engine.Shutdown();
    return 0;
}
```

## Step 4: Explore the Systems

### Input Handling
```csharp
if (Input.GetKeyDown(KeyCode.Space))
    Debug.Log("Space pressed!");

if (Input.GetMouseButtonDown(MouseButton.Left))
    Debug.Log("Click!");

Vector2 mousePos = Input.GetMousePosition();
```

### 3D Rendering
```cpp
renderer->DrawCube(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec3(1, 0, 0));
renderer->DrawSphere(glm::vec3(3, 0, 0), 0.5f, glm::vec3(0, 1, 0));
```

### Physics (Coming Soon)
```cpp
physicsSystem->CreateRigidBody(position, scale, mass);
physicsSystem->Update(deltaTime);
```

## File Locations

```
Your Game Code
    ↓
C:\Users\Keshav\OneDrive\Desktop\AURIVIA\samples\your_game\
    ↓
Add to CMakeLists.txt:
    add_executable(your_game your_game/main.cpp)
    target_link_libraries(your_game aurivia_engine)
    ↓
Rebuild: cmake --build . --config Release
    ↓
Run: .\bin\Release\your_game.exe
```

## Debugging Tips

### Enable Verbose Logging
```cpp
Logger::SetLevel(LogLevel::Debug);
```

### Log Debug Info
```csharp
Debug.Log("Variable: " + value);
Debug.LogWarning($"Warning at position {x}, {y}");
Debug.LogError("Critical error!");
```

### Visual Debugging
- Use RenderDoc to inspect draw calls
- Check `AURIVIA\assets\` for shader source
- Monitor Windows Task Manager for frame time

## Common Issues

### Build Fails with "GLFW not found"
**Solution**: CMake will auto-download GLFW. Make sure internet is available.

### Demo doesn't show anything
**Solution**: Your GPU might not support OpenGL 4.3. Update drivers.

### C# bindings not found
**Solution**: Build aurivia_engine first, then reference Aurivia.NET.cs

## Next Steps

1. **Create your first scene** with cubes and spheres
2. **Add user input** (WASD movement, mouse look)
3. **Integrate physics** (add gravity when released)
4. **Add audio** (footsteps, background music)
5. **Polish with effects** (particles, post-processing)

## Project Ideas

### Easy
- ✅ Rotating cube (done!)
- Pong game (2D, simple physics)
- Dodge-'em game (avoid falling objects)

### Medium
- Third-person camera
- Simple platformer
- Space shooter

### Hard
- Full 3D game
- Multiplayer game
- Open-world sandbox

## Learning Resources

- [DEVELOPMENT.md](DEVELOPMENT.md) - Detailed API docs
- [ARCHITECTURE.md](ARCHITECTURE.md) - How the engine works
- [samples/cube_demo/](samples/cube_demo/) - Reference implementation
- [bindings/csharp/](bindings/csharp/) - C# API reference

## Get Help

- Check the documentation files
- Review sample code
- Open a GitHub issue with details

---

**Ready?** Run `cube_demo.exe` and see your first AURIVIA game! 🚀
