#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include "engine/SDL_include.h"
#include "engine/Game.h"
#include "engine/InputManager.h"
#include "engine/Resources.h"

Game::Game(std::string title, int width, int height) {
    int _error = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
    if(_error) {
        // Encerrar programa com mensagem de erro
        std::cout << "Error! Game::Game() failed to initialize SDL: " << SDL_GetError() << std::endl;
        throw 1; 
    }

    int _bitmask = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF); // é inicilizado automaticamente quando utilizado
    if(!_bitmask) {
        std::cout << "Error! Game::Game() failed to initialize IMG: " << IMG_GetError() << std::endl;
        throw 1;
    }

    _bitmask = Mix_Init(MIX_INIT_MP3); // é inicilizado automaticamente quando utilizado
    if(!_bitmask) {
        std::cout << "Error! Game::Game() failed to initialize Mix: " << Mix_GetError() << std::endl;
        throw 1;
    }

    _error = TTF_Init();
    if(_error) {
        std::cout << "Error! Game::Game() failed to initialize TTF: " << TTF_GetError() << std::endl;
        throw 1;
    }

    _error = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);   // obrigatório
    if(_error) {
        std::cout << "Error! Game::Game() failed to open audio: " << Mix_GetError() << std::endl;
        throw 1;
    }

    int _channels = Mix_AllocateChannels(NUM_CHANNELS);   // quantas trilhas sonoras podem ser executadas simultaneamente
    if(_channels < NUM_CHANNELS) {
        std::cout << "Error! Game::Game() failed to allocate channels: " << Mix_GetError() << std::endl;
        throw 1;
    }

    SDL_Window* window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if(window == nullptr) {
        std::cout << "Error! Game::Game() failed to create window: " << SDL_GetError() << std::endl;
        throw 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr) {
        std::cout << "Error! Game::Game() failed to create render: " << SDL_GetError() << std::endl;
        throw 1;
    }

    this->window = window;
    this->renderer = renderer;
    this->storedState = nullptr;
    // this->state = unique_ptr<State> (new State());  // * Infinite loop

    frameStart = SDL_GetTicks();
    dt = 0.0F; 
}

Game::~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();

    SDL_CloseAudio();
    Mix_Quit();

    IMG_Quit();

    SDL_Quit();
}

// Game main loop
void Game::Run() {
    if(!storedState) {
        std::cout << "Error! Initial state not defined." << std::endl;
        return;
    }
    stateStack.push(std::move(storedState));
    GetState()->Start();

    while(true) {
        if(GetState()->QuitRequested()) {
            stateStack.pop();
            Resources::GetInstance().ClearImages();
            Resources::GetInstance().ClearMusics();
            Resources::GetInstance().ClearSounds();
            
            if(GetState()) {
                GetState()->Resume();
            }
        }

        if(storedState) {
            GetState()->Pause();
            stateStack.push(std::move(storedState));
            GetState()->Start();
        }
        
        if(!GetState()) break;

        CalculateDeltaTime();

        InputManager::GetInstance().Update();

        GetState()->Update(dt);
        GetState()->Render();
        SDL_RenderPresent(renderer);

        SDL_Delay(FRAME_DURATION);
    }
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

State* Game::GetState() {
    if(stateStack.empty()) {
        return nullptr;
    }

    return stateStack.top().get();
}

void Game::Push(State* state) {
    if(!state) {
        std::cout << "Warning! Game::Push() called with state = null." << std::endl;
        return;
    }

    storedState = std::unique_ptr<State>(state);
}

Game& Game::GetInstance() {
    static Game instance;
    return instance;
}

float Game::GetDeltaTime() { return dt; }

void Game::CalculateDeltaTime() {
    uint32_t fCurrent = SDL_GetTicks();

    uint32_t delta = fCurrent - frameStart;

    if(fCurrent < frameStart) { // ticks was wrapped
        delta = fCurrent;
        delta += UINT32_MAX - frameStart;
    }

    dt = (float)delta/1000;
    frameStart = fCurrent;
}
