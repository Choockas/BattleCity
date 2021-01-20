#pragma once

#include <string>
#include <memory>
#include <map>
#include <vector>

namespace Renderer
{
    class ShaderProgramm;
    class Texture2D;
    class Sprite;
    class AnimateSprite;
}


//using namespace Renderer;

void startResourceManager(char);

class ResourceManager{
    public:
        ResourceManager(const std::string& executablePath);
        ~ResourceManager() = default;
        ResourceManager(const ResourceManager& ) = delete;
        ResourceManager& operator = (const ResourceManager&) = delete;
        ResourceManager& operator = (ResourceManager&&) = delete;
        ResourceManager(ResourceManager&&) = delete;
        std::shared_ptr<Renderer::ShaderProgramm> loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath );
       std::shared_ptr<Renderer::ShaderProgramm> getShaderProgram(const std::string& shaderName);
       void loadTexture(const std::string& textureName, const std::string& texturePath); 
       std::shared_ptr<Renderer::Texture2D> loadTextures(const std::string& textureName,const std::string& texturePath );
       std::shared_ptr<Renderer::Texture2D> getTextures(const std::string& textureName);
       std::shared_ptr<Renderer::Sprite> loadSprites(const std::string& spriteName,
                                                     const std::string& textureName,
                                                     const std::string& shaderName,
                                                     const unsigned int spriteWidth,
                                                     const unsigned int spriteHight,
                                                     const std::string& subtextureName = "default");
       std::shared_ptr<Renderer::AnimateSprite> loadAnimateSprites(const std::string& spriteName,
                                                     const std::string& textureName,
                                                     const std::string& shaderName,
                                                     const unsigned int spriteWidth,
                                                     const unsigned int spriteHight,
                                                     const std::string& subtextureName = "default");
        std::shared_ptr<Renderer::Sprite> getSprites(const std::string& spriteName);
        std::shared_ptr<Renderer::AnimateSprite> getAnimateSprites(const std::string& spriteName);
        
        std::shared_ptr<Renderer::Texture2D> loadTextureAtlas(const std::string& textureName,
                                                             const std::string& stexturePath,
                                                             const std::vector<std::string> subTextures,
                                                             const unsigned int subTexwidth,
                                                             const unsigned int subTexheight);
private:
    std::string getFileString(const std::string& relativePath);
    std::string m_path;
    
    
    typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgramm>> ShaderProgramsMap;
    ShaderProgramsMap m_shaderPrograms;
    
    typedef std::map<const std::string, std::shared_ptr<Renderer::Texture2D>> Texture2DMap;
    Texture2DMap m_texture2D;
    
    typedef std::map<const std::string, std::shared_ptr<Renderer::Sprite>> SpriteMap;
    SpriteMap m_sprites;
    
    typedef std::map<const std::string, std::shared_ptr<Renderer::AnimateSprite>> AniSpriteMap;
    AniSpriteMap m_anisprites;
    
};




 
