#ifndef __TEXT_H__
#define __TEXT_H__

#define INCLUDE_SDL
#define INCLUDE_SDL_TTF
#include "engine/SDL_include.h"
#include "engine/Component.h"
#include "engine/GameObject.h"
#include <string>

class Text : public Component {
    public:
        enum TextStyle {SOLID, SHADED, BLENDED};

    private:
        TTF_Font* font;
        SDL_Texture* texture;

        std::string text;
        TextStyle style;
        std::string fontFile;
        int fontSize;
        SDL_Color color;

        void RemakeTexture();

    public:
        Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color);
        ~Text();

        void Update(float dt) override;
        void Render() override;
        bool Is(std::string type) override;

        void SetText(std::string text);
        void SetColor(SDL_Color color);
        void SetStyle(TextStyle style);
        void SetFontFile(std::string fontFile);
        void SetFontSize(int fontSize);
};

#endif