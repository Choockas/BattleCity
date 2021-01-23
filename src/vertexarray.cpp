#include "vertexarray.h"


namespace RenderEngine{
    VertexArray::VertexArray() : m_id(0)
{
    glGenVertexArrays(1,&m_id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1,&m_id);
}

    RenderEngine::VertexArray & VertexArray::operator=(RenderEngine::VertexArray && vertexArray) noexcept
{
    m_id = vertexArray.m_id;
    vertexArray.m_id = 0;
    return *this;
}

VertexArray::VertexArray(RenderEngine::VertexArray && vertexArray) noexcept
{
    m_id = vertexArray.m_id;
    vertexArray.m_id = 0;
}

    
void VertexArray::addBuffer(const VertexBuffer& vertexBuffer,const VertexBufferLayout& vertexBufferLayout) 
{
    bind();
    vertexBuffer.bind();
    const auto& layoutElements = vertexBufferLayout.getLayoutElements();
    GLbyte* offset = nullptr;
    for( unsigned int i =0; i< layoutElements.size();++i){
        const auto& currentLayoutElement = layoutElements[i];
        GLuint currentAttribIndex = m_elementssCount+i;
        glEnableVertexAttribArray(currentAttribIndex);
        glVertexAttribPointer(currentAttribIndex,
                              currentLayoutElement.count,
                              currentLayoutElement.type,
                              currentLayoutElement.normalized,
                              vertexBufferLayout.getSride(),
                              offset);
        offset+= currentLayoutElement.size;          
    }
    m_elementssCount += layoutElements.size();        
}
    
void VertexArray::bind() const
{
    glBindVertexArray(m_id);
}
    
void VertexArray::unbind() const
{
    glBindVertexArray(0);
}



}
