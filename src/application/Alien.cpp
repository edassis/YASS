#include "application/Alien.h"
#include "application/Minion.h"
#include "engine/GameObject.h"
#include "engine/Sprite.h"
#include "engine/InputManager.h"
#include "engine/Game.h"
#include "engine/Mat.h"
#include "engine/Collider.h"

Alien::Alien(GameObject& associated, int nMinion) : Component(associated) {
    this->hp = 30;
    this->nMinion = nMinion;

    auto* rpSprite = new Sprite(associated, "assets/img/alien.png");
    auto* rpCollider = new Collider(associated);
    associated.AddComponent(*rpSprite);
    associated.AddComponent(*rpCollider);
}

Alien::~Alien() {}

void Alien::Start() {
    // * Populate minionArray with "these objects" equally spaced.
    auto wpAlien = Game::GetState().GetObjectPtr(associated);
    if(wpAlien.lock() == nullptr) {
        std::cout << "Warning! Alien::Start() not found Alien pointer." << std::endl;
        return;
    }

    float arcStep = 360.0f / float(nMinion);
    float arc = 0.0f;
    for(int i = 0; i < nMinion; i++) {
        auto* rpMinionGO = new GameObject();
        auto* rpMinion = new Minion(*rpMinionGO, wpAlien, arc);
        rpMinionGO->AddComponent(*rpMinion);
        auto wpMinionGO = Game::GetState().AddObject(*rpMinionGO);
        minionArray.push_back(wpMinionGO);

        arc += arcStep;
    }
}

void Alien::Update(float dt) {
    auto& inputManager = InputManager::GetInstance();
    auto& camera = Game::GetState().GetCamera();
    
    mat::Vec2 clickPos((float)inputManager.GetMouseX(), (float)inputManager.GetMouseY());
    clickPos += camera.GetPos();

    if (inputManager.KeyPress(KEYS::LEFT_MOUSE_BUTTON)) {  // Shoot
        taskQueue.emplace(Action::SHOOT, clickPos.x, clickPos.y);
    }
    if (inputManager.KeyPress(KEYS::RIGHT_MOUSE_BUTTON)) {    // Move
        taskQueue.emplace(Action::MOVE, clickPos.x, clickPos.y);
    }

    // * Process tasks.
    if (taskQueue.size()) {
        auto& task = taskQueue.front();

        switch (task.type) {
            case task.MOVE:
            {   // Creates scope for local variables.
                const float maxSpeed = 12.0f;
                const float acc = 4.0f;
                const auto boxOffset = mat::Vec2(associated.box.w/2, associated.box.h/2); // * Top left corner.
                
                auto posI = associated.box.GetPos(); 
                auto posF = task.pos - boxOffset;
                auto posDelta = posF - posI;

                speed += posDelta.Normalized() * acc * dt;
                speed.x = std::max(std::min(maxSpeed, speed.x), -maxSpeed);
                speed.y = std::max(std::min(maxSpeed, speed.y), -maxSpeed);
                
                auto nextPos = posI + speed;
                
                if (posI.DistanceTo(nextPos) >= posI.DistanceTo(posF)) {   // * Arrived
                    speed.x = speed.y = 0.0f;

                    associated.box.SetPos(posF);

                    taskQueue.pop();
                }
                else {  // add speed
                    associated.box.x += speed.x;
                    associated.box.y += speed.y; 
                }
                break;
            } 
            case task.SHOOT:
            {
                bool warning = false;
                
                float minDist = 1e6f;  // * 1 million of pixels is okay as max value I think.
                std::shared_ptr<Minion> spMinion;
                warning = true;
                for(auto& wpMinionGO : minionArray) {
                    if (auto spMinionGOCheck = wpMinionGO.lock()) {
                        auto newDist = spMinionGOCheck->box.Center().DistanceTo(task.pos);
                        if (minDist > newDist) {
                            minDist = newDist;
                            spMinion = std::dynamic_pointer_cast<Minion>(spMinionGOCheck->GetComponent("Minion").lock());
                            
                            warning = false;
                        }
                    } 

                    if (warning) {
                        std::cout << "Warning! Alien::Update() failed to retrieve Minion pointer.(1)" << std::endl;
                    }
                }

                if(spMinion) {
                    spMinion->Shoot(task.pos);
                } else {
                    std::cout << "Warning! Alien::Update() failed to retrieve Minion pointer.(2)" << std::endl;
                }
                
                taskQueue.pop();
                break;
            }
            default:
                break;
        }
    }

    // * Rotate Alien's Sprite
    auto angleStep = mat::Deg2Rad(-25.0f) * dt;
    associated.angle += angleStep;
    // if( auto spSprite = std::dynamic_pointer_cast<Sprite>(associated.GetComponent("Sprite").lock()) ) {
    //     spSprite->SetAngle(associated.angle);
    // } else {
    //     std::cout << "Warning! Alien::Update() couldn't find the Sprite's pointer." << std::endl;
    // }

    // * Dead.
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
