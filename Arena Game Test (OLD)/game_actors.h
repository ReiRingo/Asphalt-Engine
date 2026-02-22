#ifndef GAME_ACTORS_H
#define GAME_ACTORS_H

#include "asphalt.h"

// -- Simple Bullet
class Bullet : public Actor {
public:
    Vector2 velocity;
    void onCreate() override { setMask(-4,-4,8,8); }
    void onUpdate(float dt) override {
        pos.x += velocity.x * dt;
        pos.y += velocity.y * dt;
        
        // Destroy if off-screen (simple version)
        if (Vector2Length(pos) > 2000) destroyed = true;
    }
    void onDraw(float dt) override { DrawCircleV(pos, 4, YELLOW); }
};

// -- Simple Enemy
class Enemy : public Actor {
public:
    float hp = 3;
    void onCreate() override { setMask(0,0,32,32); }
    void onUpdate(float dt) override {
        depth = pos.y; // Y-Sorting
    }
    void onDraw(float dt) override {
        DrawRectangleV(pos, {32, 32}, MAROON);
    }
};

// -- Player
class Player : public Actor {
public:
    float speed = 250.0f;
    void onCreate() override { setMask(0,0,32,32); }
    void onUpdate(float dt) override {
        // Movement
        if (IsKeyDown(KEY_W)) pos.y -= speed * dt;
        if (IsKeyDown(KEY_S)) pos.y += speed * dt;
        if (IsKeyDown(KEY_A)) pos.x -= speed * dt;
        if (IsKeyDown(KEY_D)) pos.x += speed * dt;

        // Shooting
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), SceneManager::GetCurrentScene()->camera);
            Vector2 dir = Vector2Normalize(Vector2Subtract(mouseWorld, pos));
            
            Bullet* b = Asphalt::instanceCreate<Bullet>(pos);
            b->velocity = Vector2Scale(dir, 500.0f);
        }

        // Use performAs to check all bullets against all enemies
        Asphalt::performAs<Bullet>([this](Bullet* b) {
            Asphalt::performAs<Enemy>([b](Enemy* e) {
                if (Asphalt::isColliding(b, e)) {
                    e->hp--;
                    b->destroyed = true;
                    if (e->hp <= 0) e->destroyed = true;
                }
            });
        });
        
        depth = pos.y; // << Equivalent to depth = -y;
    }

    void onDraw(float dt) override {
        DrawRectangleV(pos, {32, 32}, BLUE);
    }

    void onDrawUi(float dt) override {
        DrawText("WASD to Move | Click to Shoot", 10, 10, 20, RAYWHITE);
    }
};

#endif