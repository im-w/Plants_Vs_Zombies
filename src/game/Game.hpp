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
#include "SnowPea.hpp"
#include "WallNut.hpp"
#include "MelonPlut.hpp"
#include "SunFlower.hpp"
#include "Zombie.hpp"
#include "RegularZombie.hpp"
#include "BucketHeadZombie.hpp"
#include "Gargantuar.hpp"
#include "Bullet.hpp"






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
    void createPlant(const std::string& plantSubclassName);
    std::string selected_plant; // Store the name of the selected plant
    void scaleSpriteToMatch(sf::Sprite& newSprite, const sf::Sprite& oldSprite);
    void positionSpriteToMatch(sf::Sprite& newSprite, const sf::Sprite& oldSprite);
    void drawSpriteDebugOutline(sf::RenderWindow& window, const sf::Sprite& sprite);
    std::unique_ptr<Zombie> createZombie(const std::string& zombieSubclassName);
    void addZombie(const std::string& zombieSubclassName, int line);
    bool spritesIntersect(const sf::Sprite& sprite1, const sf::Sprite& sprite2);
    bool spriteRectangleIntersect(const sf::Sprite& sprite, const sf::RectangleShape& rectangle);

    int sun_valet = 0;
    sf::RenderWindow window;
    sf::ContextSettings settings;
    AssetManager assetManager;
    sf::Sprite backgroundSprite;
    std::vector<std::unique_ptr<Card>> cards;  // Vector to store cards
    Icon select_icon;
    std::vector<std::unique_ptr<Icon>> places;  // Vector to store plant placement icons
    sf::Clock clock;
    std::vector<std::unique_ptr<ShooterPlant>> shooterPlant_plants;
    std::vector<std::unique_ptr<SunProducerPlant>> sunProducerPlant_plants;
    std::vector<std::unique_ptr<DefenderPlant>> defenderPlant_plants;
    std::vector<std::unique_ptr<Zombie>> line1_zombies;
    std::vector<std::unique_ptr<Zombie>> line2_zombies;
    std::vector<std::unique_ptr<Zombie>> line3_zombies;
    std::vector<std::unique_ptr<Zombie>> line4_zombies;
    std::vector<std::unique_ptr<Zombie>> line5_zombies;
    std::vector<std::unique_ptr<Bullet>> bullets;
    FileHandler plants_properties;
    FileHandler zombies_properties;
    FileHandler items_properties;

};

#endif // GAME_H