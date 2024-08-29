#include "BetonWall.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"

#include <memory>

BetonWall::BetonWall(
    const EBetonWallType eBetonWallType,
    const glm::vec2& position,
    const glm::vec2& size,
    const float rotation,
    const float layer
) : IGameObject(position, size, rotation, layer),
    m_eCurrentBetonState{
        EBetonState::Destroyed,
        EBetonState::Destroyed,
        EBetonState::Destroyed,
        EBetonState::Destroyed
    },
    m_blockOffsets{
        glm::vec2(0, m_size.y / 2.f),
        glm::vec2(m_size.x / 2.f, m_size.y / 2.f),
        glm::vec2(0, 0),
        glm::vec2(m_size.x / 2.f, 0)
    },
    m_sprite(ResourceManager::getSprite("betonWall"))
{
    switch (eBetonWallType)
    {
    case EBetonWallType::All:
        m_eCurrentBetonState.fill(EBetonState::Enabled);
        m_colliders.emplace_back(glm::vec2(0), m_size);
        break;
    case EBetonWallType::Top:
        m_eCurrentBetonState[static_cast<size_t>(EBetonLocation::TopLeft)] = EBetonState::Enabled;
        m_eCurrentBetonState[static_cast<size_t>(EBetonLocation::TopRight)] = EBetonState::Enabled;
        m_colliders.emplace_back(glm::vec2(0, m_size.y / 2.f), m_size);
        break;
    case EBetonWallType::Bottom:
        m_eCurrentBetonState[static_cast<size_t>(EBetonLocation::BottomLeft)] = EBetonState::Enabled;
        m_eCurrentBetonState[static_cast<size_t>(EBetonLocation::BottomRight)] = EBetonState::Enabled;
        m_colliders.emplace_back(glm::vec2(0), glm::vec2(m_size.x, m_size.y / 2.f));
        break;
    case EBetonWallType::Left:
        m_eCurrentBetonState[static_cast<size_t>(EBetonLocation::TopLeft)] = EBetonState::Enabled;
        m_eCurrentBetonState[static_cast<size_t>(EBetonLocation::BottomLeft)] = EBetonState::Enabled;
        m_colliders.emplace_back(glm::vec2(0), glm::vec2(m_size.x / 2.f, m_size.y));
        break;
    case EBetonWallType::Right:
        m_eCurrentBetonState[static_cast<size_t>(EBetonLocation::TopRight)] = EBetonState::Enabled;
        m_eCurrentBetonState[static_cast<size_t>(EBetonLocation::BottomRight)] = EBetonState::Enabled;
        m_colliders.emplace_back(glm::vec2(m_size.x / 2.f, 0), m_size);
        break;
    case EBetonWallType::TopLeft:
        m_eCurrentBetonState[static_cast<size_t>(EBetonLocation::TopLeft)] = EBetonState::Enabled;
        m_colliders.emplace_back(glm::vec2(0, m_size.y / 2.f), glm::vec2(m_size.x / 2.f, m_size.y));
        break;
    case EBetonWallType::TopRight:
        m_eCurrentBetonState[static_cast<size_t>(EBetonLocation::TopRight)] = EBetonState::Enabled;
        m_colliders.emplace_back(m_size / 2.f, m_size);
        break;
    case EBetonWallType::BottomLeft:
        m_eCurrentBetonState[static_cast<size_t>(EBetonLocation::BottomLeft)] = EBetonState::Enabled;
        m_colliders.emplace_back(glm::vec2(0), m_size / 2.f);
        break;
    case EBetonWallType::BottomRight:
        m_eCurrentBetonState[static_cast<size_t>(EBetonLocation::BottomRight)] = EBetonState::Enabled;
        m_colliders.emplace_back(glm::vec2(m_size.x / 2.f, 0), glm::vec2(m_size.x, m_size.y / 2.f));
        break;
    }
}
void BetonWall::renderBeton(const EBetonLocation eBetonLocation) const
{
    const EBetonState state = m_eCurrentBetonState[static_cast<size_t>(eBetonLocation)];
    if (state != EBetonState::Destroyed)
    {
        m_sprite->render(
            m_position + m_blockOffsets[static_cast<size_t>(eBetonLocation)],
            m_size / 2.f, 
            m_rotation,
            m_layer
        );
    }
}
void BetonWall::render() const
{
    renderBeton(EBetonLocation::TopLeft);
    renderBeton(EBetonLocation::TopRight);
    renderBeton(EBetonLocation::BottomLeft);
    renderBeton(EBetonLocation::BottomRight);
}
void BetonWall::update(const double delta)
{

}