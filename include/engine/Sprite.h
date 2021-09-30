#ifndef __SPRITE_H__
#define __SPRITE_H__

#define INCLUDE_SDL
#include "engine/SDL_include.h"
#include "engine/Component.h"
#include "engine/Mat.h"
#include <iostream>

class Sprite : public Component {
    private:
        int width;
        int height;
        mat::Vec2 scale;
        double angleDeg;    // degrees

        SDL_Texture* texture;
        SDL_Rect clipRect;

    public:
        Sprite(GameObject& associated);
        Sprite(GameObject& associated, std::string file);
        ~Sprite();

        void Open(std::string file);

        int GetWidth();
        int GetHeight();
        mat::Vec2 GetScale();
        double GetAngle();

        void SetScale(mat::Vec2& v);
        void SetScale(float x, float y);
        void SetAngle(const double& deg);
        void SetClip(int x, int y, int w, int h);
        bool IsOpen();

        void Render(float x, float y, float w, float h);

        /* Component */
        void Update(float dt) override;
        void Render() override;
        bool Is(std::string type) override;
};

#endif