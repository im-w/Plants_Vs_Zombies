#include "AnimatedObject.hpp"

AnimatedObject::AnimatedObject() : m_currentAnimation(nullptr)
{
}

void AnimatedObject::setPosition(float x, float y)
{
    m_sprite.setPosition(x, y);
}

void AnimatedObject::setScale(float scale_x, float scale_y)
{
    m_sprite.setScale(scale_x, scale_y);
}

sf::Sprite &AnimatedObject::getSprite()
{
    return m_sprite;
}

void AnimatedObject::setTexture(const sf::Texture &texture)
{
    m_sprite.setTexture(texture);
}

void AnimatedObject::addAnimation(const std::string &name, const Animation &animation)
{
    if (m_animations.find(name) == m_animations.end())
    {
        m_animations.insert(std::make_pair(name, animation));
        if (!m_currentAnimation)
        {
            m_currentAnimation = &m_animations.at(name);
        }
    }
}

void AnimatedObject::setCurrentAnimation(const std::string &name)
{
    auto it = m_animations.find(name);
    if (it != m_animations.end())
    {
        m_currentAnimation = &it->second;
        m_currentAnimation->stop();
    }
}

void AnimatedObject::play()
{
    if (m_currentAnimation)
    {
        m_currentAnimation->play();
    }
}

void AnimatedObject::pause()
{
    if (m_currentAnimation)
    {
        m_currentAnimation->pause();
    }
}

void AnimatedObject::stop()
{
    if (m_currentAnimation)
    {
        m_currentAnimation->stop();
    }
}

void AnimatedObject::update(sf::Time deltaTime)
{
    if (m_currentAnimation)
    {
        m_currentAnimation->update(deltaTime);
        m_sprite.setTextureRect(m_currentAnimation->getFrame());
    }
}

void AnimatedObject::draw(sf::RenderWindow &window)
{
    window.draw(m_sprite);
}

sf::Vector2f AnimatedObject::getPosition() const
{
    return m_sprite.getPosition();
}