#ifndef GAME_H
#define GAME_H

#include <iostream> // for testing code
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "GamePaths.hpp"
#include "../utils/AssetManager.hpp"
#include "../utils/FileHandler.hpp"
#include "Card.hpp"  // Include the Card class
#include "Icon.hpp"
#include "AnimatedObject.hpp"
#include "Plant.hpp"
#include "PeaShooter.hpp"



class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();
    sf::Vector2f normalizePosition(int x, int y);
    void resizeSpriteToScreenXPercentage(sf::Sprite& sprite, float percentage, sf::RenderWindow& window);
    std::unique_ptr<Plant> createPlant(const std::string& plantSubclassName);
    void addPlant(const std::string& plantSubclassName);

    int sunPoints;
    sf::RenderWindow window;
    sf::ContextSettings settings;
    AssetManager assetManager;
    sf::Sprite backgroundSprite;
    std::vector<std::unique_ptr<Card>> cards;  // Vector to store cards
    Icon select_icon;
    std::vector<Icon> places;  // Vector to store plant placement icons
    sf::Clock clock;
    std::vector<std::unique_ptr<Plant>> plants;
    FileHandler plants_properties;
    FileHandler zombies_properties;
    FileHandler items_properties;


};

#endif // GAME_H