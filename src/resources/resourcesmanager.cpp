
#include "texture2D.h"
#include "shadeprogramm.h"
#include "sprite.h"
#include "animatesprite.h"
#include "resourcesmanager.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include "rapidjson/document.h"
#include "rapidjson/error/en.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"




std::string ResourceManager::m_path;
   
ResourceManager::ShaderProgramsMap ResourceManager::m_shaderPrograms;
ResourceManager::Texture2DMap  ResourceManager::m_texture2D;
ResourceManager::SpriteMap ResourceManager::m_sprites;
ResourceManager::AniSpriteMap ResourceManager::m_anisprites;


void ResourceManager::setExecutablePath(const std::string& executablePath)
{
    size_t found= executablePath.find_last_of("/\\");
    m_path = executablePath.substr(0,found);
}

void ResourceManager::unloadAllResources()
{
    m_shaderPrograms.clear();
    m_texture2D.clear();
    m_sprites.clear();
    m_anisprites.clear();
}



std::string ResourceManager::getFileString(const std::string& relativePath)
{
    std::ifstream f;
    f.open(m_path+"/"+relativePath,std::ios::in | std::ios::binary);
    if (!f.is_open())
    {
        std::cerr<<"Failed to open "<< relativePath<<std::endl;
        return std::string();
    }
    std::stringstream buffer;
    buffer<<f.rdbuf();
    std::cout<< "getting string from "<< relativePath<<std::endl;
    return buffer.str();
}

std::shared_ptr<RenderEngine::ShaderProgramm> ResourceManager::loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string vertexString = getFileString(vertexPath);
    if (vertexString.empty()){
        std::cerr<<"No vertex shader!"<< std::endl;
    }
    std::string fragmentString = getFileString(fragmentPath);
    if (fragmentString.empty()){
        std::cerr<<"No fragment shader!"<< std::endl;
    }
    
    std::shared_ptr<RenderEngine::ShaderProgramm>& newShader = m_shaderPrograms.emplace(shaderName, std::make_shared<RenderEngine::ShaderProgramm>(vertexString,fragmentString)).first->second;
    if (!newShader->isCompiled()){
        std::cerr<< "Can't load shader program:"<<"\n"
        <<"Vertex: " << vertexPath<< "\n" 
        <<"Fragment: " <<fragmentPath
        <<std::endl;
        return nullptr;
    }
    std::cout<<"shader programm " <<shaderName << " loaded right"<<std::endl;
    return newShader;
    
}

std::shared_ptr<RenderEngine::ShaderProgramm> ResourceManager::getShaderProgram(const std::string& shaderName)
{
    ShaderProgramsMap::const_iterator it=m_shaderPrograms.find(shaderName);
    if(it!=m_shaderPrograms.end()){
        return it->second;
    }
    std::cerr<<"Can't find the shader program"
    <<shaderName
    <<std::endl;
    return nullptr;
}

void ResourceManager::loadTexture(const std::string& textureName, const std::string& texturePath)
{
    int chanels = 0;
    int width = 0;
    int high = 0;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* pixels =stbi_load(std::string(m_path+"/"+texturePath ).c_str(),&width,&high,&chanels,0);
    std::cout<<""<<m_path<<std::endl;
    if(!pixels){
        std::cerr<<"Can't load image "<<texturePath<< ", name: " <<textureName <<std::endl;
        return;
    }
    
    stbi_image_free(pixels);
}

std::shared_ptr<RenderEngine::Texture2D> ResourceManager::loadTextures(const std::string& textureName, const std::string& texturePath)
{
    int chanels = 0;
    int width = 0;
    int hight = 0;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* pixels =stbi_load(std::string(m_path+"/"+texturePath ).c_str(),&width,&hight,&chanels,0);
    std::cout<<"textureName: "<< textureName<<std::endl;
    if(!pixels){
        std::cerr<<"Can't load image "<<texturePath<<std::endl;
        return nullptr;
    }
    
    std::cout << "loaded image: " << texturePath<<"\t" << "width:"<< width<<"\t"<<"higth:" << hight<<std::endl; 
    std::shared_ptr<RenderEngine::Texture2D>& newTexture =
    m_texture2D.emplace(textureName,
                        std::make_shared<RenderEngine::Texture2D>(width,
                                                              hight,
                                                              pixels,
                                                              chanels,
                                                              GL_NEAREST,
                                                              GL_CLAMP_TO_EDGE )).first->second;
    stbi_image_free(pixels);                                                               
    return newTexture;
}

