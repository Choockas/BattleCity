#include "tank.h"
#include "animatesprite.h"
#include <iostream>



Tank::Tank(std::shared_ptr<Renderer::AnimateSprite> pSprite, const float velocity, const glm::vec2& position) :
                                    m_orientation(EOrientation::BOTTOM)
                                    ,m_sprite(std::move(pSprite))
                                    ,m_move(false)
                                    ,m_velocity(velocity)
                                    ,m_position(position)
                                    ,m_move_offset( glm::vec2(0.f,1.f))
{
    m_sprite->setPosition(m_position);
    
}

void Tank::move(const bool move)
{
    m_move = move;
}

void Tank::render() const
{
    m_sprite->render();
}

void Tank::setOrientation(Tank::EOrientation eorientation)
{
    
    if (m_orientation == eorientation){
        return;
    }else{
      std::string ss;  
    switch(eorientation){
        case Tank::EOrientation::TOP:
            ss="tankTopState";
            
            m_move_offset.x = 0.f;
            m_move_offset.y = 1.f;
            m_orientation=Tank::EOrientation::TOP;
            break;
        case Tank::EOrientation::BOTTOM:
            ss="tankBottomState";
            
            m_move_offset.x = 0.f;
            m_move_offset.y = -1.f;
            m_orientation=Tank::EOrientation::BOTTOM;
            break;
        case Tank::EOrientation::LEFT:
            ss="tankLeftState";
            
            m_move_offset.x = -1.f;
            m_move_offset.y = 0.f;
            m_orientation=Tank::EOrientation::LEFT;
            break;
        case Tank::EOrientation::RIGHT:
            ss="tankRightState";
            
            m_move_offset.x = 1.f;
            m_move_offset.y = 0.f;
            m_orientation=Tank::EOrientation::RIGHT;
            break;
        default:
//             ss="tankTopState";
            break;
    }
    m_sprite->setState(ss);
    } 
}


void Tank::update(const uint64_t delta)
{
    float ddel;
    ddel = static_cast<float> (delta);
    if(m_move){
        m_position += m_velocity*m_move_offset*ddel;        
        m_sprite->setPosition(m_position); 
        m_sprite->update(delta);
    }
}

