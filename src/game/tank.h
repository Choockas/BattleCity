#pragma once
#include <memory>
#include "glm/vec2.hpp"

namespace RenderEngine{
    class AnimateSprite;
}
class Tank{
public:
    Tank(std::shared_ptr<RenderEngine::AnimateSprite> pSprite, const float velocity, const glm::vec2& position);
    enum class EOrientation{
        TOP,
        BOTTOM,
        LEFT,
        RIGHT};
    void render() const;
    void setOrientation(EOrientation eorientation);
    void move(const bool move);
    void update(const uint64_t delta);
    ~Tank();
private:
    EOrientation m_orientation;
    std::shared_ptr<RenderEngine::AnimateSprite> m_sprite;
    bool m_move;
    float m_velocity;
    glm::vec2 m_position;
    glm::vec2 m_move_offset;
};
