#include "engine/CameraFollower.h"
#include "engine/Game.h"
#include "engine/GameObject.h"

CameraFollower::CameraFollower(GameObject& go) : Component(go) {}

CameraFollower::~CameraFollower() {}

void CameraFollower::Update(float dt) {}

void CameraFollower::Render() {
    const auto& cameraPos = Game::GetState().GetCamera().pos;

    associated.box.x = cameraPos.x;
    associated.box.y = cameraPos.y;
}

bool CameraFollower::Is(std::string type) { return type == "CameraFollower"; }