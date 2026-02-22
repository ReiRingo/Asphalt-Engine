#include "scene_manager.h"
#include "game_scenes.h"

int main() {
    InitWindow(640, 480, "Asphalt Engine | Refactor Test");
    SetTargetFPS(60);

    // Initial Scene
    SceneManager::LoadScene(new MenuScene());

    while (!WindowShouldClose()) {
        // 1. SceneManager handles ALL logic
        // (Better reusability)
        SceneManager::Update();

        // 2. Rendering
        BeginDrawing();
            ClearBackground(BLACK);
            
            // Draw world (Camera) + UI (HUD)
            SceneManager::Draw();
            
            // Debugging:
            // DrawFPS(550, 450);
        EndDrawing();
    }

    SceneManager::Unload();
    CloseWindow();
    return 0;
}