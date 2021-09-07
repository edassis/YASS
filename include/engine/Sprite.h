#ifndef __SPRITE_H__
#define __SPRITE_H__

#define INCLUDE_SDL
#include "engine/SDL_include.h"
#include "engine/Component.h"
#include <iostream>

class Sprite : public Component {
    private:
        int width;
        int height;
        SDL_Texture* texture;
        SDL_Rect clipRect;
    public:
        Sprite(GameObject& associated);
        Sprite(GameObject& associated, std::string file);
        ~Sprite();

        void Open(std::string file);
        void SetClip(int x, int y, int w, int h);
        int GetWidth();
        int GetHeight();
        bool IsOpen();

        void Render(float x, float y, float w, float h);

        /* Component */
        void Update(float dt) override;
        void Render() override;
        bool Is(std::string type) override;
};

#endif