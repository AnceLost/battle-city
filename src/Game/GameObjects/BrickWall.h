#pragma once

#include "IGameObject.h"

#include <memory>
#include <array>

namespace RenderEngine
{
	class Sprite;
}

class BrickWall : public IGameObject
{
public:
	enum class EBrickWallType
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
	enum class EBrickState
	{
		All = 0,
		TopLeft = 1,
		TopRight = 2,
		Top = 3,
		BottomLeft = 4,
		Left = 5,

		TopRight_BottomLeft,
		Top_BottomLeft,
		BottomRight,
		TopLeft_BottomRight,
		Right,
		Top_BottomRight,

		Bottom,
		TopLeft_Bottom,
		TopRight_Bottom,
		Destroyed
	};
	enum class EBrickLocation
	{
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};
	BrickWall(
		const EBrickWallType eBrickWallType,
		const glm::vec2& position, 
		const glm::vec2& size,
		const float rotation,
		const float layer
	);
	void render() const override;
	
	void update(const double delta) override;

private:
	void renderBrick(const EBrickLocation eBrickLocation) const;

	std::array<EBrickState, 4> m_eCurrentBrickState;
	std::array<std::shared_ptr<RenderEngine::Sprite>, 15> m_sprites;
	std::array<glm::vec2, 4> m_blockOffsets;
};