#include "engine/Text.h"

Text::Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color) : Component(associated) {}

Text::~Text() {}

void Text::Update(float dt) {}

void Text::Render() {}

bool Text::Is(std::string type) { return type == "Text"; }

void Text::SetText(std::string text) {
    this->text = text;
}

void Text::SetColor(SDL_Color color) {
    this->color = color;
}

void Text::SetStyle(TextStyle style) {
    this->style = style;
}

void Text::SetFontFile(std::string fontFile) {
    this->fontFile = fontFile;
}

void Text::SetFontSize(int fontSize) {
    this->fontSize = fontSize;
}