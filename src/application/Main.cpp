#include "engine/Game.h"
#include "engine/GameObject.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "engine/TileMap.h"
#include "engine/TileSet.h"

using std::cout;
using std::endl;

#define VNAME(x) #x
#define VDUMP(x) std::cout << #x << " " << x << std::endl

int main(int argc, char** argv) {
    srand( (unsigned)time(NULL) );

    Game& myGame = Game::GetInstance();

    myGame.GetState().LoadAssets();

    myGame.Run();

    return 0;
}