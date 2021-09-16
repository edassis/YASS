#include "engine/Camera.h"

#include "engine/Game.h"
#include "engine/GameObject.h"
#include "engine/InputManager.h"

Camera::Camera() {
    // focus = nullptr;
}

Camera::~Camera() {}

void Camera::Follow(GameObject& newFocus) {
    // if (newFocus == nullptr) {
    //     std::cout << "Error! Camera::Follow() received nullptr from newFocus." << std::endl;
    //     return;
    // }

    pos = mat::Vec2(newFocus.box.x, newFocus.box.y);
    focus = std::make_shared<GameObject>(newFocus);
}

void Camera::Unfollow() {
    pos = mat::Vec2();
    focus = nullptr;
}

void Camera::Update(float dt) {
    mat::Rect screenArea(0.0f, 0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);

    if (focus) {    // Camera attached to some GameObject
        auto objCenter = focus->box.Center();
        auto screenCenter = screenArea.Center();

        pos = mat::Vec2( -(screenCenter.x - objCenter.x), -(screenCenter.y - objCenter.y) ); 
    }
    else {  // Camera on free mode
        const float velocity = 120.0f;

        if (InputManager::GetInstance().IsKeyDown(KEYS::UP_ARROW_KEY)) {
            pos.y -= velocity * dt;
        }
        else if (InputManager::GetInstance().IsKeyDown(KEYS::LEFT_ARROW_KEY)) {
            pos.x -= velocity * dt;
        }
        else if (InputManager::GetInstance().IsKeyDown(KEYS::DOWN_ARROW_KEY)) {
            pos.y += velocity * dt;
        }
        else if (InputManager::GetInstance().IsKeyDown(KEYS::RIGHT_ARROW_KEY)) {
            pos.x += velocity * dt;
        }
    }
}