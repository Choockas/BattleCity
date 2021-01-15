#pragma once
#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <iostream>
#include <string>
#include <map>


namespace Renderer {
    
class Texture2D{
public:
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
    void bind() const;
    //void clearSH(){ glDeleteTextures(1,&m_ID);};
private:
    GLuint m_ID;
    GLenum m_mode;
    unsigned int m_width;
    unsigned int m_hight;
    
};    
    



    
}
