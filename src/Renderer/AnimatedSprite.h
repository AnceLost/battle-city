#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>

#include <memory>
#include <string>
#include <map>
#include <vector>

#include "Sprite.h"

namespace RenderEngine {

    class AnimatedSprite : public Sprite {
    public:
        AnimatedSprite(
            const std::shared_ptr<Texture2D> pTexture,
            const std::string initialSubTexture,
            const std::shared_ptr<ShaderProgram> pShaderProgramf
        );
        void insertState(std::string state, std::vector<std::pair<std::string, uint64_t>> subTexturesDuration);
        void render(
            const glm::vec2& position,
            const glm::vec2& size,
            const float rotation
        ) override;
        void setState(const std::string& newState);
        void update(size_t delta);
    private:
        std::map<std::string, std::vector<std::pair<std::string, uint64_t>>> m_statesMap;
        size_t m_currentFrame = 0;
        uint64_t m_currentAnimationTime = 0;
        std::map<std::string, std::vector<std::pair<std::string, uint64_t>>>::const_iterator m_pCurrentAnimationDuration;
        mutable bool m_dirty = false;
    };

}