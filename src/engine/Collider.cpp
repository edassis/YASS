#include "engine/Collider.h"
#include "engine/Mat.h"
#include "engine/GameObject.h"
#include "engine/Game.h"
#include <algorithm>

#ifdef DEBUG
    #define INCLUDE_SDL
    #include "engine/SDL_include.h"
    #include "engine/Camera.h"
#endif // DEBUG

Collider::Collider(GameObject& associated, mat::Vec2 scale, mat::Vec2 offset) : Component(associated) {
    this->scale = scale;
    this->offset = offset;
    this->box = associated.box;
    // this->angle = 0.f;
}

Collider::~Collider() {}

void Collider::SetScale(mat::Vec2 scale) {
    this->scale = scale;
}

void Collider::SetOffset(mat::Vec2 offset) {
    this->offset = offset;
}

// void Collider::SetAngle(float angle) {
//     this->angle = angle;
// }

// void Collider::GetAngle() {
//     return angle;
// }

void Collider::Update(float dt) {
    box = associated.box;
    auto center = associated.box.Center();
    center += offset;

    box.Centralize(center);

    // // ? Rotated by the angle of associated;
    // // * GameObject.box not rotates, just Sprite.
    // if (auto spSprite = std::dynamic_pointer_cast<Sprite>(associated.GetComponent("Sprite").lock())) {
    //     angle = spSprite.GetAngle();
    // }

    // auto halfW = box.w/2 * scale.x;
    // auto halfH = box.h/2 * scale.y;

    // mat::Vec2 p1(-halfW, -halfH), p2(halfW, halfH); 
     
    // box.x = center.x - halfW;
    // box.y = center.y - halfH;
    // box.w = center.x + halfW;
    // box.h = center.y + halfH;

    // mat::Vec2 p1(box.x, box.y), p2(box.w, box.h); 

    // * Box uses w,h and I cannot rotate these values
    // p1 = p1.Rotated(angle);
    // p1 += center;
    // p2 = p2.Rotated(angle);
    // p2 += center; 

    // box.x = p1.x;
    // box.y = p1.y;
    // box.w = p2.x;
    // box.h = p2.y; 
}

void Collider::Render() {
#ifdef DEBUG
	mat::Vec2 center( box.Center() );
	SDL_Point points[5];
	auto& camera = Game::GetState().GetCamera();

	mat::Vec2 point = (mat::Vec2(box.x, box.y) - center).Rotated(associated.angle)
			+ center - camera.GetPos();
	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};
	
	point = (mat::Vec2(box.x + box.w, box.y) - center).Rotated(associated.angle)
			+ center - camera.GetPos();
	points[1] = {(int)point.x, (int)point.y};
	
	point = (mat::Vec2(box.x + box.w, box.y + box.h) - center).Rotated(associated.angle)
			+ center - camera.GetPos();
	points[2] = {(int)point.x, (int)point.y};
	
	point = (mat::Vec2(box.x, box.y + box.h) - center).Rotated(associated.angle)
			+ center - camera.GetPos();
	points[3] = {(int)point.x, (int)point.y};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
}

bool Collider::Is(std::string type) { return type == "Collider"; }

bool Collider::IsColliding(const mat::Rect& otherBox, const float& otherAngle) const {
    return IsColliding(box, otherBox, associated.angle, otherAngle);
}

bool Collider::IsColliding(const mat::Rect& a, const mat::Rect& b, const float& angleOfA, const float& angleOfB) {
	mat::Vec2 A[] = { 
		mat::Vec2( a.x, a.y + a.h ),
		mat::Vec2( a.x + a.w, a.y + a.h ),
		mat::Vec2( a.x + a.w, a.y ),
		mat::Vec2( a.x, a.y )
	};
	
	mat::Vec2 B[] = { 
		mat::Vec2( b.x, b.y + b.h ),
		mat::Vec2( b.x + b.w, b.y + b.h ),
		mat::Vec2( b.x + b.w, b.y ),
		mat::Vec2( b.x, b.y )
	};

	for(auto& v : A) {
		v = mat::Rotate(v - a.Center(), angleOfA) + a.Center();
	}

	for(auto& v : B) {
		v = mat::Rotate(v - b.Center(), angleOfB) + b.Center();
	}

	mat::Vec2 axes[] = { 	
		mat::Normalize(A[0] - A[1]), 
		mat::Normalize(A[1] - A[2]), 
		mat::Normalize(B[0] - B[1]), 
		mat::Normalize(B[1] - B[2]) 
	};

	for(auto& axis : axes) {
		float P[4];

		for (int i = 0; i < 4; ++i) P[i] = mat::Vec2::Dot(A[i], axis);

		float minA = *std::min_element(P, P + 4);
		float maxA = *std::max_element(P, P + 4);

		for (int i = 0; i < 4; ++i) P[i] = mat::Vec2::Dot(B[i], axis);

		float minB = *std::min_element(P, P + 4);
		float maxB = *std::max_element(P, P + 4);

		if (maxA < minB || minA > maxB)
			return false;
	}

	return true;
}