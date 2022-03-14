#include "application/Alien.h"
#include "application/Minion.h"
#include "engine/GameObject.h"
#include "engine/Sprite.h"
#include "engine/Sound.h"
#include "engine/InputManager.h"
#include "engine/Game.h"
#include "engine/Mat.h"
#include "engine/Collider.h"
#include "engine/Bullet.h"

int Alien::alienCount = 0;

Alien::Alien(GameObject& associated, int nMinion) : Component(associated) {
    alienCount++;
    this->state = RESTING;
    this->currentTime = 0.f;
    this->hp = 30;
    this->nMinion = nMinion;

    auto* rpSprite = new Sprite(associated, "assets/img/alien.png");
    auto* rpCollider = new Collider(associated);
    associated.AddComponent(*rpSprite);
    associated.AddComponent(*rpCollider);
}

Alien::~Alien() {
    alienCount--;
}

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
    restTimer.Update(dt);

    const auto curPos = associated.box.GetPos();

    switch (state) {
        case RESTING:
            // resting time finished, move to player
            if(restTimer.GetTime() - currentTime > 2.f) {
                if(auto spPlayer = Game::GetState().GetPlayerPointer().lock()) {
                    destination = spPlayer->box.Center();
                    state = MOVING;
                } else {
                    std::cout << "Warning! Alien::Update() not able to find player." << std::endl;
                }
            }
            break;
        case MOVING:
            // Arrived in destination
            if((curPos - destination).Length() < mat::EPS) {
                Shoot(dt);
                currentTime = restTimer.GetTime();
                state = RESTING;
            } else {
                // Move to destination
                Move(dt);
            }
            break;
        default:
            break;
    }

    // auto& inputManager = InputManager::GetInstance();
    // auto& camera = Game::GetState().GetCamera();
    
    // mat::Vec2 clickPos((float)inputManager.GetMouseX(), (float)inputManager.GetMouseY());
    // clickPos += camera.GetPos();

    // if (inputManager.KeyPress(KEYS::LEFT_MOUSE_BUTTON)) {  // Shoot
    //     taskQueue.emplace(Action::SHOOT, clickPos.x, clickPos.y);
    // }
    // if (inputManager.KeyPress(KEYS::RIGHT_MOUSE_BUTTON)) {    // Move
    //     taskQueue.emplace(Action::MOVE, clickPos.x, clickPos.y);
    // }

    // // * Process tasks.
    // if (taskQueue.size()) {
    //     auto& task = taskQueue.front();

    //     switch (task.type) {
    //         case task.MOVE:
    //         {   // Creates scope for local variables.
    //             const float maxSpeed = 12.0f;
    //             const float acc = 4.0f;
    //             const auto boxOffset = mat::Vec2(associated.box.w/2, associated.box.h/2); // * Top left corner.
                
    //             auto posI = associated.box.GetPos(); 
    //             auto posF = task.pos - boxOffset;
    //             auto posDelta = posF - posI;

    //             speed += posDelta.Normalized() * acc * dt;
    //             speed.x = std::max(std::min(maxSpeed, speed.x), -maxSpeed);
    //             speed.y = std::max(std::min(maxSpeed, speed.y), -maxSpeed);
                
    //             auto nextPos = posI + speed;
                
    //             if (posI.DistanceTo(nextPos) >= posI.DistanceTo(posF)) {   // * Arrived
    //                 speed.x = speed.y = 0.0f;

    //                 associated.box.SetPos(posF);

    //                 taskQueue.pop();
    //             }
    //             else {  // add speed
    //                 associated.box.x += speed.x;
    //                 associated.box.y += speed.y; 
    //             }
    //             break;
    //         } 
    //         case task.SHOOT:
    //         {
    //             break;  // !!!!!!!!
    //             bool warning = false;
                
    //             float minDist = 1e6f;  // * 1 million of pixels is okay as max value I think.
    //             std::shared_ptr<Minion> spMinion;
    //             warning = true;
    //             for(auto& wpMinionGO : minionArray) {
    //                 if (auto spMinionGOCheck = wpMinionGO.lock()) {
    //                     auto newDist = spMinionGOCheck->box.Center().DistanceTo(task.pos);
    //                     if (minDist > newDist) {
    //                         minDist = newDist;
    //                         spMinion = std::dynamic_pointer_cast<Minion>(spMinionGOCheck->GetComponent("Minion").lock());
                            
    //                         warning = false;
    //                     }
    //                 } 

    //                 if (warning) {
    //                     std::cout << "Warning! Alien::Update() failed to retrieve Minion pointer.(1)" << std::endl;
    //                 }
    //             }

    //             if(spMinion) {
    //                 spMinion->Shoot(task.pos);
    //             } else {
    //                 std::cout << "Warning! Alien::Update() failed to retrieve Minion pointer.(2)" << std::endl;
    //             }
                
    //             taskQueue.pop();
    //             break;
    //         }
    //         default:
    //             break;
    //     }
    // }

    // * Rotate Alien's Sprite
    auto angleStep = mat::Deg2Rad(-25.0f) * dt;
    associated.angle += angleStep;
    // if( auto spSprite = std::dynamic_pointer_cast<Sprite>(associated.GetComponent("Sprite").lock()) ) {
    //     spSprite->SetAngle(associated.angle);
    // } else {
    //     std::cout << "Warning! Alien::Update() couldn't find the Sprite's pointer." << std::endl;
    // }
}

