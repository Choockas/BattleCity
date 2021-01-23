#pragma once
#include <vector>
#include "glad/glad.h"

namespace RenderEngine{
    
    class VertexBufferLayout{
    public:
        struct VertexBufferLayoutElement{
            GLint count;
            GLenum type;
            GLboolean normalized;
            unsigned int size;
        };
        
        VertexBufferLayout();
//         ~VertexBufferLayout();
        void addElementLayoutFloat(const unsigned  int count,const bool normalized);
        void reserveElements(const size_t count);
        unsigned int getSride() const { return m_stride;}
        const std::vector<VertexBufferLayoutElement>& getLayoutElements() const {return m_layoutElements;} 
        
    private:
        std::vector<VertexBufferLayoutElement> m_layoutElements; 
        unsigned int m_stride;
        
    };
    
    
    
}
