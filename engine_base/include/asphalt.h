#ifndef ASPHALT_H
#define ASPHALT_H

#include "raylib.h"
#include "raymath.h"
#include "scene_manager.h"
#include <vector>

namespace Asphalt {

    // --- Collision ---
    
    // Checks AABB collision between two actors using their masks
    inline bool isColliding(Actor* a, Actor* b) {
        if (!a || !b || a == b) return false;
        
        Rectangle r1 = { a->pos.x + a->mask.x, a->pos.y + a->mask.y, a->mask.width, a->mask.height };
        Rectangle r2 = { b->pos.x + b->mask.x, b->pos.y + b->mask.y, b->mask.width, b->mask.height };
        
        return CheckCollisionRecs(r1, r2);
    }

    // --- Instance Management ---

    // Quickly spawn an actor into the current scene
    template <typename T>
    inline T* instanceCreate(Vector2 position) {
        T* newActor = new T();
        newActor->pos = position;
        SceneManager::GetCurrentScene()->addActor(newActor);
        return newActor;
    }

    // Find the first actor of a specific type
    template <typename T>
    inline T* instanceFind() {
        auto& actors = SceneManager::GetCurrentScene()->getActors(); // Requires a getter in Scene
        for (auto* a : actors) {
            if (T* target = dynamic_cast<T*>(a)) return target;
        }
        return nullptr;
    }

    // --- Math Helpers ---
    // I suck at math, frfr but that's fine :)

    // Get the Euclidean distance between two points
    inline float distanceTo(Vector2 p1, Vector2 p2) {
        return Vector2Distance(p1, p2);
    }

    // Get the angle between two points in degrees
    inline float angleTo(Vector2 p1, Vector2 p2) {
        return Vector2Angle(p1, p2) * RAD2DEG;
    }

    // Iterates through specific actors and run Funcs from it.
    template <typename T, typename Func>
    inline void performAs(Func action) {
        // Automatically grab actors from the active scene
        auto& actors = SceneManager::GetCurrentScene()->getActors();
        
        for (Actor* actor : actors) {
            // Observation: dynamic_cast checks if the actor "is a" T
            if (T* target = dynamic_cast<T*>(actor)) {
                if (!target->destroyed) {
                    action(target);
                }
            }
        }
    }

    // -- GLOBAL COLOURS (GameMaker-style)
    static Color colour = WHITE;
    
    // Setter
    inline void drawColour(Color col) {
        colour = col;
    }

    // Getter
    inline Color drawGetColour() {
        return colour; // < Copy instead, so people can use it.
    }

    // -- GLOBAL FONT! (GameMaker-style)
    static Font font;

    // Setter
    inline void drawFont(Font fnt) {
        font = fnt;
    }

    // Getter
    inline Font drawGetFont() {
        return font;
    }

    // Draw Texts
    inline void drawText(const char* text, int x, int y, float scale = 20.0f, float spacing = 1.0f) {
        DrawTextEx(font, text, Vector2{ (float)x, (float)y }, scale, spacing, colour);
    }
}

#endif