
#include "shadeprogramm.h"
#include "texture2D.h"
#include "sprite.h"


#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

namespace Renderer{

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
 
 const GLuint indexes[] ={
       0,1,2,
       2,3,0             
 };

 glGenVertexArrays(1,&m_VAO);
 glBindVertexArray(m_VAO);
 
 m_vertexCoordsBuffer.init(vertexCoords,2*4*sizeof(GLfloat));
 
 
 glEnableVertexAttribArray(0);
 glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,nullptr);
 
 m_textureCoordsBuffer.init(texCoords,2*4*sizeof(GLfloat));
 
 glEnableVertexAttribArray(1);
 glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,nullptr);

 m_indexCoordsBuffer.init(indexes,6*sizeof(GLuint));
 
 
 glBindBuffer(GL_ARRAY_BUFFER,0);
//  m_vertexCoordsBuffer.unbind();
 glBindVertexArray(0);
//  m_indexCoordsBuffer.unbind();
 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
 
}

Sprite::~Sprite(){
    glDeleteVertexArrays(1,&m_VAO);
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
 
 glBindVertexArray(m_VAO);
 m_pShaderProgramm->setMatrix4("modelMat",model);
 glActiveTexture(GL_TEXTURE0);
 m_pTexture->bind();
 
//  glDrawArrays(GL_TRIANGLES,0,6); 
 glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,nullptr);
 glBindVertexArray(0);
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
