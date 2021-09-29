#include "application/Alien.h"
#include "application/Minion.h"
#include "engine/GameObject.h"
#include "engine/Sprite.h"
#include "engine/InputManager.h"
#include "engine/Game.h"
#include "engine/Mat.h"

Alien::Alien(GameObject& associated, int nMinion) : Component(associated) {
    this->hp = 30;
    this->nMinion = nMinion;

    auto* sprite = new Sprite(associated, "assets/img/alien.png");
    associated.AddComponent(*sprite);
}

Alien::~Alien() {} // ? Do I really need to manually free minionArray?

void Alien::Start() {
    // * Populate minionArray with "these objects" equally spaced.
    auto wpAlien = Game::GetState().GetObjectPtr(associated);
    if(wpAlien.lock() == nullptr) {
        std::cout << "Warning! Alien::Start() not found Alien pointer." << std::endl;
        return;
    }

    float arcStep = 360.0f / nMinion;
    float arc = 0.0f;
    for(int i = 0; i < nMinion; i++) {
        auto* pMinionGO = new GameObject();
        auto* pMinion = new Minion(*pMinionGO, wpAlien, arc);
        associated.AddComponent(*pMinion);
        auto wpMinionGO = Game::GetState().AddObject(*pMinionGO);
        minionArray.push_back(wpMinionGO);

        arc += arcStep;
    }
}

void Alien::Update(float dt) {
    auto& inputManager = InputManager::GetInstance();
    auto& camera = Game::GetState().GetCamera();
    
    mat::Vec2 clickPos(inputManager.GetMouseX(), inputManager.GetMouseY());
    clickPos += camera.GetPos();
    clickPos -= mat::Vec2(associated.box.w/2, associated.box.h/2);  // * Offsets mouse click to the box's center.

    if (inputManager.KeyPress(KEYS::LEFT_MOUSE_BUTTON)) {  // Shoot
        taskQueue.emplace(Action::SHOOT, clickPos.x, clickPos.y);
    }
    if (inputManager.KeyPress(KEYS::RIGHT_MOUSE_BUTTON)) {    // Move
        taskQueue.emplace(Action::MOVE, clickPos.x, clickPos.y);
    }

    if (taskQueue.size()) {
        auto& task = taskQueue.front();

        switch (task.type) {
            case task.MOVE:
            {   // Creates scope for local variables.
                const float maxSpeed = 12.0f;
                const float acc = 4.0f;
                // auto posI = associated.box.Center();
                auto posI = mat::Vec2(associated.box.x, associated.box.y);
                auto posdt = task.pos - posI;

                speed += posdt.Normalized() * acc * dt;
                speed.x = std::max(std::min(maxSpeed, speed.x), -maxSpeed);
                speed.y = std::max(std::min(maxSpeed, speed.y), -maxSpeed);
                
                auto posF = posI + speed;
                
                if (posI.DistanceTo(posF) >= posI.DistanceTo(task.pos)) {   // arrived
                    speed.x = speed.y = 0.0f;

                    associated.box.x = task.pos.x;
                    associated.box.y = task.pos.y;

                    taskQueue.pop();
                }
                else {  // add speed
                    associated.box.x += speed.x;
                    associated.box.y += speed.y; 
                }
                break;
            } 
            case task.SHOOT:
                // ! Temporary
                taskQueue.pop();
                break;
            default:
                break;
        }
    }

    if (hp <= 0) {
        associated.RequestDelete();
    }
}

void Alien::Render() {}

bool Alien::Is(std::string type) { return type == "Alien"; }

/* Inner class Action */
Alien::Action::Action(ActionType type, float x, float y) {
    this->type = type;
    this->pos = mat::Vec2(x, y);
}
