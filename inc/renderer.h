#pragma once
#include "vertexarray.h"
#include "indexbuffers.h"
#include "shadeprogramm.h"

namespace RenderEngine{
    
    class Renderer{
    public:
        Renderer();
        
        static void draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const ShaderProgramm& shaderProgramm);
        static void setClearColor(float r,float g, float b, float a);
        static void clear();
        static void setViewPort(unsigned int width, unsigned int hight, unsigned int leftOffset=0, unsigned int bottomOffset=0);
        
        static std::string getRendererStr();
        static std::string getVersionString();
        
    private:
        
    };
}
