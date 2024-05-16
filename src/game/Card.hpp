#ifndef CARD_HPP
#define CARD_HPP

#include <SFML/Graphics.hpp>

class Card
{
public:
    Card(std::string plant_subclass_name, int price, const std::string &imagePath, float x, float y);
    void setPosition(float x, float y);
    void draw(sf::RenderWindow &window);
    sf::Sprite &getSprite();
    std::string getPlantName();
    int getPrice();

private:
    std::string m_plant_subclass_name;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    int m_price;
};

#endif // CARD_HPP
