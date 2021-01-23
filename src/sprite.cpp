
#include "shadeprogramm.h"
#include "texture2D.h"
#include "sprite.h"


#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "renderer.h"

namespace RenderEngine{

 Sprite::Sprite(std::shared_ptr<Texture2D>  pTexture,
                std::string initialSubTexture,
                std::shared_ptr<ShaderProgramm> pShaderProgramm,
                const glm::vec2& position,
                const glm::vec2& size,
                const float rotation) : m_pTexture(std::move(pTexture)),
                                        m_pShaderProgramm(std::move(pShaderProgramm)),
                                        m_position(position),
                                        m_size(size),
                                        m_rotation(rotation)
 {
     // 1-2
     // |/|
     // 0-3
     const GLfloat vertexCoords[] ={
    //x-y     
    0.f,0.f,
    0.f,1.f,
    1.f,1.f,
    1.f,0.f,
    
 };
auto subTexture2D = m_pTexture -> getSubtexture2D(std::move(initialSubTexture)); 
 
const GLfloat texCoords[] ={
    //U-V
            subTexture2D.leftBottomUV.x, subTexture2D.leftBottomUV.y,
            subTexture2D.leftBottomUV.x, subTexture2D.rightTopUV.y,
            subTexture2D.rightTopUV.x,   subTexture2D.rightTopUV.y,
            subTexture2D.rightTopUV.x,   subTexture2D.leftBottomUV.y,
 };
 
 const GLuint indices[] ={
       0,1,2,
       2,3,0             
 };

 
 
 
 
 m_vertexCoordsBuffer.init(vertexCoords,2*4*sizeof(GLfloat));
 VertexBufferLayout vertexCordsLayout;
 vertexCordsLayout.addElementLayoutFloat(2,false);
 m_vertexArray.addBuffer(m_vertexCoordsBuffer, vertexCordsLayout);
 
 
 
 
 m_textureCoordsBuffer.init(texCoords,2*4*sizeof(GLfloat));
 
 VertexBufferLayout textureCoordsLayout;
 textureCoordsLayout.addElementLayoutFloat(2,false);
 m_vertexArray.addBuffer(m_textureCoordsBuffer,textureCoordsLayout); 
 

 m_indexCoordsBuffer.init(indices,6);
 
 m_vertexArray.unbind();
 m_indexCoordsBuffer.unbind();
 
 

 
}

Sprite::~Sprite(){
    
}

void Sprite::render() const
{
 m_pShaderProgramm->use();
 glm::mat4 model(1.f);
 model = glm::translate(model,glm::vec3(m_position,0.f));
 model = glm::translate(model,glm::vec3(0.5f*m_size.x,0.5f*m_size.y,0.f));
 model = glm::rotate(model,glm::radians(m_rotation),glm::vec3(0.f,0.f,1.f));
 model = glm::translate(model,glm::vec3(-0.5f*m_size.x,-0.5f*m_size.y,0.f));
 model = glm::scale(model,glm::vec3(m_size,1.f));
 
 //m_vertexArray.bind();
 m_pShaderProgramm->setMatrix4("modelMat",model);
 glActiveTexture(GL_TEXTURE0);
 m_pTexture->bind();
  
 Renderer::draw(m_vertexArray,m_indexCoordsBuffer,*m_pShaderProgramm);
}

void Sprite::setPosition(const glm::vec2& position){
    m_position = position;
    
}

void Sprite::setSize(const glm::vec2& size){
    m_size = size;
    
}

void Sprite::setRotation(const float rotation){
    m_rotation = rotation;
    
}


}
