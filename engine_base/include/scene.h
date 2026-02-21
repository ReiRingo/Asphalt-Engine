#ifndef SCENE_H
#define SCENE_H

#include "raylib.h"
#include "actor.h"
#include <vector>
#include <algorithm>

class Scene {
    protected:
    std::vector<Actor*> actors;
    std::vector<Actor*> actorsToAdd;

    public: 
    Vector2 sceneSize = {0, 0};
    Camera2D camera = { 0 };

    virtual ~Scene() {
        for (auto a : actors) { a->onEnd(); delete a; }
        actors.clear();
    }

    std::vector<Actor*>& getActors() { return actors; }

    virtual void onStart() = 0;
    
    // Marked virtual so children can add custom logic
    // I'm a genorous someone ok?
    virtual void updateScene(float dt) {
        for (Actor* actor : actorsToAdd) {
            actor->onCreate();
            actors.push_back(actor);
        }
        actorsToAdd.clear();

        for (Actor* actor : actors) {
            if (!actor->destroyed) actor->onUpdate(dt);
        }

        std::sort(actors.begin(), actors.end(), [](Actor* a, Actor* b) {
            return a->depth < b->depth; 
        });

        actors.erase(std::remove_if(actors.begin(), actors.end(), [](Actor* actor) {
            if (actor->destroyed) {
                actor->onDestroy();
                actor->onEnd();
                delete actor;
                return true;
            }
            return false;
        }), actors.end());
    }

    // Observation: Marked virtual to allow custom UI passes
    virtual void drawScene(float dt) {
        BeginMode2D(camera);
            for (Actor* actor : actors) {
                if (!actor->destroyed) actor->onDraw(dt);
            }
        EndMode2D();

        for (Actor* actor : actors) {
            if (!actor->destroyed) actor->onDrawUi(dt);
        }
    }

    void addActor(Actor* actor) {
        actorsToAdd.push_back(actor);
    }
};

#endif