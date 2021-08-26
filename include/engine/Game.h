#ifndef __GAME_H__
#define __GAME_H__

#include "engine/State.h"
#include <iostream>
#include <memory>

#define NUM_CHANNELS 32
#define FRAME_DURATION 33   // ms

using std::string;
using std::unique_ptr;

class SDL_Window;
class SDL_Renderer;

class Game {
    private:
        // static unique_ptr<Game> instance;
        SDL_Window *window;
        SDL_Renderer *renderer;
        unique_ptr<State> state;
        // State *state;

        Game(string title = "Eduardo Ferreira de Assis - 17/0102289", int width = 1024, int height = 600);
        // Game();
        // Game(const Game&) = delete;
        // Game& operator=(const Game&) = delete;
    public:
        ~Game();

        void Run();
        SDL_Renderer* GetRenderer();
        State& GetState();
        static Game& GetInstance();
};

#endif