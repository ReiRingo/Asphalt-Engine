#ifndef PLAYER_H
#define PLAYER_H

#include "actor.h"
#include "raylib.h"

// Player Example
class Player : public Actor {
    public:

    void onCreate() override {
        depth = 5.0f;
        std::cout << "Alive and well!" << std::endl;
    }

    void onUpdate(float dt) override {
        // What happens here?
    }

    void onDraw(float dt) override {
        // Draw sprite here manually
    }
};

#endif