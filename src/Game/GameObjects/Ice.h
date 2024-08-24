#pragma once

#include "IGameObject.h"

#include <memory>
#include <array>

namespace RenderEngine
{
	class Sprite;
}

class Ice : public IGameObject
{
public:
	enum class EIceLocation : uint8_t
	{
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};
	Ice(
		const glm::vec2& position,
		const glm::vec2& size,
		const float rotation,
		const float layer
	);
	void render() const override;

private:
	void renderIce(const EIceLocation eIceLocation) const;

	std::shared_ptr<RenderEngine::Sprite> m_sprite;
	std::array<glm::vec2, 4> m_blockOffsets;
};