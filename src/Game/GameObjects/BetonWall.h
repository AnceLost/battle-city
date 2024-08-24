#pragma once

#include "IGameObject.h"

#include <memory>
#include <array>

namespace RenderEngine
{
	class Sprite;
}

class BetonWall : public IGameObject
{
public:
	enum class EBetonWallType
	{
		All,
		Top,
		Bottom,
		Left,
		Right,
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};
	enum class EBetonState
	{
		Enabled = 0,
		Destroyed
	};
	enum class EBetonLocation
	{
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};
	BetonWall(
		const EBetonWallType eBetonWallType,
		const glm::vec2& position,
		const glm::vec2& size,
		const float rotation,
		const float layer
	);
	void render() const override;

	void update(const uint64_t delta) override;

private:
	void renderBeton(const EBetonLocation eBetonLocation) const;

	std::array<EBetonState, 4> m_eCurrentBetonState;
	std::shared_ptr<RenderEngine::Sprite> m_sprite;
	std::array<glm::vec2, 4> m_blockOffsets;
};