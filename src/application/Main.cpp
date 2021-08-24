#include "engine/Game.h"
#include "engine/GameObject.h"
#include <iostream>
#include <memory>
#include "unistd.h"

using std::cout;
using std::endl;

#define VNAME(x) #x
#define VDUMP(x) std::cout << #x << " " << x << std::endl

int main(int argc, char **argv) {
    // Game myGame = Game::GetInstance();

    // myGame.GetState().LoadAssets();

    // myGame.Run();

    // GameObject go();
    std::unique_ptr<GameObject> go(new GameObject());
    Sprite spt(*go);
    
    cout << (spt.Is("Sprite") ? "true" : "false") << endl;

    getchar();
    
    return 0;
}

// TODO: 
// - Use unique_ptrs instead of pure pointers in `GameObject`;
// - Implement auxiliar math functions;
// - Adjust `State` functions;
// - Test `Component::Is()`;
// - Implement `Is`;