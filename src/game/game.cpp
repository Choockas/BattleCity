#include "game.h"
#include "resourcesmanager.h"
#include "texture2D.h"
#include "shadeprogramm.h"
#include "sprite.h"
#include "animatesprite.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/mat4x2.hpp"
#include <iostream>
#include "tank.h"

#include <GLFW/glfw3.h>


Game::Game(const glm::ivec2 windowsize) : m_windowsize(windowsize),
                                          m_currenState(GameSTATE::ACTIVE)
{
    m_keys.fill(false);
}

void Game::render() 
{
     ResourceManager::getAnimateSprites("newanimatedsprite")->render();
     ResourceManager::getSprites("newsprite")->render();
    if(m_ptank){
    m_ptank->render();
    m_ptank->move(false);
    }
//     ResourceManager::getAnimateSprites("newanimatedsprite")->render();
}

void Game::setkey(const int key, const int action)
{
    m_keys[key] = action;
}

void Game::update(uint64_t delta)
{
    ResourceManager::getAnimateSprites("newanimatedsprite")->update(delta);
    ResourceManager::getSprites("newsprite");
    if(m_ptank){
        if(m_keys[GLFW_KEY_W]){
            m_ptank->setOrientation(Tank::EOrientation::TOP);
            m_ptank->move(true);
        }else if(m_keys[GLFW_KEY_A]){
            m_ptank->setOrientation(Tank::EOrientation::LEFT);
            m_ptank->move(true);
        }else if(m_keys[GLFW_KEY_D]){
            m_ptank->setOrientation(Tank::EOrientation::RIGHT);
            m_ptank->move(true);
        }else if(m_keys[GLFW_KEY_S]){
            m_ptank->setOrientation(Tank::EOrientation::BOTTOM);
            m_ptank->move(true);
        }
        else{
            m_ptank->move(false);
        }
        
    m_ptank->update(delta);
    }
}

Game::~Game()
{
    m_ptank.release();
}

bool Game::init()
{
    
    
 auto pDefaulShaderProgram = ResourceManager::loadShaders("defaultshader","res/shaders/vertex.txt","res/shaders/fragment.txt");

    
    ResourceManager::loadJSONResources("res/resources.json"); 
    
    auto pSpriteShaderProgram = ResourceManager::getShaderProgram("spriteShader");
    if (!pSpriteShaderProgram){
        std::cerr<<"Can't find shader programm " << "spriteShader" <<std::endl;
        return false;
    }

    
    auto pTextureAtlas = ResourceManager::getTextures("mapTextureAtlas");
    
    if (!pTextureAtlas){
        std::cerr<<"Can't get textures " << "mapTextureAtlas" <<std::endl;
        return false;
    }
    
    
//     auto pTextureAtlas = ResourceManager::loadTextureAtlas ( "defaulttextureAtlas","res/textures/map_8x8.png",std::move(subTexturesNames),8,8);  */   
    
    
    
    auto pSprite = ResourceManager::loadSprites("newsprite", "mapTextureAtlas", "spriteShader",50,50,"beton");
    if (!pSprite){
        std::cerr<<" Can' t find sprite "<<"newsprite"<<std::endl;
    }
    
    pSprite->setPosition(glm::vec2(300,100));     
    
    
    auto paniSprite = ResourceManager::loadAnimateSprites("newanimatedsprite", "mapTextureAtlas", "spriteShader",50,50,"beton");
    
    paniSprite -> setPosition(glm::vec2(300,300));
    
    std::vector<std::pair<std::string, uint64_t>> waterState;
    waterState.emplace_back(std::make_pair<std::string,uint64_t>("water1",1000000000) );    
    waterState.emplace_back(std::make_pair<std::string,uint64_t>("water2",1000000000));
    waterState.emplace_back(std::make_pair<std::string,uint64_t>("water3",1000000000));
    
    std::vector<std::pair<std::string, uint64_t>> eagleState;
    eagleState.emplace_back(std::make_pair<std::string,uint64_t>("eagle",1000000000) );    
    eagleState.emplace_back(std::make_pair<std::string,uint64_t>("deadEagle",1000000000));
    std::string anisprstate = "waterState";
    paniSprite -> insertState("waterState",std::move(waterState));
    paniSprite -> insertState("eagleState",std::move(eagleState));
    
    
    paniSprite->setState(anisprstate);
    
    //*********requaired to be active**************
     pDefaulShaderProgram->use(); 
     pDefaulShaderProgram->setInt("tex",0);
     
     glm::mat4 modeMatrix_1 = glm::mat4(1.0f);
     modeMatrix_1 = glm::translate(modeMatrix_1,glm::vec3(200.0f,50.0f,0.0f));
     
     glm::mat4 modeMatrix_2 = glm::mat4(1.0f);
     modeMatrix_2 = glm::translate(modeMatrix_2,glm::vec3(440.0f,50.0f,0.0f));
     
    glm::mat4 projectionMatrix = glm::ortho (0.0f, static_cast<float>(m_windowsize.x),0.0f,static_cast<float>( m_windowsize.y),-100.0f,100.0f);
    
    pDefaulShaderProgram->setMatrix4("projectionMat", projectionMatrix);
    
    pSpriteShaderProgram->use(); 
    pSpriteShaderProgram->setInt("tex",0);
    pSpriteShaderProgram -> setMatrix4("projectionMat", projectionMatrix);

    auto pTanksAnimatedSprite = ResourceManager::getAnimateSprites("tankAnimateSprite");
    if (!pTanksAnimatedSprite)
    {
        std::cerr<<"Can't find anamated sprite"<<std::endl;
        return false;
    }
    
    m_ptank = std::make_unique<Tank>(pTanksAnimatedSprite,0.0000001f,glm::vec2(150,150));
    
    if (!Game::m_ptank)
    {
        std::cerr<<"Can't create unique tank"<<std::endl;
        return false;
    }
//     
    
    return true;
}
