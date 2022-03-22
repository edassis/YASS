#ifndef __GAME_H__
#define __GAME_H__

#include "engine/State.h"
#include <iostream>
#include <stack>
#include <memory>
#include <cmath>

#define NUM_CHANNELS 32
#define FRAME_DURATION 33   // ms
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 600

struct SDL_Window;
struct SDL_Renderer;

class Game {
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        
        std::unique_ptr<State> storedState;
        std::stack<std::unique_ptr<State>> stateStack;

        uint32_t frameStart;    // Last frame in ms.
        float dt;             // Delta in s.
        
        Game(std::string title = "Eduardo Ferreira de Assis - 17/0102289", int width = SCREEN_WIDTH, int height = SCREEN_HEIGHT);
        
        void CalculateDeltaTime();
        
    public:
        ~Game();

        Game(const Game&) = delete;
        Game(const Game&&) = delete;
        void operator=(const Game&) = delete;
        
        void Push(State* state);
        
        void Run();

        SDL_Renderer* GetRenderer();    // * SDL can fail making renderer be nullptr
        State* GetState();
        static Game& GetInstance();

        float GetDeltaTime();
};

#endif
