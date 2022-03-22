#include "engine/Game.h"
#include "engine/StageState.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

#define VNAME(x) #x
#define VDUMP(x) std::cout << #x << " " << x << std::endl

int main(int argc, char** argv) {
    srand( (unsigned)time(NULL) );
    
    Game& myGame = Game::GetInstance();
    myGame.Push(new StageState());
    myGame.Run();

    return 0;
}
