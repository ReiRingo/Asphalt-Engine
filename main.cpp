#include "raylib.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include "actor.h"  // Actors
#include "player.h" // Player actor test

// *** -- Main Function - Entry Point
int main() {
    // Directory Init
    ChangeDirectory(GetApplicationDirectory());

    // Config
    std::string WindowName = "Asphalt Engine";   // Change to whatever you want your window to be named
    int FPS = 30;                                // Old school RPG
    Color DefaultWindowColour = BLACK;           // The 'background'

    // Initialisation
    InitWindow(640, 480, WindowName.c_str());
    SetTargetFPS(FPS);

    // -- Game Loop
    // Actors
    std::vector<Actor*> actors;
    std::vector<Actor*> actorsToAdd;

    // Actor Init
    actorsToAdd.push_back(new Player());    // Add player to the game
    // actorsToAdd.push_back(new Freakbob());  // Add freakbob to the game

    // Main Game Loop
    while(!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        
        // 0. Create Phase
        for (Actor* actor : actorsToAdd) {
            actor->onCreate();
            actors.push_back(actor);
        }
        actorsToAdd.clear(); // Empty the temp list after adding to main list

        // 1. Update Phase
        for (Actor* actor : actors) {
            if (!actor->destroyed) actor->onUpdate(deltaTime);
        }

        // 2. Sort Phase
        std::sort(actors.begin(), actors.end(), [](Actor* a, Actor* b) {
            return a->depth < b->depth; 
        });

        // 3. Draw Phase
        BeginDrawing();
            ClearBackground(DefaultWindowColour);
            for (Actor* actor : actors) {
                if (!actor->destroyed) actor->onDraw(deltaTime);
            }
        EndDrawing();

        // 4. Destroy Phase
        actors.erase(std::remove_if(actors.begin(), actors.end(), [](Actor* actor) {
            if (actor->destroyed) {
                actor->onDestroy();
                actor->onEnd();
                UnloadTexture(actor->sprite); // Important: Free the GPU texture!
                delete actor;
                return true;
            }
            return false;
        }), actors.end());
    }

    // Clean Up
    for (Actor* actor : actors) {
        actor->onEnd();
        delete actor; // Free memory.
    }

    CloseWindow();
    return 0;
}

// *** Functions
template <typename T, typename Func>
void performAs(std::vector<Actor*>& actors, Func action) {
    for (Actor* actor : actors) {
        if (T* target = dynamic_cast<T*>(actor)) {
            action(target);
        }
    }
}

/* *** EXAMPLE:
// Inside Main
performAs<Freakbob>(actors, [](Freakbob* fb) {
    fb->pos.x = 10.0f; // Sets the pos.x of performed freakbob to 10.0f
    fb->pos.y = 10.0f; // sets pos.y instead!
})
*/

/*
bool isColliding(Actor* act1, Actor* act2) {
    if (act1 == act2) return false; // Why would you even...

    // TODO: Collision check soon!
}
*/

// 000101010111001010101 10 010 0010100 11001 01100101 01010100 100 0101
// ^^ Gibberish. (This means nothing, I'm just keeping my sanity.)