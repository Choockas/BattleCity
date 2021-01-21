#pragma once
#include <stdio.h>
#include <memory>
#include "glm/vec2.hpp"

class Tank;

class Game{

public:
Game(const glm::ivec2 windowsize);
~Game();

void render();
void update(uint64_t delta);
void setkey(const int key,const int action);
bool init();


private:
    std::array<bool,349> m_keys;
    enum class GameSTATE {
        ACTIVE,
        PAUSE
    }; 
    glm::ivec2 m_windowsize;
    GameSTATE m_currenState;
    std::unique_ptr<Tank> m_ptank;
};
