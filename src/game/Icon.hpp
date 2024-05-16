#ifndef ICON_HPP
#define ICON_HPP

#include <SFML/Graphics.hpp>

class Icon
{
public:
    Icon();
    void setTexture(const sf::Texture &texture);
    void setPosition(float x, float y);
    void draw(sf::RenderWindow &window);
    void hide();
    void unhide();
    bool isHidden();
    sf::Sprite &getSprite();
    sf::Vector2f getPosition();

private:
    sf::Sprite m_sprite;
    bool m_hidden;
};

#endif // ICON_HPP
