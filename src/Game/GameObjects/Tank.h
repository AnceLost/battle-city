#pragma once

#include <memory>

#include <glm/vec2.hpp>

#include "IGameObject.h"

namespace RenderEngine {
	class AnimatedSprite;
}

class Tank : IGameObject {
public:
	enum class EOrientation {
		Top,
		Bottom,
		Left,
		Right
	};
	Tank(
		std::shared_ptr<RenderEngine::AnimatedSprite> pSprite,
		const float velocity,
		const glm::vec2& position,
		const glm::vec2& size,
		const float rotation = 0.f
	);

	void render() const override;
	void setOrientation(const EOrientation orientation);
	void move(const bool move);
	void update(const uint64_t delta) override;

private:
	EOrientation m_eOrientation;
	std::shared_ptr<RenderEngine::AnimatedSprite> m_pSprite;
	bool m_move;
	float m_velocity;
	glm::vec2 m_moveOffset;
};