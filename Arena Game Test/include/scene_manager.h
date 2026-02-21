#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "scene.h"

class SceneManager {
    private:
    static Scene* currentScene;
    static Scene* nextScene;

    public:
    // Call this to queue a transition
    static void LoadScene(Scene* scene) {
        nextScene = scene;
    }

    static Scene* GetCurrentScene() { return currentScene; }

    // Call this at the very start of your Main Loop
    static void Update() {
        // 1. Check for transition
        if (nextScene != nullptr) {
            if (currentScene != nullptr) {
                // TODO: Make onEnd
                delete currentScene; 
            }
            
            currentScene = nextScene;
            currentScene->onStart(); // Initialize the new scene
            nextScene = nullptr;     // Reset the queue
        }

        // 2. Update the active scene
        if (currentScene != nullptr) {
            currentScene->updateScene(GetFrameTime());
        }
    }

    // Call this in your Main Loop's drawing phase
    static void Draw() {
        if (currentScene != nullptr) {
            currentScene->drawScene(GetFrameTime());
        }
    }
    
    // Clean up when the game closes
    static void Unload() {
        if (currentScene != nullptr) delete currentScene;
    }
};

// Initialize static members
Scene* SceneManager::currentScene = nullptr;
Scene* SceneManager::nextScene = nullptr;

#endif