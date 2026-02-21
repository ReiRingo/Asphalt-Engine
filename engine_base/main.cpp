#include "raylib.h"
#include "scene_manager.h"
#include "asphalt.h"

int main() {
    // Settings
    ChangeDirectory(GetApplicationDirectory());
    InitWindow(640, 480, "Asphalt Engine");
    SetTargetFPS(30);

    // Default Draw Properties
    Font defFont = LoadFont("assets/default_font.ttf");
    Asphalt::drawFont(defFont);
    Asphalt::drawColour(WHITE);

    // Load the first scene
    // SceneManager::LoadScene(new YourScene());

    while (!WindowShouldClose()) {
        // The Manager handles the scary "delete/new" logic safely
        SceneManager::Update();

        BeginDrawing();
        ClearBackground(BLACK);
            
            // \/ This handles the drawing of every actor and scenes.
            SceneManager::Draw();
        
        EndDrawing();
    }

    UnloadFont(defFont);
    SceneManager::Unload();
    CloseWindow();
    return 0;
}