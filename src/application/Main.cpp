// #define INCLUDE_SDL
// #define INCLUDE_SDL_IMAGE
// #define INCLUDE_SDL_MIXER
// #include "engine/SDL_include.h"
#include "engine/Game.h"

int main(int argc, char **argv) {
    Game myGame = Game::GetInstance();

    myGame.Run();

    return 0;
}