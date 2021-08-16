#ifndef __GAME_H__
#define __GAME_H__

#include "engine/State.h"
#include <iostream>

#define NUM_CHANNELS 32
#define FRAME_DURATION 33   // ms

using std::string;

class SDL_Window;
class SDL_Renderer;

class Game {
    private:
        static Game *instance;
        SDL_Window *window;
        SDL_Renderer *renderer;
        State *state;

        Game(string title = "Eduardo Ferreira de Assis - 17/0102289", int width = 1024, int height = 600);
    public:
        ~Game();

        void Run();
        SDL_Renderer* GetRenderer();
        State& GetState();
        static Game& GetInstance();
};

#endif