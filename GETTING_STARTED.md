# Getting Started with Asphalt

## Welcome to Asphalt

> ***A lightweight, scene-based 2D engine wrapper for Raylib.***

This small guide will help get you from zero to a working scene.

> Make sure to read throughly.

## Environment Setup

Asphalt doesn't require a heavy IDE.

Since Raylib is already pre-installed (when you create a new project), you just need a text editor and a compiler.

**Recommended Editors**: VS Code, Notepad++, or even a simple terminal-based editor like Vim/Nano.

## Project Structure:

Please keep your structure clean and consistent!

Use headers as much as possible and keep **main.cpp** clean.

It is not mandatory, but code hygiene is good practise. (Let's be civilised.)

## Creating a Project

To create a project, simply run the **create_project** bat file.

This will prompt you to name your folder, which will then copy the needed files into the specified folder.

## Core Structure

- Scenes manage Actors.

- Actors contain behaviour.

- The Scene handles updating and drawing all active Actors.

- Scene Manager handles Scenes.

- You control the main game loop.

## Creating Actors

**Actors** are the "objects" of your game (Players, Enemies, Bullets, Managers).

Every Actor has a **lifecycle:** onCreate, onUpdate, onDraw, and onDrawUi.

**onCreate**: Runs once after the actor's creation (When called via `instanceCreate<...>`).

**onUpdate**: Runs every frame but before **onDraw** and **onDrawUi**

**onDraw**: Runs every frame after **onUpdate** but before **onDrawUi**

**onDrawUi**: Runs every frame after everything else.

Create a file named **game_actors.h**:

> I recommend placing them in the same directory as main.cpp

```cpp
#ifndef GAME_ACTORS_H
#define GAME_ACTORS_H

#include "asphalt.h"

class Player : public Actor {
public:
    float speed = 200.0f;

    void onCreate() override {
        pos = { 320, 240 }; // Start in the middle
        // Define a collision mask (x_offset, y_offset, width, height)
        setMask(0, 0, 32, 32); 

        // Define a static sprite (Optional)
        // sprite = LoadTexture("assets/your_sprite.png");
    }

    void onUpdate(float dt) override {
        // Movement logic
        if (IsKeyDown(KEY_W)) pos.y -= speed * dt;
        if (IsKeyDown(KEY_S)) pos.y += speed * dt;
        if (IsKeyDown(KEY_A)) pos.x -= speed * dt;
        if (IsKeyDown(KEY_D)) pos.x += speed * dt;

        // Depth sorting (Optional: keeps actors drawn correctly based on Y position)
        depth = pos.y; 
    }

    void onDraw(float dt) override {
        // Draw the player (World Space)
        DrawRectangleV(pos, {32, 32}, BLUE);
        // Sprites (Optional)
        // DrawTexture(sprite, pos.x, pos.y, WHITE);
    }

    void onDrawUi(float dt) override {
        // Draw HUD elements (Screen Space - ignores camera)
        Asphalt::drawText("PLAYER 1", (int)pos.x, (int)pos.y - 20, 10);
    }
};

#endif
```

## Setting the Scene

Scenes hold your actors and manage the camera.

Create a file named **game_scenes.h**:

> Again, I recommend placing them in the same directory as main.cpp

```cpp
#ifndef GAME_SCENES_H
#define GAME_SCENES_H

#include "asphalt.h"
#include "game_actors.h"

class LevelOne : public Scene {
public:
    void onStart() override {
        // Use Asphalt's helper to spawn the player
        Asphalt::instanceCreate<Player>(Vector2{ 0, 0 });
        // The player's create function runs after this.
        
        // Initialise camera
        camera.zoom = 1.0f;
        camera.offset = { 320, 240 };
        // target = what the camera looks at
        // offset = where that target appears on screen
    }

    void updateScene(float dt) override {
        // Call the base update to handle actor lifecycles
        Scene::updateScene(dt);

        // Update camera to follow the player
        Player* p = Asphalt::instanceFind<Player>();
        if (p) camera.target = p->pos; // You can add a smooth lerp as well
    }
};

#endif
```

## Running the game

In the **main.cpp**, you simply initialise the **SceneManager** and load your first scene:

```cpp
#include "scene_manager.h"
#include "game_scenes.h"

int main() {
    InitWindow(640, 480, "My Asphalt Game");
    
    // Load your font and set the first scene
    // Asphalt::drawFont(LoadFont("...")); // Font asset file goes in here
    SceneManager::LoadScene(new LevelOne());
    // SceneManager owns the scenes
    // And manages the clean up.
    // Although, if you draw sprites directly from a scene
    // The SceneManager won't Unload it!
    // It's deprecated to draw sprites from a scene.

    while (!WindowShouldClose()) {
        SceneManager::Update(); // Handles logic and scene transitions
        
        BeginDrawing();
            ClearBackground(RAYWHITE);
            SceneManager::Draw(); // Draws all actors in the current scene
        EndDrawing();
    }

    SceneManager::Unload();
    CloseWindow();
    return 0;
}
```

## Asphalt Utilities

The `Asphalt::` namespace contains several helpers to make development easier:

| Function                | Description                                                 |
|-------------------------|-------------------------------------------------------------|
| instanceCreate<T>(pos)  | Spawns a new Actor of type T at the given position.         |
| instanceFind<T>()       | Returns the first instance of type T found in the scene.    |
| isColliding(a, b)       | Checks AABB collision using masks.                          |
| performAs<T>(func)      | Runs a function on every active instance of type T.         |
| angleTo(p1, p2)         | Returns the angle between two points in degrees.            |

As well as draw functions:

| Function                                  | Description                                   |
|-------------------------------------------|-----------------------------------------------|
| drawColour(colour)                        | Changes the global colour (for drawText())    |
| drawFont(font)                            | Changes the global font (for drawText())      |
| drawText(text, x, y, [scale], [spacing])  | Draws a text based from the global properties |

## Tip

Don't be afraid to look at the underlying headers and their functions.

This isn't a large engine, since it's generally based on raylib.

It wouldn't hurt to check. (Just don't touch any. Unless you know what you're doing.)

It's also heavily docummented with commends - if you like to read.

## Notes:

- Asphalt does not replace the Raylib game loop — you still control the window lifecycle.

- Some functions expose float dt (delta time) even if the example doesn’t use it. It’s there for time-based movement, animation, and interpolation.

- This is still in development, so you may encounter limits. But since this isn't tied to a game IDE / engine, you can fix it yourself for now.

# Known bugs / errors / compilation issues:

## 1. The Order (Forward-declaration)

Sometimes, the order gets all trippy.

If one scene loads another scene that hasn’t been fully defined yet, you may encounter a compilation error.

Declare both classes first, then define their member functions below.

**To fix that**, you initialise both, then write the code for each below both!

```cpp
// *** Initialise
class YourScene : public Scene {
    public:
    void onStart() override;
    void updateScene(float deltaTime) override;
};

class AnotherScene : public Scene {
    public:
    void onStart() override;
    void updateScene(float deltaTime) override;
};

// *** Define Functions

// - YourScene
YourScene::onStart() {}
YourScene::updateScene(float deltaTime) {
    if (IsKeyPressed(KEY_Z)) {
        SceneManager::LoadScene(new AnotherScene()); // This would work now
    }
};

// - AnotherScene
AnotherScene::onStart() {}
AnotherScene::updateScene(float deltaTime) {
    Asphalt::drawText("Works now!", 100, 100);
}
```

# End of Guide!

Thanks for being with me until the end! I really appreciate it.

> *If you find a bug, do report. Even if you could fix it yourself, it would help me as the owner of the engine :>.*