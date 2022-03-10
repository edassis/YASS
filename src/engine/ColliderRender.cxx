// Adicione o trecho abaixo no começo do seu Collider.cpp,
// logo após os seus includes e antes de qualquer função.
#ifdef DEBUG
#include "engine/SDL_include.h"
#include "engine/Game.h"
#include "engine/Mat.h"
#include "engine/Camera.h"
#endif // DEBUG

// Copie o conteúdo dessa função para dentro da sua e adapte o nome das funções para as suas.
// Funções usadas:
// Rect::GetCenter()				- Retorna um Vec2 no centro do Rect
// Vec2::operator-( const Vec2& )	- Subtrai dois Vec2
// Vec2::Rotate( float rad )		- Rotaciona um Vec2 pelo ângulo em radianos passado
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