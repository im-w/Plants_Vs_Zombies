#include "Icon.hpp"

Icon::Icon() : m_hidden(false) {
}

void Icon::setTexture(const sf::Texture& texture) {
    m_sprite.setTexture(texture);
}

void Icon::setPosition(float x, float y) {
    m_sprite.setPosition(x, y);
}

void Icon::draw(sf::RenderWindow& window) {
    if (!m_hidden) {
        window.draw(m_sprite);
    }
}

void Icon::hide() {
    m_hidden = true;
}

void Icon::unhide() {
    m_hidden = false;
}

sf::Sprite& Icon::getSprite() {
    return m_sprite;
}

bool Icon::isHidden() {
    return m_hidden;
}

sf::Vector2f Icon::getPosition() {
    return m_sprite.getPosition();
}