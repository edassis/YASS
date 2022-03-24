#ifndef __TEXT_H__
#define __TEXT_H__

#define INCLUDE_SDL
#define INCLUDE_SDL_TTF
#include "engine/SDL_include.h"
#include "engine/Component.h"
#include "engine/GameObject.h"
#include <string>
#include <memory>

struct deleter_texture {
    void operator()(SDL_Texture* texture) {
        SDL_DestroyTexture(texture);
    }
};

// template <typename D, D fn>
// struct deleter_from_fn {
//     template <typename T>
//     constexpr void operator()(T* arg) const {
//         fn(arg);
//     }
// };

// template <typename T, typename D, D fn>
// using my_unique_ptr = std::unique_ptr<T, deleter_from_fn<D, fn>>;

// // usage:
// my_unique_ptr<Bar, decltype(&destroy), destroy> p{create()};

class Text : public Component {
    public:
        enum TextStyle {SOLID, SHADED, BLENDED};

    private:
        std::shared_ptr<TTF_Font> font;
        std::unique_ptr<SDL_Texture, deleter_texture> texture;

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