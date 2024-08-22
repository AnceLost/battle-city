#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>

#include <memory>
#include <string>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

namespace RenderEngine {

    class Texture2D;
    class ShaderProgram;

    class Sprite {
	public:
        Sprite(
            const std::shared_ptr<Texture2D> pTexture,
            const std::string initialSubTexture,
            const std::shared_ptr<ShaderProgram> pShaderProgram
        );

        ~Sprite();

        Sprite(const Sprite&) = delete;
        Sprite& operator=(const Sprite&) = delete;

        virtual void render(
            const glm::vec2& position, 
            const glm::vec2& size, 
            const float rotation
        );

    protected:
        std::shared_ptr<Texture2D> m_pTexture;
        std::shared_ptr<ShaderProgram> m_pShaderProgram;
        GLuint m_VAO;

        VertexArray m_vertexArray;
        VertexBuffer m_vertexCoordsBuffer;
        VertexBuffer m_textureCoordsBuffer;
        IndexBuffer m_indexBuffer;
};

}