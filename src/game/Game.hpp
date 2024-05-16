#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cmath>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Clock.hpp>
#include <algorithm>
#include "GamePaths.hpp"
#include "Card.hpp"
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
#include "Sun.hpp"
#include "../utils/AssetManager.hpp"
#include "../utils/FileHandler.hpp"

class Game
{
public:
    Game();
    virtual ~Game(){};
    void run();

private:
    void processEvents();
    void update();
    void render();
    sf::Vector2f normalizePosition(int x, int y);
    void resizeSpriteToScreenXPercentage(sf::Sprite &sprite, float percentage, sf::RenderWindow &window);
    void createPlant(const std::string &plantSubclassName);
    void positionSpriteToMatch(sf::Sprite &newSprite, const sf::Sprite &oldSprite);
    std::unique_ptr<Zombie> createZombie(const std::string &zombieSubclassName);
    void addZombie(const std::string &zombieSubclassName, int line);
    bool spritesIntersect(const sf::Sprite &sprite1, const sf::Sprite &sprite2);
    bool spriteRectangleIntersect(const sf::Sprite &sprite, const sf::RectangleShape &rectangle);
    void playSound(const std::string soundPath);
    void textUpdated();
    void loosingMassage();
    void winMassage();
    void gameLoos(float x);
    void gameWin();
    void generateSun(int x = 0, int y = 0);
    void moveSuns();
    void setupMusic();
    void setupBackground();
    void setupCrads();
    void setupIcons();
    void updatePlants(sf::Time elapsedTime);
    void updateSuns(sf::Time elapsedTime);
    void updateZombiesInLine(sf::Time elapsedTime, std::vector<std::unique_ptr<Zombie>> &lineN_zombies);
    void updateBullets(sf::Time elapsedTime);
    void renderCards();
    void renderPlaces();
    void renderShooterPlants();
    void renderSunProducerPlants();
    void renderDefenderPlants();
    void renderZombiesInLine(std::vector<std::unique_ptr<Zombie>> &lineN_zombies);
    void renderBullets();
    void renderSuns();
    void autoSunSpawn(sf::Time elapsedTime);

    int sun_valet = 0;
    int numberOfRaiderZombies = 10;
    bool loosingStatement = false;
    bool victoryStatement = false;
    float loosingLinePosition_x = 613.333f;
    std::string selected_plant;
    sf::RenderWindow window;
    sf::ContextSettings settings;
    AssetManager assetManager;
    sf::Sprite backgroundSprite;
    sf::Sprite victoryBackground;
    sf::Sprite loosingBackground;
    sf::Sprite brainEating;
    std::vector<std::unique_ptr<Card>> cards;
    Icon select_icon;
    sf::Music music;
    sf::Music sound;
    sf::Text sunGained;
    sf::Text zombieAteYourBrain;
    sf::Text winText;
    sf::Font font;
    sf::Font zombieFont;
    sf::Font winFont;
    std::vector<std::unique_ptr<Icon>> places;
    sf::Clock clock;
    sf::Time totalTime = sf::Time::Zero;
    std::vector<std::unique_ptr<ShooterPlant>> shooterPlant_plants;
    std::vector<std::unique_ptr<SunProducerPlant>> sunProducerPlant_plants;
    std::vector<std::unique_ptr<DefenderPlant>> defenderPlant_plants;
    std::vector<std::unique_ptr<Zombie>> line1_zombies;
    std::vector<std::unique_ptr<Zombie>> line2_zombies;
    std::vector<std::unique_ptr<Zombie>> line3_zombies;
    std::vector<std::unique_ptr<Zombie>> line4_zombies;
    std::vector<std::unique_ptr<Zombie>> line5_zombies;
    std::vector<std::unique_ptr<Sun>> suns;
    std::vector<std::unique_ptr<Bullet>> bullets;
    FileHandler plants_properties;
    FileHandler zombies_properties;
    FileHandler items_properties;
    int selected_plant_price;
    int sun_generate_interval;
};

#endif // GAME_H
