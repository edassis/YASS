#ifndef __GAME_H__
#define __GAME_H__

#include <iostream>

#define MIX_CHANNELS 32
#define FRAME_DURATION 33   // ms

using std::string;

class State;
class SDL_Window;
class SDL_Renderer;

class Game {
    private:
        static Game *instance;
        SDL_Window *window;
        SDL_Renderer *renderer;
        State *state;

        Game(string title = "Eduardo Ferreira de Assis - 170102289", int width = 1024, int height = 600);
    public:
        ~Game();

        void Run();
        SDL_Renderer* GetRenderer();
        State& GetState();
        static Game& GetInstance();
};

#endif