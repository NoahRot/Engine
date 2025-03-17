🛠 Mandatory Components (Core Engine)
These are the absolute essentials to get your engine running. Start with these.

1️⃣ Core System

    [ ] Engine (Main entry point to manage initialization and shutdown)
    [V] Logger (Singleton to handle logging/debugging)
    [V~] Config Manager (Handles engine settings, file-based config loading, etc.)

2️⃣ Windowing & Graphics

    [V] Window (SDL2-based window creation and management)
    [ ] Renderer (OpenGL context setup and rendering pipeline)
    [ ] ShaderManager (Handles GLSL shaders)
    [ ] TextureManager (Loads and manages OpenGL textures)

3️⃣ Input Handling

    [V] InputManager (Manages keyboard, mouse, and gamepad input using SDL events)

4️⃣ Game Loop

    [V] TimeManager (Keeps track of delta time and FPS)
    [ ] EventManager (Handles SDL events)
    [ ] SceneManager (Switches between different game states/scenes)

5️⃣ Resource Management

    [ ] AssetManager (Handles loading/unloading of textures, models, sounds, etc.)
    [ ] FileSystem (File loading, paths, etc.)

🔹 Good to Have (Improves Usability & Performance)
These are not strictly required but make the engine more functional and optimized.

6️⃣ Rendering Improvements

    [ ] Mesh (Basic model/geometry management)
    [ ] Material (Handles shaders, textures, and properties)
    [ ] Framebuffer (Allows post-processing, screen effects)
    [ ] Font Rendering (Using FreeType for text rendering)
    [ ] 2D Renderer (Batch rendering for sprites, UI elements)

7️⃣ Audio

    [V] AudioManager (Using SDL_mixer or OpenAL for sound effects and music)
    [ ] AudioSource (Component to play sounds in 3D space)

8️⃣ Scene & Entity System

    [ ] Entity (Base class for objects in the world)
    [ ] ComponentSystem (Basic ECS architecture for extensibility)
    [ ] TransformComponent (Handles position, rotation, scale)

9️⃣ Physics (Basic)

    [ ] PhysicsWorld (Using Box2D or Bullet for physics simulation)
    [ ] ColliderComponent (Defines collision shapes)
    [ ] RigidbodyComponent (Handles movement and forces)

🔹 Optional / Advanced (For Later Development)
These are complex but will significantly enhance the engine.

🔟 Advanced Rendering

    [ ] Deferred Rendering (Optimized rendering pipeline)
    [ ] Shadow Mapping (Dynamic lighting/shadows)
    [ ] Post-Processing (Bloom, motion blur, etc.)
    [ ] PBR (Physically-Based Rendering) (Realistic lighting and materials)

🔟 Scripting & AI

    [ ] Scripting System (Lua or Python integration for gameplay logic)
    [ ] AI System (Pathfinding, behavior trees)

🔟 Networking

    [ ] Networking Module (Using ENet or custom UDP/TCP for multiplayer support)

🔟 Editor / Debugging

    [ ] Engine Editor (ImGui-based UI for level editing)
    [ ] Profiler (FPS counter, memory tracking)