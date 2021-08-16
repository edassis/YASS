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