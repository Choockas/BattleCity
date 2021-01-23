#include "indexbuffers.h"


namespace RenderEngine{
    IndexBuffer::IndexBuffer() : m_id(0),
                                 m_count(0)
{
    
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1,&m_id);
}

    RenderEngine::IndexBuffer & IndexBuffer::operator=(RenderEngine::IndexBuffer && indexBuffer) noexcept
{
    m_id = indexBuffer.m_id;
    indexBuffer.m_id = 0;
    m_count = indexBuffer.m_count;
    indexBuffer.m_count =0;
    return *this;
}

IndexBuffer::IndexBuffer(RenderEngine::IndexBuffer && indexBuffer) noexcept
{
    m_id = indexBuffer.m_id;
    indexBuffer.m_id = 0;
    m_count = indexBuffer.m_count;
    indexBuffer.m_count = 0;
}

    
void IndexBuffer::init(const void* data, const unsigned int count){
        GLint csize=0;
        GLuint tsize = count *sizeof(GLuint);
        m_count = count;
        glGenBuffers(1,&m_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,tsize,data,GL_STATIC_DRAW);
        glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER,GL_BUFFER_SIZE,&csize);
        if(csize!=tsize){
            glDeleteBuffers(1,&m_id); 
            return;            
        }                  
}
    
void IndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_id);
}
    
void IndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}



}
