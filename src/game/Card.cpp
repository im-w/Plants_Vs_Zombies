#include "Card.hpp"

Card::Card(std::string plant_subclass_name, const std::string &imagePath, float x, float y)
{
    if (!m_texture.loadFromFile(imagePath))
    {
        throw std::runtime_error("Failed to load image at " + imagePath);
    }
    m_sprite.setTexture(m_texture);
    setPosition(x, y);
    m_plant_subclass_name = plant_subclass_name;
}

void Card::setPosition(float x, float y)
{
    m_sprite.setPosition(x, y);
}

void Card::draw(sf::RenderWindow &window)
{
    window.draw(m_sprite);
}

sf::Sprite &Card::getSprite()
{
    return m_sprite;
}

std::string Card::getPlantName()
{
    return m_plant_subclass_name;
}