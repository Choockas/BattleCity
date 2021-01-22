#include "indexbuffers.h"


namespace Renderer{
    IndexBuffer::IndexBuffer() : m_id(0)
{
    
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1,&m_id);
}

    Renderer::IndexBuffer & IndexBuffer::operator=(Renderer::IndexBuffer && indexBuffer) noexcept
{
    m_id = indexBuffer.m_id;
    indexBuffer.m_id = 0;
    return *this;
}

IndexBuffer::IndexBuffer(Renderer::IndexBuffer && indexBuffer) noexcept
{
    m_id = indexBuffer.m_id;
    indexBuffer.m_id = 0;
}

    
void IndexBuffer::init(const void* data, const unsigned int size){
        GLint csize=0;
        glGenBuffers(1,&m_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,size,data,GL_STATIC_DRAW);
        glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER,GL_BUFFER_SIZE,&csize);
        if(csize!=size){
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
