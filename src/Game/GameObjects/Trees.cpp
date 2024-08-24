#include "Trees.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"

#include <memory>

Trees::Trees(
    const glm::vec2& position,
    const glm::vec2& size,
    const float rotation
) : IGameObject(position, size, rotation),
    m_blockOffsets{
        glm::vec2(0, m_size.y / 2.f),
        glm::vec2(m_size.x / 2.f, m_size.y / 2.f),
        glm::vec2(0, 0),
        glm::vec2(m_size.x / 2.f, 0)
    },
    m_sprite(ResourceManager::getSprite("trees"))
{
    
}
void Trees::renderTrees(const ETreeLocation eTreeLocation) const
{
    m_sprite->render(
        m_position + m_blockOffsets[static_cast<size_t>(eTreeLocation)],
        m_size / 2.f, 
        m_rotation
    );
}
void Trees::render() const
{
    renderTrees(ETreeLocation::TopLeft);
    renderTrees(ETreeLocation::TopRight);
    renderTrees(ETreeLocation::BottomLeft);
    renderTrees(ETreeLocation::BottomRight);
}