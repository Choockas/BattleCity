#pragma once
#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <iostream>
#include <string>
#include <map>


namespace Renderer {
    
    class Texture2D{
    public:
        struct SubTexture2D{
            glm::vec2 leftBottomUV;
            glm::vec2 rightTopUV;
            
            SubTexture2D(const glm::vec2& _leftBottomUV, const glm::vec2& _rightTopUV)
            : leftBottomUV(_leftBottomUV)
            , rightTopUV(_rightTopUV)
            {}
            
            SubTexture2D()
            : leftBottomUV(0.f)
            , rightTopUV(1.f)
            {}
            
        };
        Texture2D(const GLuint width,
                  const GLuint hight,
                  const unsigned char* data,
                  const GLuint chanals=4,
                  const GLenum filter=GL_LINEAR,
                  const GLenum wrapMode=GL_CLAMP_TO_EDGE);
        ~Texture2D();
        Texture2D() = delete;
        Texture2D(const Texture2D&)= delete;
        Texture2D& operator=(const Texture2D&)=delete;
        Texture2D& operator=(Texture2D&& texture2D);
        Texture2D(Texture2D&& texture2D);
        void addSubTextures2D(std::string name,glm::vec2& leftBottomUV, glm::vec2& rightTopUV);
        const SubTexture2D& getSubtexture2D(const std::string name) const;
        void bind() const;
        unsigned int getWidth() const{ return m_width;}
        unsigned int getHight() const{ return m_hight;}
    private:
        GLuint m_ID;
        GLenum m_mode;
        unsigned int m_width;
        unsigned int m_hight;
        std::map<std::string,SubTexture2D> m_subTextures2D;
        
    };    
    



    
}
