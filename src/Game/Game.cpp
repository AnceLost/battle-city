#include "Game.h"

#include "../Resources/ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/AnimatedSprite.h"
#include "Level.h"
#include "GameObjects/Tank.h"

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>


Game::Game(const glm::ivec2& windowSize)
    : m_eCurrentGameState(EGameState::Active),
    m_windowSize(windowSize)
{
	m_keys.fill(false);
}
Game::~Game()
{

}
void Game::render()
{
    if (m_pLevel)
    {
        m_pLevel->render();
    }

    if (m_pTank) 
    {
        m_pTank->render();
    }
}
void Game::update(const uint64_t delta)
{
    if (m_pLevel)
    {
        m_pLevel->update(delta);
    }
    if (m_pTank) 
    {
        if (m_keys[GLFW_KEY_W]) //�����
        {
            m_pTank->setOrientation(Tank::EOrientation::Top);
            m_pTank->move(true);
        }
        else if (m_keys[GLFW_KEY_A]) //�����
        {
            m_pTank->setOrientation(Tank::EOrientation::Left);
            m_pTank->move(true);
        }
        else if (m_keys[GLFW_KEY_D]) //������
        {
            m_pTank->setOrientation(Tank::EOrientation::Right);
            m_pTank->move(true);
        }
        else if (m_keys[GLFW_KEY_S]) //����
        {
            m_pTank->setOrientation(Tank::EOrientation::Bottom);
            m_pTank->move(true);
        }
        else
        {
            m_pTank->move(false);
        }
        m_pTank->update(delta);
    }
}
void Game::setKey(const int key, const int action)
{
	m_keys[key] = action;
}
bool Game::init()
{
    ResourceManager::loadJSONResources("res/resources.json");

    auto pSpriteShaderProgram = ResourceManager::getShaderProgram("spriteShader");
    if (!pSpriteShaderProgram) return false;

    auto pTextureAtlas = ResourceManager::getTexture("mapTextureAtlas");
    if (!pTextureAtlas) return false; 

    auto pTanksTextureAtlas = ResourceManager::getTexture("tanksTextureAtlas");
    if (!pTanksTextureAtlas) return false;

    glm::mat4 modelMatrix_1 = glm::mat4(1.f);
    modelMatrix_1 = glm::translate(modelMatrix_1, glm::vec3(100.f, 50.f, 0.f));

    glm::mat4 modelMatrix_2 = glm::mat4(1.f);
    modelMatrix_2 = glm::translate(modelMatrix_2, glm::vec3(590.f, 50.f, 0.f));

    glm::mat4 projectionMatrix = glm::ortho(
        0.f,
        static_cast<float>(m_windowSize.x),
        0.f,
        static_cast<float>(m_windowSize.y),
        -100.f,
        100.f
    );

    pSpriteShaderProgram->use();
    pSpriteShaderProgram->setInt("tex", 0);
    pSpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);

    auto pTanksAnimatedSprite = ResourceManager::getAnimatedSprite("tankAnimatedSprite");
    if (!pTanksAnimatedSprite) return false;
    pTanksAnimatedSprite->setState("tankTopState");

    m_pTank = std::make_unique<Tank>(
        pTanksAnimatedSprite,
        0.0000001f,
        glm::vec2(0),
        glm::vec2(16.f*3, 16.f*3)
    );
    m_pLevel = std::make_unique<Level>(ResourceManager::getLevels()[0]);

    return true;
}