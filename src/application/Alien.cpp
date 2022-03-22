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
    auto wpAlien = Game::GetInstance().GetState()->GetObjectPtr(associated);
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
        auto wpMinionGO = Game::GetInstance().GetState()->AddObject(*rpMinionGO);
        minionArray.push_back(wpMinionGO);

        arc += arcStep;
    }
}

void Alien::Update(float dt) {
    restTimer.Update(dt);

    const auto curPos = associated.box.GetPos();

    auto spPlayer = Game::GetInstance().GetState()->GetPlayerPointer().lock();
    if(!spPlayer) {
        std::cout << "Warning! Alien::Update() not able to find player." << std::endl;
        return;
    }

    switch (state) {
        case RESTING:
            // resting time finished, move to player
            if(restTimer.GetTime() - currentTime > 2.f) {
                destination = spPlayer->box.GetPos();
                state = MOVING;
            }
            break;
        case MOVING:
            Move(dt);
            // Arrived in destination
            if((curPos - destination).Length() < mat::EPS) {
                Shoot(dt);
                currentTime = restTimer.GetTime();
                state = RESTING;
            }
            break;
        default:
            break;
    }

    // * Rotate Alien's Sprite
    auto angleStep = mat::Deg2Rad(-25.0f) * dt;
    associated.angle += angleStep;
}

void Alien::Shoot(float dt) {
    std::shared_ptr<Minion> spMinion;
    std::shared_ptr<GameObject> spPlayer;
    
    spPlayer = Game::GetInstance().GetState()->GetPlayerPointer().lock();
    if(!spPlayer) {
        std::cout << "Warning! Alien::Shoot() failed to retrieve Player pointer." << std::endl;
        return;
    }

    auto target = spPlayer->box.Center();

    float minDist = 1e6f;
    // Retrieve the closest minion from player. 
    for(auto& wpMinionGO : minionArray) {
        if (auto spMinionGO = wpMinionGO.lock()) {
            auto minionDist = spMinionGO->box.Center().DistanceTo(target);
            if (minDist > minionDist) {
                minDist = minionDist;
                spMinion = std::dynamic_pointer_cast<Minion>(spMinionGO->GetComponent("Minion").lock());
            }
        } else {
            std::cout << "Warning! Alien::Shoot() failed to retrieve MinionGO pointer." << std::endl;
        }
    }

    if(spMinion) {
        spMinion->Shoot(target);
    } else {
        std::cout << "Warning! Alien::Shoot() failed to retrieve Minion pointer." << std::endl;
    }
}

void Alien::Move(float dt) {
    const float maxSpeed = 12.0f;
    const float acc = 4.0f;
    
    const auto curPos = associated.box.GetPos();

    if((destination - curPos).Length() < mat::EPS) {
        // Already in destination
        return;
    }

    auto direction = (destination - curPos).Normalized();

    speed += direction * acc * dt;

    if(speed.Length() > maxSpeed) {
        speed = speed.Normalized() * maxSpeed;
    }
   
    auto nextPos = curPos + speed;
    // std::cout << "direction: " << direction.x << ' ' << direction.y << std::endl;
    // std::cout << "speed: " << speed.x << ' ' << speed.y << std::endl;
    // std::cout << "curPos: " << curPos.x << ' ' << curPos.y << std::endl;
    // std::cout << "nextPos: " << nextPos.x << ' ' << nextPos.y << std::endl;
    // std::cout << "destination: " << destination.x << ' ' << destination.y << std::endl;
    
    if (curPos.DistanceTo(destination) < curPos.DistanceTo(nextPos)) {   // * Arrived
        speed.x = speed.y = 0.0f;
        nextPos = destination;
    }
    associated.box.SetPos(nextPos);
}

void Alien::Render() {}

bool Alien::Is(std::string type) { return type == "Alien"; }

void Alien::NotifyCollision(const GameObject& other) {
    auto spBullet = std::dynamic_pointer_cast<Bullet>(other.GetComponent("Bullet").lock());
    if(!spBullet || spBullet->IsTargetPlayer()) return;
    
    // Take damage
    hp -= spBullet->GetDamage();
    
    if (hp <= 0) {
        associated.RequestDelete();

        // Explosion animation
        auto* rpSpriteGO = new GameObject();
        rpSpriteGO->AddComponent(*new Sprite(*rpSpriteGO, "assets/img/aliendeath.png", 4, 0.1f, 4*0.1f));
        auto* rpSpriteSound = new Sound(*rpSpriteGO, "assets/audio/boom.wav");
        rpSpriteGO->AddComponent(*rpSpriteSound);
        rpSpriteGO->box.Centralize(associated.box.Center());
        rpSpriteSound->Play();
        Game::GetInstance().GetState()->AddObject(*rpSpriteGO);
    }
}
