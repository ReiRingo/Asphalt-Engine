#ifndef ACTOR_H
#define ACTOR_H

#include "raylib.h"

class Actor {
    public:
    // Destructor
    virtual ~Actor() {}

    // -- Actor Parent Properties
    // Sprite
    Texture2D sprite;       // Sprite / Sprite sheet
    Rectangle frameRect;    // Animation frame rectangle
    Rectangle mask;         // For collision / place
    int currentFrame = 0;
    int totalFrames = 4;
    float animTimer = 0.0f;
    bool destroyed = false;

    // Position and Depth
    Vector2 pos = {0, 0};
    float depth = 0.0f;

    // Events
    virtual void onCreate() {}
    virtual void onUpdate(float deltaTime) {}
    virtual void onDraw(float deltaTime) {}
    virtual void onDestroy() {}
    virtual void onEnd() {}

    // Usable methods
    Rectangle setMask(float x, float y, float w, float h) {
        mask.x = x;
        mask.y = y;
        mask.width = w;
        mask.height = h;
        return mask;
    }
};

#endif