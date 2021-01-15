#pragma once
#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>

#include <memory>
#include <string>


namespace Renderer {
    class Texture2D;
    class ShaderProgramm;
    
    class Sprite{
    public:
        Sprite (const std::shared_ptr<Texture2D>  pTexture,
                std::shared_ptr<ShaderProgramm> pShaderProgramm,
                const glm::vec2& position,
                const glm::vec2& size,
                const float rotation=0
               );
        ~Sprite();
        Sprite(Sprite&) = delete;
        Sprite& operator=(const Sprite&) = delete; 
         void render() const;
         void setPosition(const glm::vec2& position);
         void setSize(const glm::vec2&  size);
         void setRotation(const float rotation);
    private:
        std::shared_ptr<Texture2D> m_pTexture;
        std::shared_ptr<ShaderProgramm> m_pShaderProgramm;
        glm::vec2 m_position;
        glm::vec2 m_size;
        float m_rotation;
        GLuint m_VAO;
        GLuint m_vertexCoordsVBO;
        GLuint m_texCoordsVBO;
    };
 
}

