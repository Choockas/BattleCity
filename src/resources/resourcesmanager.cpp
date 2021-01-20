
#include "texture2D.h"
#include "shadeprogramm.h"
#include "sprite.h"
#include "animatesprite.h"
#include "resourcesmanager.h"

#include <fstream>
#include <sstream>
#include <iostream>


#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"



ResourceManager::ResourceManager(const std::string& executablePath)
{
    size_t found = executablePath.find_last_of("/\\");
    m_path = executablePath.substr(0,found); 
    std::cout<< "resurse manager is created, "<<"looked for"<<m_path<<std::endl;
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

std::shared_ptr<Renderer::ShaderProgramm> ResourceManager::loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string vertexString = getFileString(vertexPath);
    if (vertexString.empty()){
        std::cerr<<"No vertex shader!"<< std::endl;
    }
    std::string fragmentString = getFileString(fragmentPath);
    if (fragmentString.empty()){
        std::cerr<<"No fragment shader!"<< std::endl;
    }
    
    std::shared_ptr<Renderer::ShaderProgramm>& newShader = m_shaderPrograms.emplace(shaderName, std::make_shared<Renderer::ShaderProgramm>(vertexString,fragmentString)).first->second;
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

std::shared_ptr<Renderer::ShaderProgramm> ResourceManager::getShaderProgram(const std::string& shaderName)
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

std::shared_ptr<Renderer::Texture2D> ResourceManager::loadTextures(const std::string& textureName, const std::string& texturePath)
{
    int chanels = 0;
    int width = 0;
    int hight = 0;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* pixels =stbi_load(std::string(m_path+"/"+texturePath ).c_str(),&width,&hight,&chanels,0);
    std::cout<<""<<m_path<<std::endl;
    if(!pixels){
        std::cerr<<"Can't load image "<<texturePath<<std::endl;
        return nullptr;
    }
    
    std::shared_ptr<Renderer::Texture2D>& newTexture =
    m_texture2D.emplace(textureName,
                        std::make_shared<Renderer::Texture2D>(width,
                                                              hight,
                                                              pixels,
                                                              chanels,
                                                              GL_NEAREST,
                                                              GL_CLAMP_TO_EDGE )).first->second;
    stbi_image_free(pixels);                                                               
    
    return newTexture;
}

std::shared_ptr<Renderer::Texture2D> ResourceManager::getTextures(const std::string& textureName)
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

std::shared_ptr<Renderer::Sprite> ResourceManager::loadSprites(const std::string& spriteName,
                                                               const std::string& textureName,
                                                               const std::string& shaderName,
                                                               const unsigned int spriteWidth,
                                                               const unsigned int spriteHight,
                                                               const std::string& subtextureName 
                                                              )
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
    
    std::shared_ptr<Renderer::Sprite> newSprite = m_sprites.emplace(spriteName,
                                                                    std::make_shared<Renderer::Sprite>(pTexture,
                                                                                                       subtextureName,
                                                                                                       pShader,
                                                                                                       glm::vec2(0.f,0.f),
                                                                                                       glm::vec2(spriteWidth,spriteHight),
                                                                                                       0)).first->second;
        return newSprite;
    
}

std::shared_ptr<Renderer::Sprite> ResourceManager::getSprites(const std::string& spriteName)
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

std::shared_ptr< Renderer::Texture2D > ResourceManager::loadTextureAtlas(const std::string& textureName,
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

std::shared_ptr<Renderer::AnimateSprite> ResourceManager::getAnimateSprites(const std::string& spriteName)
{
    AniSpriteMap::const_iterator it = m_anisprites.find(spriteName);
    if(it!=m_anisprites.end()){
        return it->second;
    }
    std::cerr<<"Can't find anisprite"
    <<spriteName
    <<std::endl;
    return nullptr;
    
}

std::shared_ptr<Renderer::AnimateSprite> ResourceManager::loadAnimateSprites(const std::string& spriteName, const std::string& textureName, const std::string& shaderName, const unsigned int spriteWidth, const unsigned int spriteHight, const std::string& subtextureName)
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
    
    std::shared_ptr<Renderer::AnimateSprite> newSprite = m_anisprites.emplace(spriteName,
                                                                    std::make_shared<Renderer::AnimateSprite>(pTexture,
                                                                                                       subtextureName,
                                                                                                       pShader,
                                                                                                       glm::vec2(0.f,0.f),
                                                                                                       glm::vec2(spriteWidth,spriteHight),
                                                                                                       0)).first->second;
        return newSprite;
    
}

