# 🏎️ Asphalt Engine
A lightweight, actor-based 2D game engine wrapper for [raylib](https://www.raylib.com/).

Asphalt Engine simplifies the raylib boilerplate by providing a structured **Actor-Event** system. It handles object lifecycles, depth sorting, and memory management, allowing you to focus on gameplay logic rather than the game loop mechanics.

## ✨ Features
* **Event-Driven Actors**: Inherit from the `Actor` class to use `onCreate`, `onUpdate`, and `onDraw`.
* **Automatic Depth Sorting**: Objects are rendered based on their `depth` value—no more manual draw-order headaches.
* **Smart Lifecycle Management**: Automatic cleanup of textures and memory when an actor is destroyed.
* **Type-Safe Interaction**: Use the `performAs<T>` utility to safely interact with specific actor types.
* **MIT Licensed**: Free to use for personal and commercial projects.

## 🚀 Quick Start

### 1. Define an Actor
```cpp
class Player : public Actor {
public:
    void onCreate() override {
        sprite = LoadTexture("assets/player.png");
        pos = { 100, 100 };
    }

    void onUpdate(float deltaTime) override {
        if (IsKeyDown(KEY_RIGHT)) pos.x += 200 * deltaTime;
        // Update your collision mask here
        setMask(pos.x, pos.y, 32, 32);
    }

    void onDraw(float deltaTime) override {
        DrawTextureV(sprite, pos, WHITE);
    }
};
```

### 2. Add to the Game Loop
In your main.cpp, simply push your actor to the birth queue:

```cpp
actorsToAdd.push_back(new Player()); // Before the while() loop
```

# 🛠️ Engine Architecture
Asphalt uses a 5-phase loop every frame:

**Create:** New actors are initialized and added to the active pool.

**Update:** Logic and physics are calculated.

**Sort:** Actors are sorted by depth (Lower values = Background, Higher values = Foreground).

**Draw:** Actors render their sprites to the buffer.

**Destroy:** Flagged actors are cleaned up and memory is freed.

# 🏗️ Requirements
### C++17 or higher.

### raylib 5.0+

### g++ (MinGW-w64) compiler.

> *Note: It must support C++17 or higher (GCC 7+).*

Operating System: Windows (currently supported via the included .bat scripts).

# 🛠️ How to build

1. **Install MinGW-w64**: Ensure you have `g++` installed. You can check by typing `g++ --version` in your terminal.
2. **Clone the Repo**:
   ```bash
   git clone [https://github.com/ReiRingo/AsphaltEngine.git](https://github.com/ReiRingo/Asphalt-Engine.git)
   ```

# 📜 License
This project is licensed under the MIT License - see the LICENSE file for details.