#include "vertexbuffers.h"


namespace RenderEngine{
    VertexBuffer::VertexBuffer() : m_id(0)
{
    
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1,&m_id);
}

    RenderEngine::VertexBuffer & VertexBuffer::operator=(RenderEngine::VertexBuffer && vertexBuffer) noexcept
{
    m_id = vertexBuffer.m_id;
    vertexBuffer.m_id = 0;
    return *this;
}

VertexBuffer::VertexBuffer(RenderEngine::VertexBuffer && vertexBuffer) noexcept
{
    m_id = vertexBuffer.m_id;
    vertexBuffer.m_id = 0;
}

    
    void VertexBuffer::init(const void* data, const unsigned int size){
        GLint  csize = 0;
        glGenBuffers(1,&m_id);
        glBindBuffer(GL_ARRAY_BUFFER,m_id);
        glBufferData(GL_ARRAY_BUFFER,size,data,GL_STATIC_DRAW);
        glGetBufferParameteriv(GL_ARRAY_BUFFER,GL_BUFFER_SIZE,&csize);
        if(csize!=size){
            glDeleteBuffers(1,&m_id); 
            return;
            
        }        
    }
    
void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER,m_id);
}
    
void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void VertexBuffer::update(const void* data, const unsigned int size) const
{
    glBindBuffer(GL_ARRAY_BUFFER,m_id);
    glBufferSubData(GL_ARRAY_BUFFER,0,size,data);
}

}
