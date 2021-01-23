#include "animatesprite.h"
#include "texture2D.h"
#include <iostream>

namespace RenderEngine{

 AnimateSprite::AnimateSprite( std::shared_ptr<Texture2D>  pTexture,
                std::string initialSubTexture,
                std::shared_ptr<ShaderProgramm> pShaderProgramm,
                const glm::vec2& position,
                const glm::vec2& size,
                const float rotation) : Sprite(std::move(pTexture),
                                               std::move(initialSubTexture),
                                               std::move(pShaderProgramm),
                                               std::move(position),
                                               std::move(size),
                                               std::move(rotation))
                
 {
     m_pCurrentAnimationDuration = m_statesMap.end();
     
 }


void AnimateSprite::insertState(std::string state, std::vector<std::pair<std::string, uint64_t > > subTexturesDuration)
{
        m_statesMap.emplace(std::move(state),std::move(subTexturesDuration));
}


void AnimateSprite::setState(std::string& newState)
{
    auto it = m_statesMap.find(newState);
    if (it==m_statesMap.end()){
        std::cout << "cant find state"<<newState<<std::endl;
        return;
    }
    if(it!= m_pCurrentAnimationDuration){
        m_currentAnimationTime =0;
        m_currentFrame = 0;
        m_pCurrentAnimationDuration =it; 
        m_dirty = true; 
    }
    
}

void AnimateSprite::update(const uint64_t delta) 
{
    if(m_pCurrentAnimationDuration != m_statesMap.end()){
        m_currentAnimationTime+= delta;
        while(m_currentAnimationTime>= m_pCurrentAnimationDuration->second[m_currentFrame].second){
            m_currentAnimationTime -=m_pCurrentAnimationDuration->second[m_currentFrame].second;
            ++m_currentFrame;
            m_dirty = true;
        
        if(m_currentFrame == m_pCurrentAnimationDuration->second.size()){
            m_currentFrame =0;
        }
        }
    }
}


void AnimateSprite::render() const 
{
    if (m_dirty){
        
        auto subTexture2D = m_pTexture -> getSubtexture2D(m_pCurrentAnimationDuration->second[m_currentFrame].first); 
        
        const GLfloat texCoords[] ={
            //U-V
            subTexture2D.leftBottomUV.x, subTexture2D.leftBottomUV.y,
            subTexture2D.leftBottomUV.x, subTexture2D.rightTopUV.y,
            subTexture2D.rightTopUV.x,   subTexture2D.rightTopUV.y,
            subTexture2D.rightTopUV.x,   subTexture2D.leftBottomUV.y,
        };
        m_textureCoordsBuffer.update(texCoords,2*4*sizeof(GLfloat)); 
        
//         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
        m_dirty = false;
    }
    Sprite::render();
    
}

}
