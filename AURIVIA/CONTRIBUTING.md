# Contributing to AURIVIA

Thank you for your interest in contributing to AURIVIA! This document outlines how you can help.

## Getting Started

1. **Fork** the repository
2. **Clone** your fork: `git clone https://github.com/your-username/AURIVIA.git`
3. **Create a branch** for your feature: `git checkout -b feature/my-feature`
4. **Make your changes** and test thoroughly
5. **Commit** with clear messages: `git commit -m "Add feature: description"`
6. **Push** to your fork: `git push origin feature/my-feature`
7. **Submit a Pull Request** describing your changes

## Code Guidelines

### C++ Style
```cpp
// Classes and namespaces use PascalCase
namespace Aurivia {
    class MyClass {
    private:
        // Member variables prefix with m_
        int m_count;
        std::string m_name;
        
    public:
        // Methods use camelCase
        void Initialize();
        bool IsValid() const;
    };
}
```

### C# Style
```csharp
// Follow C# naming conventions
namespace Aurivia
{
    public class MyComponent : MonoBehavior
    {
        // Properties use PascalCase
        public float Speed { get; set; }
        
        // Methods use PascalCase
        public void Initialize() { }
    }
}
```

## Areas to Contribute

### High Priority
- Complete physics system integration
- Implement audio playback
- Add more primitive shapes (sphere, plane)
- Cross-platform testing

### Medium Priority
- Animation system
- Particle effects
- Asset loader
- Performance profiling tools

### Documentation
- API documentation
- Tutorial videos
- Example projects
- Architecture diagrams

## Testing

Before submitting a PR:
1. Build with `cmake --build . --config Release`
2. Run sample: `./bin/cube_demo`
3. Test input handling and rendering
4. Verify no warnings/errors

## Reporting Issues

Include:
- System information (OS, compiler, GPU)
- Minimal reproduction case
- Expected vs actual behavior
- Relevant logs or screenshots

## Code Review Process

All PRs require:
- Code review (at least 1 maintainer)
- Tests for new features
- Documentation updates
- CI/CD checks passing

## License

By contributing, you agree your code will be licensed under the MIT License.

---

**Questions?** Open an issue or email: aurivia-dev@example.com
