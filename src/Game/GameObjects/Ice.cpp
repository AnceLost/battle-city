#include "Ice.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"

#include <memory>

Ice::Ice(
    const glm::vec2& position,
    const glm::vec2& size,
    const float rotation,
    const float layer
) : IGameObject(position, size, rotation, layer),
    m_blockOffsets{
        glm::vec2(0, m_size.y / 2.f),
        glm::vec2(m_size.x / 2.f, m_size.y / 2.f),
        glm::vec2(0, 0),
        glm::vec2(m_size.x / 2.f, 0)
    },
    m_sprite(ResourceManager::getSprite("ice"))
{
    
}
void Ice::renderIce(const EIceLocation eBetonLocation) const
{
    m_sprite->render(
        m_position + m_blockOffsets[static_cast<size_t>(eBetonLocation)],
        m_size / 2.f, 
        m_rotation,
        m_layer
    );
}
void Ice::render() const
{
    renderIce(EIceLocation::TopLeft);
    renderIce(EIceLocation::TopRight);
    renderIce(EIceLocation::BottomLeft);
    renderIce(EIceLocation::BottomRight);
}