std::shared_ptr<RenderEngine::Texture2D> ResourceManager::getTextures(const std::string& textureName)
{
    Texture2DMap::const_iterator it=m_texture2D.find(textureName);
    if(it!=m_texture2D.end()){
        return it->second;
    }
    std::cerr<<"Can't find texture"
    <<textureName
    <<std::endl;
    return nullptr;
}

std::shared_ptr<RenderEngine::Sprite> ResourceManager::loadSprites(const std::string& spriteName,
                                                               const std::string& textureName,
                                                               const std::string& shaderName,
                                                               const unsigned int spriteWidth,
                                                               const unsigned int spriteHight,
                                                               const std::string& subtextureName )
{
    
    auto pTexture  = getTextures(textureName);
    if(!pTexture){
        std::cerr<< "Can't get textures "<<"for the sprite:"<<spriteName<<std::endl;
        //glfwTerminate();
        return nullptr;
    }
    
    auto pShader = getShaderProgram(shaderName);
    if(!pShader){
        std::cerr<< "Can't get shader "<<"for the sprite:"<<spriteName<<std::endl;
        // glfwTerminate();
        return nullptr;
        
    }
    
    std::shared_ptr<RenderEngine::Sprite> newSprite = m_sprites.emplace(spriteName,
                                                                    std::make_shared<RenderEngine::Sprite>(pTexture,
                                                                                                       subtextureName,
                                                                                                       pShader,
                                                                                                       glm::vec2(0.f,0.f),
                                                                                                       glm::vec2(spriteWidth,spriteHight),
                                                                                                       0)).first->second;
    return newSprite;
                                                                                                    
}

std::shared_ptr<RenderEngine::Sprite> ResourceManager::getSprites(const std::string& spriteName)
{
    SpriteMap::const_iterator it=m_sprites.find(spriteName);
    if(it!=m_sprites.end()){
        return it->second;
    }
    std::cerr<<"Can't find sprite"
    <<spriteName
    <<std::endl;
    return nullptr;
}

std::shared_ptr< RenderEngine::Texture2D > ResourceManager::loadTextureAtlas(const std::string& textureName,
                                                                        const std::string& stexturePath,
                                                                        const std::vector<std::string> subTextures,
                                                                        const unsigned int subTexwidth,
                                                                        const unsigned int subTexheight)
{
    
    
    
    auto pTexture = loadTextures(std:: move(textureName),std:: move(stexturePath));
    
    if (pTexture) {
        const unsigned int textureWidth = pTexture ->getWidth();
        const unsigned int textureHigth = pTexture ->getHight();
        unsigned int currentTextureOffsetX = 0;
        unsigned int currentTextureOffsetY = textureHigth;
        //          unsigned int currentTextureOffsetY = 0;
        for (const auto& currentSubtextureName:subTextures)
        {
            glm::vec2 leftBottomUV(static_cast<float> (currentTextureOffsetX)/textureWidth, static_cast<float>(currentTextureOffsetY-subTexheight+0.01f)/textureHigth );
            glm::vec2 rightTopUV(static_cast<float> (currentTextureOffsetX+subTexwidth)/textureWidth, static_cast<float>(currentTextureOffsetY-0.01f)/textureHigth );
            pTexture->addSubTextures2D(std::move(currentSubtextureName),leftBottomUV,rightTopUV);
            currentTextureOffsetX+=subTexwidth;
            if (currentTextureOffsetX>=textureWidth)
            {
                currentTextureOffsetX = 0;
                currentTextureOffsetY -= subTexheight;
            }
        }
        
    }
    
    return pTexture; 
}

std::shared_ptr<RenderEngine::AnimateSprite> ResourceManager::getAnimateSprites(const std::string& spriteName)
{
    AniSpriteMap::const_iterator it = m_anisprites.find(spriteName);
    if(it!=m_anisprites.end()){
        return it->second;
    }
    std::cerr<<"Can't find anisprite " <<spriteName <<std::endl;
    return nullptr;
    
}

std::shared_ptr<RenderEngine::AnimateSprite> ResourceManager::loadAnimateSprites(const std::string& spriteName, const std::string& textureName, const std::string& shaderName, const unsigned int spriteWidth, const unsigned int spriteHight, const std::string& subtextureName)
{
    auto pTexture  = getTextures(textureName);
    if(!pTexture){
        std::cerr<< "Can't get textures "<<"for the sprite:"<<spriteName<<std::endl;
        //glfwTerminate();
        return nullptr;
    }
    
    auto pShader = getShaderProgram(shaderName);
    if(!pShader){
        std::cerr<< "Can't get shader "<<"for the sprite:"<<spriteName<<std::endl;
        // glfwTerminate();
        return nullptr;
        
    }
    
    std::shared_ptr<RenderEngine::AnimateSprite> newSprite = m_anisprites.emplace(spriteName,
                                                                            std::make_shared<RenderEngine::AnimateSprite>(pTexture,
                                                                                                                        subtextureName,
                                                                                                                        pShader,
                                                                                                                        glm::vec2(0.f,0.f),
                                                                                                                        glm::vec2(spriteWidth,spriteHight),
                                                                                                                        0)).first->second;
                                                                                                                        return newSprite;
                                                                                                                        
}

