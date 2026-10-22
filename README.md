Order

- Project setup. Git, CMake, dependency management (vcpkg, FetchContent, or vendored SDL3), compiler warnings on, sanitizers (ASan/UBSan) in debug builds. Fix this before any code exists.

- Window, loop, timing. SDL3 init, window, renderer, event pump, clean shutdown. Implement a fixed-timestep update with variable-rate render. Measure delta time with SDL_GetPerformanceCounter. Changing the loop structure later is expensive.

- Input abstraction. Map scancodes to actions (your Action enum), separate discrete events from polled held-key state. Add gamepad mapping here, not later.

- Rendering primitives. Draw rectangles, then textures, then sprites with source rects. Add a camera (world-to-screen transform). Keep drawing code behind a thin interface; do not scatter SDL_Render* calls through gameplay code.

- Debug tooling. Logging, on-screen FPS and frame time, Dear ImGui overlay, collision-box visualization. Every later stage is faster with these.

- Entity model and update/render split. Start with a plain struct or array of structs. Do not build an ECS yet. Separate update(dt) from render(). Game state must be drawable without mutating it.

- Core mechanic with placeholder art. Movement, collision (AABB first), and the single action the game is about. Use colored rectangles. Tune until it feels right. If this is not fun, nothing downstream fixes it.

- Vertical slice. One level, one enemy or obstacle type, one win condition, one lose condition, restartable. End-to-end playable. This exposes architecture problems while the code is still small.

- Asset loading. Texture, font, and audio loaders with a cache keyed by path or ID. Load once, free on shutdown. Introduce a simple ownership rule (resource manager owns, everything else borrows).

- Game state machine. Boot, menu, playing, paused, game over. A stack of states (push pause over play) handles most cases.

- Level data format and loader. Replace hardcoded levels with data files. Include a version field. Use Tiled or LDtk before building a custom editor.

- Audio. Sound effects and music through SDL3 audio streams or SDL_mixer. Add volume control and a mixer abstraction.

- UI and HUD. Text rendering, menus, health or score display, input navigation for menus.
Save/load and settings. Persist progress and options (resolution, volume, key bindings). Use SDL_GetPrefPath for the directory.
- Content production. Levels, enemies, items, progression. Build the editor or extend the level tool here if the content volume demands it.

- Polish. Animation, particles, screen shake, transitions, sound feedback. Profile before optimizing. Fix measured bottlenecks only.

- Packaging. Release builds, asset bundling, platform builds, crash handling, and testing on a clean machine.

Rules for the sequence

The game is playable after every step from 7 onward. Never spend weeks on infrastructure with nothing on screen.
Add an abstraction when the second use appears, not before.
Defer ECS, scripting languages, plugin systems, and custom allocators until a concrete problem requires them.
Keep the engine layer (window, input, renderer, assets) separate from game code from the beginning, as a directory boundary at minimum.
Commit working states. Tag the vertical slice.
Scope: finish a small game first. A complete small game teaches the packaging, state, and polish steps that unfinished large projects never reach.
