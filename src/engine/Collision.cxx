#include "engine/Collision.h"
#include "engine/Mat.h"
#include <algorithm>
#include <cmath>

bool Collision::IsColliding(mat::Rect& a, mat::Rect& b, float angleOfA, float angleOfB) {
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