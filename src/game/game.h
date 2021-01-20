#pragma once
#include <stdio.h>
#include <memory>

class Game{

public:
Game();
~Game();

void render();
void update(uint64_t delta);
void setkey(const int key,const int action);



private:
    std::array<bool,349> m_keys;
    enum class GameSTATE {
        ACTIVE,
        PAUSE
    }; 

    GameSTATE m_currenState;
};
