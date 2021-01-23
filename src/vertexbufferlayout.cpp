#include "vertexbufferlayout.h"


namespace RenderEngine{
    
    VertexBufferLayout::VertexBufferLayout() : m_stride(0)
    {
        
    }
    
    void VertexBufferLayout::addElementLayoutFloat(const unsigned int count, const bool normalized)
    {
        GLint tcount = count;
        unsigned int tsize = count*sizeof(GLfloat);
        m_layoutElements.push_back({tcount, GL_FLOAT,normalized,tsize});
        m_stride+=m_layoutElements.back().size;
    }
    
    void VertexBufferLayout::reserveElements(const size_t count)
    {
        m_layoutElements.reserve(count);
    }



    
}
