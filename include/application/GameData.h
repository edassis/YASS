#ifndef __GAMEDATA_H__
#define __GAMEDATA_H__

class GameData {
private:
    GameData() {
        playerVictory = false;
    }

public:
    ~GameData() {}

    static GameData& GetInstance() {
        static GameData rsc;
        return rsc;
    }

    bool playerVictory;
};

#endif