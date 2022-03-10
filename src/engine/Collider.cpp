#include "engine/Collider.h"
#include "engine/Mat.h"
#include "engine/GameObject.h"
#include "engine/Game.h"

#ifdef DEBUG
    #define INCLUDE_SDL
    #include "engine/SDL_include.h"
    #include "engine/Camera.h"
#endif // DEBUG

Collider::Collider(GameObject& associated, mat::Vec2 scale, mat::Vec2 offset) : Component(associated) {
    this->scale = scale;
    this->offset = offset;
    this->box = associated.box;
}

Collider::~Collider() {}

void Collider::SetScale(mat::Vec2 scale) {
    this->scale = scale;
}

void Collider::SetOffset(mat::Vec2 offset) {
    this->offset = offset;
}

void Collider::Update(float dt) {
    box = associated.box;
    auto center = associated.box.Center();
    center += offset;
    float angle = 0.f;

    // ? Rotated by the angle of associated;
    if (auto spSprite = std::dynamic_pointer_cast<Sprite>(associated.GetComponent("Sprite").lock())) {
        angle = spSprite.GetAngle();
    }

    auto halfW = box.w/2 * scale.x;
    auto halfH = box.h/2 * scale.y;

    mat::Vec2 p1(-halfW, -halfH), p2(halfW, halfH); 
     
    // box.x = center.x - halfW;
    // box.y = center.y - halfH;
    // box.w = center.x + halfW;
    // box.h = center.y + halfH;

    // mat::Vec2 p1(box.x, box.y), p2(box.w, box.h); 

    p1 = p1.Rotated(angle);
    p1 += center;
    p2 = p2.Rotated(angle);
    p2 += center; 

    box.x = p1.x;
    box.y = p1.y;
    box.w = p2.x;
    box.h = p2.y; 
}

void Collider::Render() {
#ifdef DEBUG
	mat::Vec2 center( box.Center() );
	SDL_Point points[5];
	auto& camera = Game::GetState()::GetCamera();

	mat::Vec2 point = (mat::Vec2(box.x, box.y) - center).Rotated(associated.angleDeg/(180/mat::PI))
			+ center - camera.GetPos();
	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};
	
	point = (mat::Vec2(box.x + box.w, box.y) - center).Rotated(associated.angleDeg/(180/mat::PI))
			+ center - camera.GetPos();
	points[1] = {(int)point.x, (int)point.y};
	
	point = (mat::Vec2(box.x + box.w, box.y + box.h) - center).Rotated(associated.angleDeg/(180/mat::PI) )
			+ center - Camera::pos;
	points[2] = {(int)point.x, (int)point.y};
	
	point = (mat::Vec2(box.x, box.y + box.h) - center).Rotated(associated.angleDeg/(180/mat::PI))
			+ center - Camera::pos;
	points[3] = {(int)point.x, (int)point.y};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
}

bool Collider::Is(std::string type) { return type == "Collider"; }