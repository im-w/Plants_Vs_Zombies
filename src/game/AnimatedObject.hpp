#ifndef ANIMATED_OBJECT_HPP
#define ANIMATED_OBJECT_HPP

#include <SFML/Graphics.hpp>
#include "Animation.hpp"

class AnimatedObject
{
public:
    AnimatedObject();
    void setPosition(float x, float y);
    void setTexture(const sf::Texture &texture);
    void addAnimation(const std::string &name, const Animation &animation);
    void setCurrentAnimation(const std::string &name);
    void play();
    void pause();
    void stop();
    void update(sf::Time deltaTime);
    void draw(sf::RenderWindow &window);
    void setScale(float scale_x, float scale_y);
    sf::Vector2f getPosition() const;
    sf::Sprite &getSprite();

private:
    sf::Sprite m_sprite;
    std::map<std::string, Animation> m_animations;
    Animation *m_currentAnimation;
};

#endif // ANIMATED_OBJECT_HPP
