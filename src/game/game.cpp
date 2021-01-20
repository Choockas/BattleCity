#include "game.h"


Game::Game() : m_currenState(GameSTATE::ACTIVE)
{
    m_keys.fill(false);
}

void Game::render()
{
    
}

void Game::setkey(const int key, const int action)
{
    m_keys[key] = action;
}

void Game::update(uint64_t delta)
{
    
}

Game::~Game()
{
    
}
