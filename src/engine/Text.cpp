#include "engine/Text.h"
#include "engine/Game.h"
#include "engine/Resources.h"
#include "engine/Camera.h"

Text::Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color) : Component(associated) {
    this->fontFile = fontFile;
    this->fontSize = fontSize;
    this->style = style;
    this->text = text;
    this->color = color;

    font = nullptr;
    texture = nullptr;
    
    RemakeTexture();
}

Text::~Text() {}

void Text::Update(float dt) {}

void Text::Render() {
    auto destPos = associated.box.GetPos() - Game::GetInstance().GetState()->GetCamera().GetPos();
    
    SDL_Rect clipRect {0, 0, (int)associated.box.w, (int)associated.box.h};
    SDL_Rect dstRect {(int)destPos.x, (int)destPos.y, (int)associated.box.w, (int)associated.box.h};
    
    int _error = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(),
            texture.get(), &clipRect, &dstRect, mat::Rad2Deg(associated.angle), nullptr, SDL_FLIP_NONE);
    if(_error) {
        std::cout << "Error! Text::Render() failed to render: " << SDL_GetError() << std::endl;
    }
}

bool Text::Is(std::string type) { return type == "Text"; }

void Text::SetText(std::string text) {
    this->text = text;
    RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
    this->color = color;
    RemakeTexture();
}

void Text::SetStyle(TextStyle style) {
    this->style = style;
    RemakeTexture();
}

void Text::SetFontFile(std::string fontFile) {
    this->fontFile = fontFile;
    RemakeTexture();
}

void Text::SetFontSize(int fontSize) {
    this->fontSize = fontSize;
    RemakeTexture();
}

void Text::RemakeTexture() {
    font = Resources::GetInstance().GetFont(fontFile, fontSize);

    SDL_Surface* surface = nullptr;
    SDL_Color bgColor = {0xff, 0xff, 0xff, 0xff};
    switch (style) {
        case SOLID:
            surface = TTF_RenderText_Solid(this->font.get(), this->text.c_str(), this->color);
            break;
        case SHADED:
            surface = TTF_RenderText_Shaded(this->font.get(), this->text.c_str(), this->color, bgColor);
            break;
        case BLENDED:
            surface = TTF_RenderText_Blended(this->font.get(), this->text.c_str(), this->color);
            break;
        default:
            std::cout << "Warning! Text() called with invalid TextStyle." << std::endl;
            break;
    }

    texture = { SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface), deleter_texture() };

    if(!texture) {
        std::cout << "Warning! Text() failed to create font's texture." << std::endl;
        return;
    }

    associated.box.w = (float)surface->w;
    associated.box.h = (float)surface->h;

    SDL_FreeSurface(surface);
}