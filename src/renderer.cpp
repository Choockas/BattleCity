#include "renderer.h"


namespace RenderEngine{
    
    
    Renderer::Renderer(){
        
    }
    
    void Renderer::draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer,const ShaderProgramm& shaderProgramm)
    {
        shaderProgramm.use();
        vertexArray.bind();
        indexBuffer.bind();
        glDrawElements(GL_TRIANGLES,indexBuffer.getCount(),GL_UNSIGNED_INT,nullptr);
        
    }
    
    void Renderer::setClearColor(float r,float g,float b, float a)
    {
        glClearColor(r,g,b,a);
    }
    
    void Renderer::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }
    
    void Renderer::setViewPort(unsigned int width, unsigned int hight, unsigned int leftOffset, unsigned int bottomOffset)
    {
        glViewport(leftOffset,bottomOffset,width,hight);
    }
    
    std::string Renderer::getRendererStr()
    {
       return (char*)glGetString(GL_RENDERER);
    }
    
    std::string Renderer::getVersionString()
    {
        GLint64 nrAttribs64;
        glGetInteger64v(GL_MAX_VERTEX_ATTRIBS, &nrAttribs64);
        return (char*) glGetString(GL_VERSION);
    }
    
}
