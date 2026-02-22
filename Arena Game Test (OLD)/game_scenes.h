#ifndef GAME_SCENES_H
#define GAME_SCENES_H

#include "game_actors.h"

// --- 1. DECLARATIONS (Tell the compiler WHAT they are) ---

class MenuScene : public Scene {
public:
    void onStart() override;
    void drawScene(float dt) override;
};

class LevelOne : public Scene {
public:
    Player* playerRef = nullptr;
    void onStart() override;
    void updateScene(float dt) override;
};

// --- 2. IMPLEMENTATIONS (Now we tell the compiler HOW they work) ---

// Menu Logic
void MenuScene::onStart() {
    // Nothing needed
}

void MenuScene::drawScene(float dt) {
    DrawText("Alpha Wolf Sigma", 160, 150, 40, YELLOW);
    DrawText("Press ENTER to Start", 210, 220, 20, GRAY);
    
    if (IsKeyPressed(KEY_ENTER)) {
        // This works now because LevelOne was fully declared above!
        SceneManager::LoadScene(new LevelOne());
    }
}

// Level Logic
void LevelOne::onStart() {
    camera.zoom = 1.0f;
    camera.offset = { 320, 240 };
    playerRef = Asphalt::instanceCreate<Player>({0, 0});

    for(int i = 0; i < 20; i++) {
        Asphalt::instanceCreate<Enemy>({ (float)GetRandomValue(-500, 500), (float)GetRandomValue(-500, 500) });
    }
}

void LevelOne::updateScene(float dt) {
    Scene::updateScene(dt); 
    if (playerRef) {
        camera.target.x += (playerRef->pos.x - camera.target.x) * 0.1f;
        camera.target.y += (playerRef->pos.y - camera.target.y) * 0.1f;
    }
    if (IsKeyPressed(KEY_ESCAPE)) SceneManager::LoadScene(new MenuScene());
}

#endif