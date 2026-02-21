#ifndef ACTOR_H
#define ACTOR_H

#include "raylib.h"

class Actor {
    public:
    virtual ~Actor() {}

    // -- Properties
    Texture2D sprite;
    Rectangle frameRect = {0,0,0,0};
    Rectangle mask = {0,0,0,0}; 
    
    Vector2 pos = {0, 0};
    float depth = 0.0f;                      // Y-sorting buffer
    bool destroyed = false;

    // -- Lifecycle
    virtual void onCreate() {}
    virtual void onUpdate(float dt) {}
    
    // World Space Drawing (Affected by Camera)
    virtual void onDraw(float dt) {} 
    
    // Screen Space Drawing (HUD, Health bars - NOT affected by Camera)
    virtual void onDrawUi(float dt) {} 

    virtual void onDestroy() {}
    virtual void onEnd() {}

    // -- Utils
    void setMask(float x, float y, float w, float h) {
        mask = {x, y, w, h};
    }
};

#endif