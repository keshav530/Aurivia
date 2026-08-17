// AURIVIA Game Engine C# Bindings
// This file is the entry point for C# interop

using System;
using System.Runtime.InteropServices;

namespace Aurivia
{
    /// <summary>
    /// Core game loop and engine management
    /// </summary>
    public class Engine
    {
        [DllImport("aurivia_engine.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr CreateEngine(string title, uint width, uint height);

        [DllImport("aurivia_engine.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void DeleteEngine(IntPtr engine);

        [DllImport("aurivia_engine.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern bool InitializeEngine(IntPtr engine);

        [DllImport("aurivia_engine.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void UpdateEngine(IntPtr engine, float deltaTime);

        [DllImport("aurivia_engine.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void RenderEngine(IntPtr engine);

        [DllImport("aurivia_engine.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern bool IsEngineRunning(IntPtr engine);

        [DllImport("aurivia_engine.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void ShutdownEngine(IntPtr engine);

        private IntPtr m_nativeHandle;

        public Engine(string title, uint width, uint height)
        {
            m_nativeHandle = CreateEngine(title, width, height);
        }

        public bool Initialize()
        {
            return InitializeEngine(m_nativeHandle);
        }

        public void Update(float deltaTime)
        {
            UpdateEngine(m_nativeHandle, deltaTime);
        }

        public void Render()
        {
            RenderEngine(m_nativeHandle);
        }

        public bool IsRunning => IsEngineRunning(m_nativeHandle);

        public void Shutdown()
        {
            ShutdownEngine(m_nativeHandle);
        }

        ~Engine()
        {
            DeleteEngine(m_nativeHandle);
        }
    }

    /// <summary>
    /// Input system for keyboard, mouse, and gamepad
    /// </summary>
    public class Input
    {
        public static bool GetKey(KeyCode key) => false; // TODO
        public static bool GetKeyDown(KeyCode key) => false; // TODO
        public static bool GetKeyUp(KeyCode key) => false; // TODO

        public static bool GetMouseButton(MouseButton button) => false; // TODO
        public static bool GetMouseButtonDown(MouseButton button) => false; // TODO
        public static bool GetMouseButtonUp(MouseButton button) => false; // TODO

        public static Vector2 GetMousePosition() => Vector2.Zero; // TODO
    }

    /// <summary>
    /// MonoBehavior-like component system
    /// </summary>
    public abstract class MonoBehavior
    {
        public GameObject gameObject { get; protected set; }
        public Transform transform { get; protected set; }

        public virtual void Awake() { }
        public virtual void Start() { }
        public virtual void Update() { }
        public virtual void LateUpdate() { }
        public virtual void OnDestroy() { }
    }

    /// <summary>
    /// Game object representation
    /// </summary>
    public class GameObject
    {
        public string name { get; set; }
        public Transform transform { get; private set; }
        private MonoBehavior[] m_components;

        public GameObject(string name)
        {
            this.name = name;
            this.transform = new Transform();
        }

        public T AddComponent<T>() where T : MonoBehavior, new()
        {
            var component = new T();
            component.gameObject = this;
            component.transform = this.transform;
            return component;
        }
    }

    /// <summary>
    /// Transform component
    /// </summary>
    public class Transform
    {
        public Vector3 position { get; set; }
        public Vector3 eulerAngles { get; set; }
        public Vector3 scale { get; set; }

        public Transform()
        {
            position = Vector3.Zero;
            eulerAngles = Vector3.Zero;
            scale = Vector3.One;
        }
    }

    /// <summary>
    /// 3D Vector
    /// </summary>
    public struct Vector3
    {
        public float x, y, z;

        public Vector3(float x, float y, float z)
        {
            this.x = x; this.y = y; this.z = z;
        }

        public static Vector3 Zero => new Vector3(0, 0, 0);
        public static Vector3 One => new Vector3(1, 1, 1);
    }

    /// <summary>
    /// 2D Vector
    /// </summary>
    public struct Vector2
    {
        public float x, y;

        public Vector2(float x, float y)
        {
            this.x = x; this.y = y;
        }

        public static Vector2 Zero => new Vector2(0, 0);
    }

    /// <summary>
    /// Key codes
    /// </summary>
    public enum KeyCode
    {
        A = 65, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        Num0 = 48, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
        Escape = 256, Enter, Tab, Backspace, Space = 32,
    }

    /// <summary>
    /// Mouse buttons
    /// </summary>
    public enum MouseButton
    {
        Left = 0,
        Right = 1,
        Middle = 2
    }

    /// <summary>
    /// Debug logging
    /// </summary>
    public static class Debug
    {
        public static void Log(object message) => Console.WriteLine("[LOG] " + message);
        public static void LogWarning(object message) => Console.WriteLine("[WARN] " + message);
        public static void LogError(object message) => Console.WriteLine("[ERROR] " + message);
    }
}
