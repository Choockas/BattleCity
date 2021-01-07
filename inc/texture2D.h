#pragma once


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
private:
    GLuint m_ID;
    GLenum m_mode;
    unsigned int m_width;
    unsigned int m_hight;
    
};    
    
   
Texture2D::Texture2D(const GLuint width,
              const GLuint hight,
              const unsigned char* data,
              const GLuint chanals,
              const GLenum filter ,
              const GLenum wrapMode): m_width(width), m_hight(hight)
{
    switch(chanals){
        case 3:
            m_mode = GL_RGB;
            break;
        case 4:
            m_mode = GL_RGBA;
            break;
        default:
            m_mode = GL_RGBA;
            break;
    }
    glGenTextures(1,&m_ID);
    glBindTexture(GL_TEXTURE_2D,m_ID);
    glTexImage2D(GL_TEXTURE_2D,0, m_mode,m_width,m_hight,0,GL_RGB,GL_UNSIGNED_BYTE,data);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, wrapMode);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, filter);  
    glBindTexture(GL_TEXTURE_2D,0);
}

void Texture2D::bind() const
{
    glBindTexture(GL_TEXTURE_2D,m_ID);
}

Texture2D::~Texture2D()
{
    glDeleteTextures(1,&m_ID);
}

Texture2D& Texture2D::operator=(Texture2D&& texture2D)
{
    glDeleteTextures(1,&m_ID);
    m_ID = texture2D.m_ID;
    texture2D.m_ID = 0;
    m_mode = texture2D.m_mode;
    m_width = texture2D.m_width;
    m_hight = texture2D.m_hight;
    return *this;
}

 Texture2D::Texture2D(Texture2D&& texture2D)
 {
     m_ID = texture2D.m_ID;
    texture2D.m_ID = 0;
    m_mode = texture2D.m_mode;
    m_width = texture2D.m_width;
    m_hight = texture2D.m_hight;  
     
}



    
}
