#pragma once
#include "glad/glad.h"
#include "vertexbuffers.h"
#include "vertexbufferlayout.h"

namespace RenderEngine{
    
    
    
    class VertexArray{
    public:
        VertexArray();
        ~VertexArray();
        VertexArray(const VertexArray&)=delete;
        VertexArray& operator = (const VertexArray&)= delete;
        VertexArray& operator = (VertexArray&&) noexcept;
        VertexArray(VertexArray&&) noexcept;
        
        
        void addBuffer(const VertexBuffer& vertexBuffer,const VertexBufferLayout&);
        void bind() const;
        void unbind() const;
    private:
        GLuint m_id=0;
        size_t m_elementssCount=0;
        
    };
        
    
    
}