void Alien::Shoot(float dt) {
    // Retrieve the closest minion from player. 
    std::shared_ptr<Minion> spMinion;
    float minDist = 1e6f;
    for(auto& wpMinionGO : minionArray) {
        if (auto spMinionGO = wpMinionGO.lock()) {
            auto newDist = spMinionGO->box.Center().DistanceTo(destination);
            if (minDist > newDist) {
                minDist = newDist;
                spMinion = std::dynamic_pointer_cast<Minion>(spMinionGO->GetComponent("Minion").lock());
            }
        } else {
            std::cout << "Warning! Alien::Update() failed to retrieve MinionGO pointer." << std::endl;
        }
    }

    if(spMinion) {
        spMinion->Shoot(destination);
    } else {
        std::cout << "Warning! Alien::Update() failed to retrieve Minion pointer." << std::endl;
    }
}

void Alien::Move(float dt) {
    const float maxSpeed = 12.0f;
    const float acc = 4.0f;
    
    const auto curPos = associated.box.GetPos();

    auto direction = destination - curPos;
    direction = direction.Normalized();

    speed += direction * acc * dt;
    speed.x = std::max(std::min(maxSpeed, speed.x), -maxSpeed);
    speed.y = std::max(std::min(maxSpeed, speed.y), -maxSpeed);
    
    auto nextPos = curPos + speed;
    
    if (curPos.DistanceTo(nextPos) >= curPos.DistanceTo(destination)) {   // * Arrived
        speed.x = speed.y = 0.0f;
        associated.box.SetPos(destination);
        nextPos = destination;
    }
    associated.box.SetPos(nextPos);
}

void Alien::Render() {}

bool Alien::Is(std::string type) { return type == "Alien"; }

// /* Inner class Action */
// Alien::Action::Action(ActionType type, float x, float y) {
//     this->type = type;
//     this->pos = mat::Vec2(x, y);
// }

void Alien::NotifyCollision(const GameObject& other) {
    auto spBullet = std::dynamic_pointer_cast<Bullet>(other.GetComponent("Bullet").lock());
    if(!spBullet || spBullet->IsTargetPlayer()) return;
    
    // Take damage
    hp -= spBullet->GetDamage();
    
    if (hp <= 0) {
        associated.RequestDelete();

        auto* rpSpriteGO = new GameObject();
        rpSpriteGO->AddComponent(*new Sprite(*rpSpriteGO, "assets/img/aliendeath.png", 4, 0.1f, 4*0.1f));
        auto* rpSpriteSound = new Sound(*rpSpriteGO, "assets/audio/boom.wav");
        rpSpriteGO->AddComponent(*rpSpriteSound);
        Game::GetState().AddObject(*rpSpriteGO);

        rpSpriteGO->box.Centralize(associated.box.Center());
        rpSpriteSound->Play();
    }
}
