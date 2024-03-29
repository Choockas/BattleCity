#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>

#include <memory>
#include <string>
#include "vertexbuffers.h"
#include "indexbuffers.h"
#include "vertexarray.h"


namespace RenderEngine {
    class Texture2D;
    class ShaderProgramm;
    
    class Sprite{
    public:
        Sprite (std::shared_ptr<Texture2D>  pTexture,
                std::string initialSubTexture,
                std::shared_ptr<ShaderProgramm> pShaderProgramm,
                const glm::vec2& position = glm::vec2(0.f),
                const glm::vec2& size= glm::vec2(1.f),
                const float rotation=0.f
               );
        //~Sprite();
        virtual ~ Sprite();
        Sprite(Sprite&) = delete;
        Sprite& operator=(const Sprite&) = delete; 
         virtual void render() const;
         void setPosition(const glm::vec2& position);
         void setSize(const glm::vec2&  size);
         void setRotation(const float rotation);
    protected:
        std::shared_ptr<Texture2D> m_pTexture;
        std::shared_ptr<ShaderProgramm> m_pShaderProgramm;
        glm::vec2 m_position;
        glm::vec2 m_size;
        float m_rotation;
        
        VertexArray m_vertexArray;
        VertexBuffer m_vertexCoordsBuffer;
        VertexBuffer m_textureCoordsBuffer;
        IndexBuffer m_indexCoordsBuffer;
        

    };
 
}

