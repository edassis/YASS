#include "engine/Game.h"

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "engine/SDL_include.h"

using std::cout;
using std::endl;

// unique_ptr<Game> Game::instance = unique_ptr<Game> {};

Game::Game(string title, int width, int height) {
    int _error = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
    if(_error) {
        // Encerrar programa com mensagem de erro
        cout << "Failed to initialize SDL: " << SDL_GetError() << endl;
        throw 1; 
    }

    int _bitmask = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF); // é inicilizado automaticamente quando utilizado
    if(!_bitmask) {
        cout << "Failed to initialize IMG: " << IMG_GetError() << endl;
        throw 1;
    }

    _bitmask = Mix_Init(MIX_INIT_MP3); // é inicilizado automaticamente quando utilizado
    if(!_bitmask) {
        cout << "Failed to initialize Mix: " << Mix_GetError() << endl;
        throw 1;
    }

    _error = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);   // obrigatório
    if(_error) {
        cout << "Failed to open audio: " << Mix_GetError() << endl;
        throw 1;
    }

    int _channels = Mix_AllocateChannels(NUM_CHANNELS);   // quantas trilhas sonoras podem ser executadas simultaneamente
    if(_channels < NUM_CHANNELS) {
        cout << "Failed to allocate channels: " << Mix_GetError() << endl;
        throw 1;
    }

    SDL_Window *window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if(window == nullptr) {
        cout << "Failed to create window: " << SDL_GetError() << endl;
        throw 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr) {
        cout << "Failed to create render: " << SDL_GetError() << endl;
        throw 1;
    }

    this->window = window;
    this->renderer = renderer;
    this->state = unique_ptr<State> (new State());
    // this->state = new State();
}

Game::~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_CloseAudio();
    Mix_Quit();

    IMG_Quit();

    SDL_Quit();
}

// Game main loop
void Game::Run() {
    while(!state->QuitRequested()) {
        state->Update();
        state->Render();
        SDL_RenderPresent(renderer);

        SDL_Delay(FRAME_DURATION);
    }
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

State& Game::GetState() {
    return *state;
}


Game& Game::GetInstance() {
    static Game instance;
    return instance;
}
