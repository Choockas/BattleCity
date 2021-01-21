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
//      ResourceManager::getAnimateSprites("NewAnimatedSprite")->render();
//      ResourceManager::getSprites("NewSprite")->render();
    if(m_ptank){
    m_ptank->render();
    m_ptank->move(false);
    }
}

void Game::setkey(const int key, const int action)
{
    m_keys[key] = action;
}

void Game::update(uint64_t delta)
{
//     ResourceManager::getAnimateSprites("NewAnimatedSprite")->update(delta);
//     ResourceManager::getSprites("NewSprite");
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
    
}

bool Game::init()
{
    auto pDefaulShaderProgram = ResourceManager::loadShaders("Default Shader","res/shaders/vertex.txt","res/shaders/fragment.txt");
if(!pDefaulShaderProgram){
    std::cerr<< "Can't get managed resource"<<std::endl;
    
    return false;
}

auto pSpriteShaderProgram = ResourceManager::loadShaders("Sprite Shader","res/shaders/vsprite.txt","res/shaders/fsprite.txt");
if(!pSpriteShaderProgram){
    std::cerr<< "Can't get managed resource"<<std::endl;
    
    return false;
}


auto pTexture  = ResourceManager::loadTextures("DefaultTexture","res/textures/map_16x16.png");
if(!pTexture){
    std::cerr<< "Can't get managed textures"<<std::endl;
    
    return false;
}

std::vector<std::string> subTexturesNames ={"block",
                                            "topRightBlock",
                                            "topLeftBlock",
                                            "topBlock",
                                            "bottomRightBlock",
                                            "rightBlock",
                                            
                                            "bootomBlock",
                                            "leftBlock",
                                            "bottomLeftBlock",
                                            "topBeton",
                                            "bottomBeton",
                                            "leftBeton",                                            

                                            "rightBeton",
                                            "topLeftBeton",
                                            "topRightBeton",                                            
                                            "water1",
                                            "water2",
                                            "water3",
                                            
                                            "beton",
                                             "trees",
                                            "ice",
                                            "wall",
                                            "respawn1",
                                            "respawn2",

                                            "respawn3",
                                            "respawn4"                                            
                                            "bottomLeftBeton",
                                            "bottomRightBeton",
                                            "eagle",
                                            "deadEagle",
                                            "nothing"


                                            
};
                                            
auto pTextureAtlas = ResourceManager::loadTextureAtlas ( "DefaultTextureAtlas","res/textures/map_8x8.png",std::move(subTexturesNames),8,8);     

auto pSprite = ResourceManager::loadSprites("NewSprite", "DefaultTextureAtlas", "Sprite Shader",50,50,"beton");

pSprite->setPosition(glm::vec2(300,100));     


auto paniSprite = ResourceManager::loadAnimateSprites("NewAnimatedSprite", "DefaultTextureAtlas", "Sprite Shader",50,50,"beton");

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




std::vector<std::string> tanksSubTexturesNames ={
                                            "tankTop1",
                                            "tankTop2",
                                            "tankLeft1",
                                            "tankLeft2",
                                            "tankBottom1",
                                            "tankBottom2",
                                            "tankRight1",
                                            "tankRight2"                                            
                                             } ;
                                            
auto pTanksTextureAtlas = ResourceManager::loadTextureAtlas ( "TanksTextureAtlas","res/textures/tanks.png",std::move(tanksSubTexturesNames),16,16);                                             
auto pTankSprite = ResourceManager::loadAnimateSprites("TankAnimatedSprite", "TanksTextureAtlas", "Sprite Shader",50,50,"tankTop1");                                            

std::vector<std::pair<std::string, uint64_t>> tankTopState;
tankTopState.emplace_back(std::make_pair<std::string,uint64_t>("tankTop1",330000000));    
tankTopState.emplace_back(std::make_pair<std::string,uint64_t>("tankTop2",330000000));

std::vector<std::pair<std::string, uint64_t>> tankLeftState;
tankLeftState.emplace_back(std::make_pair<std::string,uint64_t>("tankLeft1",330000000));    
tankLeftState.emplace_back(std::make_pair<std::string,uint64_t>("tankLeft2",330000000));

std::vector<std::pair<std::string, uint64_t>> tankBottomState;
tankBottomState.emplace_back(std::make_pair<std::string,uint64_t>("tankBottom1",330000000));    
tankBottomState.emplace_back(std::make_pair<std::string,uint64_t>("tankBottom2",330000000));

std::vector<std::pair<std::string, uint64_t>> tankRightState;
tankRightState.emplace_back(std::make_pair<std::string,uint64_t>("tankRight1",330000000));    
tankRightState.emplace_back(std::make_pair<std::string,uint64_t>("tankRight2",330000000));

pTankSprite -> insertState("tankTopState",std::move(tankTopState));
pTankSprite -> insertState("tankLeftState",std::move(tankLeftState));
pTankSprite -> insertState("tankBottomState",std::move(tankBottomState));
pTankSprite -> insertState("tankRightState",std::move(tankRightState));

std::string anistate = "tankTopState";
pTankSprite->setState(anistate);

m_ptank = std::make_unique<Tank>(pTankSprite,0.0000001f,glm::vec2(150,150));

return true;
}