bool ResourceManager::loadJSONResources(const std::string& JSON)
{
    const std::string JSONstring = getFileString(JSON);
    if (JSONstring.empty())
    {
        std::cerr << "No JSON resourses file"<<std::endl;
            return false;
    }
    
    rapidjson::Document document;
    rapidjson::ParseResult parsOk = document.Parse(JSONstring.c_str());
//     std::cout<<"getting: "<<JSONstring.length()<<std::endl;
    if(!parsOk){
        std::cerr << "Parse file error"<< rapidjson::GetParseError_En(parsOk.Code())<<"("<<parsOk.Offset()<<")" <<std::endl;
        std::cerr << "In JSONfile:" << JSON<<std::endl;
        return false;
    }
    
    auto shadersIt = document.FindMember("shaders");
    if (shadersIt!=document.MemberEnd())
    {
        for (const auto& currentShader : shadersIt-> value.GetArray())
        {
            const std::string name = currentShader["name"].GetString() ;
            const std::string filepath_v = currentShader["filePath_v"].GetString() ;
            const std::string filepath_f = currentShader["filePath_f"].GetString() ;
            loadShaders(name, filepath_v,filepath_f);
            
        }
    }
    else { return false;}
    
    auto textureAtlas = document.FindMember("textureAtlas");
    if (textureAtlas!=document.MemberEnd())
    {
        for (const auto& currentTextureAtlas : textureAtlas-> value.GetArray())
        {
            const std::string name = currentTextureAtlas["name"].GetString() ;
            const std::string filepath = currentTextureAtlas["filePath"].GetString() ;
            const unsigned int subTextureWidth = currentTextureAtlas["subTextureWidth"].GetUint() ;
            const unsigned int subTextureHight = currentTextureAtlas["subTextureHight"].GetUint() ;
            const auto subTexturesArray = currentTextureAtlas["subTextureArray"].GetArray();
            std::vector<std::string> subTextures;
            subTextures.reserve(subTexturesArray.Size());
            for(const auto& currentSubtextures : subTexturesArray){
                subTextures.emplace_back(currentSubtextures.GetString());                
            }
            
            loadTextureAtlas(name, filepath,std::move(subTextures), subTextureWidth,subTextureHight);
            
        }
    } else { return false;}
    
    
    auto animateSpritesIt = document.FindMember("animatedSprites");
    if (animateSpritesIt!=document.MemberEnd())
    {
        for (const auto& currentAnimateSprite : animateSpritesIt-> value.GetArray())
        {
            const std::string name = currentAnimateSprite["name"].GetString() ;
            const std::string atlas = currentAnimateSprite["textureAtlas"].GetString() ;
            const std::string shader = currentAnimateSprite["shader"].GetString() ;
            const unsigned int initialWidth = currentAnimateSprite["initialWidth"].GetUint() ;
            const unsigned int initialHight = currentAnimateSprite["initialHight"].GetUint() ;
            const std::string  initialSubTexture = currentAnimateSprite["initialSubTexture"].GetString();           
            
         
        
            auto pAnimatedSprite = loadAnimateSprites(name,atlas,shader,initialWidth,initialHight,initialSubTexture);
            if(! pAnimatedSprite ){
                std::cerr << "Can't load sprite (initial) "<< initialSubTexture << std::endl;
                return false;
            }
            
            const auto statesArray = currentAnimateSprite["states"].GetArray();
            
            for(const auto& currentStateArray : statesArray){
                const std::string stateName = currentStateArray["statesName"].GetString();
                std::vector<std::pair<std::string,uint64_t>>  frames;
                const auto framesArray =  currentStateArray["frames"].GetArray();
                frames.reserve(framesArray.Size());
                for(const auto& currentFrame : framesArray){
                    const std::string subTexture = currentFrame["subTexture"].GetString();
                    const uint64_t duration = currentFrame["duration"].GetUint64();
                    frames.emplace_back(std::pair<std::string,uint64_t>(subTexture,duration));
                    
                }
                pAnimatedSprite->insertState(stateName, std::move(frames));
            }
            
            
            
        }
    } else { return false;}
    
    
    
    return true;
}
