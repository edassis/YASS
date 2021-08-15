// #define INCLUDE_SDL
// #define INCLUDE_SDL_IMAGE
// #define INCLUDE_SDL_MIXER
// #include "engine/SDL_include.h"
#include "engine/Game.h"
#include <iostream>
#include "unistd.h"

using std::cout;
using std::endl;

int main(int argc, char **argv) {
    Game myGame = Game::GetInstance();

    myGame.GetState().LoadAssets();

    myGame.Run();

    sleep(1);

    return 0;
}