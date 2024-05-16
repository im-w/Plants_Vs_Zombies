#include "Game.hpp"

Game::Game() : window(sf::VideoMode(1920, 1080), "Plants vs. Zombies", sf::Style::Default), plants_properties(PLANTS_PROPERTIES_PATH), zombies_properties(ZOMBIES_PROPERTIES_PATH), items_properties(ITEMS_PROPERTIES_PATH)
{
    window.setFramerateLimit(60);
    setupMusic();
    setupBackground();
    setupCrads();
    setupIcons();

    addZombie("RegularZombie", 2);
    addZombie("BucketHeadZombie", 1);
    addZombie("Gargantuar", 3);
    addZombie("RegularZombie", 5);
    generateSun();
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    sf::Vector2f mousePosition;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::MouseMoved:
            for (auto &place : places)
            {
                place->hide();
            }
            mousePosition = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
            for (auto &place : places)
            {
                if (place->getSprite().getGlobalBounds().contains(mousePosition) && select_icon.isHidden() == false)
                {
                    place->unhide();
                    break;
                }
            }
            break;
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                mousePosition = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                bool iconToggled = false;
                for (auto &card : cards)
                {
                    if (card->getSprite().getGlobalBounds().contains(mousePosition))
                    {
                        sf::Vector2f cardPosition = card->getSprite().getPosition();
                        if (!select_icon.isHidden() && select_icon.getSprite().getPosition() == cardPosition)
                        {
                            select_icon.hide();
                            selected_plant = "";
                            iconToggled = true;
                            break;
                        }
                        else
                        {
                            select_icon.setPosition(cardPosition.x, cardPosition.y);
                            select_icon.unhide();
                            selected_plant = card->getPlantName();
                            iconToggled = true;
                            break;
                        }
                    }
                }

                for (auto &place : places)
                {
                    if (place->getSprite().getGlobalBounds().contains(mousePosition))
                    {
                        if (selected_plant != "")
                        {
                            createPlant(selected_plant);
                            if (selected_plant == "PeaShooter" || selected_plant == "SnowPea")
                            {
                                positionSpriteToMatch(shooterPlant_plants.back()->getSprite(), place->getSprite());
                            }
                            else if (selected_plant == "SunFlower")
                            {
                                positionSpriteToMatch(sunProducerPlant_plants.back()->getSprite(), place->getSprite());
                            }
                            else if (selected_plant == "WallNut")
                            {
                                positionSpriteToMatch(defenderPlant_plants.back()->getSprite(), place->getSprite());
                            }
                            selected_plant = "";
                        }
                    }
                }

                for (auto sun = suns.begin(); sun != suns.end();)
                {
                    if (sun->get()->getSprite().getGlobalBounds().contains(mousePosition))
                    {
                        sun_valet += std::stoi(items_properties.getData("sun", "value"));
                        sun = suns.erase(sun);
                    }
                    else
                    {
                        ++sun;
                    }
                }
                if (!iconToggled)
                {
                    select_icon.hide();
                }
            }
            else if (event.mouseButton.button == sf::Mouse::Right)
            {
                mousePosition = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                std::cout << "Right-clicked at position: (" << mousePosition.x << ", " << mousePosition.y << ")" << std::endl;
            }
            break;
        case sf::Event::Closed:
            window.close();
            break;
        default:
            break;
        }
    }
}

void Game::update()
{
    sf::Time elapsedTime = clock.restart();
    updatePlants(elapsedTime);
    updateSuns(elapsedTime);
    updateZombiesInLine(elapsedTime, line1_zombies);
    updateZombiesInLine(elapsedTime, line2_zombies);
    updateZombiesInLine(elapsedTime, line3_zombies);
    updateZombiesInLine(elapsedTime, line4_zombies);
    updateZombiesInLine(elapsedTime, line5_zombies);
    updateBullets(elapsedTime);
}

void Game::render()
{
    window.clear();
    window.draw(backgroundSprite);
    renderCards();
    renderPlaces();
    renderShooterPlants();
    renderSunProducerPlants();
    renderDefenderPlants();
    renderZombiesInLine(line1_zombies);
    renderZombiesInLine(line2_zombies);
    renderZombiesInLine(line3_zombies);
    renderZombiesInLine(line4_zombies);
    renderZombiesInLine(line5_zombies);
    renderBullets();
    textUpdated();
    window.draw(sunGained);
    renderSuns();
    select_icon.draw(window);
    window.display();
}

sf::Vector2f Game::normalizePosition(int x, int y)
{
    sf::FloatRect textureSize = backgroundSprite.getGlobalBounds();
    float newX = (x + 100) / 200.0f * textureSize.width;
    float newY = (y + 100) / 200.0f * textureSize.height;

    return sf::Vector2f(newX, newY);
}
void Game::resizeSpriteToScreenXPercentage(sf::Sprite &sprite, float percentage, sf::RenderWindow &window)
{
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();
    float newWidth = window.getSize().x * percentage / 100;
    float scaleX = newWidth / spriteBounds.width;
    float scaleY = newWidth / spriteBounds.width;
    sprite.setScale(scaleX, scaleY);
}

void Game::createPlant(const std::string &plantSubclassName)
{
    if (plantSubclassName == "PeaShooter")
    {
        assetManager.LoadTexture("pea_shooter_idle_animation", PEASHOOTER_PLANT_IDLE_ANIMATION_PATH);
        assetManager.LoadAnimation("pea_shooter_idle_animation", PEASHOOTER_PLANT_IDLE_ANIMATION_PATH, 620, 877, 77, 40, true);
        auto peashooter = std::make_unique<PeaShooter>(plants_properties);
        peashooter->setTexture(assetManager.GetTexture("pea_shooter_idle_animation"));
        peashooter->addAnimation("idle", assetManager.GetAnimation("pea_shooter_idle_animation"));
        peashooter->getSprite().setScale(0.13, 0.13);
        shooterPlant_plants.push_back(std::move(peashooter));
        return;
    }
    else if (plantSubclassName == "SunFlower")
    {
        assetManager.LoadTexture("sunflower_idle_animation", SUNFLOWER_PLANT_IDLE_ANIMATION_PATH);
        assetManager.LoadAnimation("sunflower_idle_animation", SUNFLOWER_PLANT_IDLE_ANIMATION_PATH, 620, 877, 54, 50, true);
        auto sunflower = std::make_unique<SunFlower>(plants_properties);
        sunflower->setTexture(assetManager.GetTexture("sunflower_idle_animation"));
        sunflower->addAnimation("idle", assetManager.GetAnimation("sunflower_idle_animation"));
        sunflower->getSprite().setScale(0.15, 0.15);
        sunProducerPlant_plants.push_back(std::move(sunflower));
        return;
    }
    else if (plantSubclassName == "SnowPea")
    {
        assetManager.LoadTexture("snowpea_idle_animation", SNOW_PEA_PLANT_IDLE_ANIMATION_PATH);
        assetManager.LoadAnimation("snowpea_idle_animation", SNOW_PEA_PLANT_IDLE_ANIMATION_PATH, 620, 877, 20, 100, true);
        auto snowPea = std::make_unique<SnowPea>(plants_properties);
        snowPea->setTexture(assetManager.GetTexture("snowpea_idle_animation"));
        snowPea->addAnimation("idle", assetManager.GetAnimation("snowpea_idle_animation"));
        snowPea->getSprite().setScale(0.15, 0.15);
        shooterPlant_plants.push_back(std::move(snowPea));
        return;
    }
    else if (plantSubclassName == "WallNut")
    {
        assetManager.LoadTexture("wallnut_idle_animation", WALL_NUT_PLANT_IDLE_ANIMATION_PATH);
        assetManager.LoadAnimation("wallnut_idle_animation", WALL_NUT_PLANT_IDLE_ANIMATION_PATH, 620, 877, 16, 250, true);
        auto wallNut = std::make_unique<WallNut>(plants_properties);
        wallNut->setTexture(assetManager.GetTexture("wallnut_idle_animation"));
        wallNut->addAnimation("idle", assetManager.GetAnimation("wallnut_idle_animation"));
        wallNut->getSprite().setScale(0.15, 0.15);
        defenderPlant_plants.push_back(std::move(wallNut));
        return;
    }
    else
    {
        return;
    }
}

std::unique_ptr<Zombie> Game::createZombie(const std::string &zombieSubclassName)
{
    if (zombieSubclassName == "RegularZombie")
    {
        playSound(GARGANTUAR_INTERVAL_SOUND_PATH);
        assetManager.LoadTexture("regular_zombie_walking_animation", REGULAR_ZOMBIE_WALKING_ANIMATION_PATH);
        assetManager.LoadAnimation("regular_zombie_walking_animation", REGULAR_ZOMBIE_WALKING_ANIMATION_PATH, 620, 877, 15, 174, true);
        auto regularZombie = std::make_unique<RegularZombie>(zombies_properties);
        regularZombie->setTexture(assetManager.GetTexture("regular_zombie_walking_animation"));
        regularZombie->addAnimation("walking", assetManager.GetAnimation("regular_zombie_walking_animation"));
        regularZombie->getSprite().setScale(0.3, 0.3);
        regularZombie->initHitbox();
        return regularZombie;
    }
    else if (zombieSubclassName == "BucketHeadZombie")
    {
        playSound(GARGANTUAR_INTERVAL_SOUND_PATH);
        assetManager.LoadTexture("buckethead_zombie_walking_animation", BUCKETHEAD_ZOMBIE_WALKING_ANIMATION_PATH);
        assetManager.LoadAnimation("buckethead_zombie_walking_animation", BUCKETHEAD_ZOMBIE_WALKING_ANIMATION_PATH, 620, 877, 14, 140, true);
        auto bucketHeadZombie = std::make_unique<BucketHeadZombie>(zombies_properties);
        bucketHeadZombie->setTexture(assetManager.GetTexture("buckethead_zombie_walking_animation"));
        bucketHeadZombie->addAnimation("walking", assetManager.GetAnimation("buckethead_zombie_walking_animation"));
        bucketHeadZombie->getSprite().setScale(0.3, 0.3);
        bucketHeadZombie->initHitbox();
        return bucketHeadZombie;
    }
    else if (zombieSubclassName == "Gargantuar")
    {
        playSound(GARGANTUAR_INTERVAL_SOUND_PATH);
        assetManager.LoadTexture("gargantuar_zombie_walking_animation", GARGANTUAR_ZOMBIE_WALKING_ANIMATION_PATH);
        assetManager.LoadAnimation("gargantuar_zombie_walking_animation", GARGANTUAR_ZOMBIE_WALKING_ANIMATION_PATH, 600, 800, 48, 70, true);
        auto gargantuarZombie = std::make_unique<Gargantuar>(zombies_properties);
        gargantuarZombie->setTexture(assetManager.GetTexture("gargantuar_zombie_walking_animation"));
        gargantuarZombie->addAnimation("walking", assetManager.GetAnimation("gargantuar_zombie_walking_animation"));
        gargantuarZombie->getSprite().setScale(0.3, 0.3);
        gargantuarZombie->initHitbox();
        return gargantuarZombie;
    }
    else
    {
        return nullptr;
    }
}

void Game::addZombie(const std::string &zombieSubclassName, int line)
{
    std::unique_ptr<Zombie> newZombie = createZombie(zombieSubclassName);
    if (newZombie)
    {
        switch (line)
        {
        case 1:
            newZombie->setPosition(1920, 87);
            line1_zombies.push_back(std::move(newZombie));
            break;
        case 2:
            newZombie->setPosition(1920, 245);
            line2_zombies.push_back(std::move(newZombie));
            break;
        case 3:
            newZombie->setPosition(1920, 361);
            line3_zombies.push_back(std::move(newZombie));
            break;
        case 4:
            newZombie->setPosition(1920, 493);
            line4_zombies.push_back(std::move(newZombie));
            break;
        case 5:
            newZombie->setPosition(1920, 630);
            line5_zombies.push_back(std::move(newZombie));
            break;
        default:
            std::cout << "Invalid line number: " << line << std::endl;
            break;
        }
    }
    else
    {
        std::cout << "Failed to create zombie of subclass: " << zombieSubclassName << std::endl;
    }
}

void Game::scaleSpriteToMatch(sf::Sprite &newSprite, const sf::Sprite &oldSprite)
{
    sf::FloatRect oldBounds = oldSprite.getGlobalBounds();
    sf::FloatRect newBounds = newSprite.getGlobalBounds();
    float scaleX = oldBounds.width / newBounds.width;
    float scaleY = oldBounds.height / newBounds.height;
    std::cout << "oldBounds.width" << scaleX << "scaleY" << scaleY << std::endl;
    std::cout << "scaleX" << scaleX << "scaleY" << scaleY << std::endl;
    newSprite.setScale(scaleY, scaleY);
}

void Game::positionSpriteToMatch(sf::Sprite &newSprite, const sf::Sprite &oldSprite)
{
    sf::Vector2f oldPosition = oldSprite.getPosition();
    newSprite.setPosition(oldPosition);
}

void Game::drawSpriteDebugOutline(sf::RenderWindow &window, const sf::Sprite &sprite)
{
    sf::FloatRect bounds = sprite.getGlobalBounds();
    sf::RectangleShape outline(sf::Vector2f(bounds.width, bounds.height));
    outline.setPosition(bounds.left, bounds.top);
    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineColor(sf::Color::Red);
    outline.setOutlineThickness(2.0f);
    window.draw(outline);
}

bool Game::spritesIntersect(const sf::Sprite &sprite1, const sf::Sprite &sprite2)
{
    sf::FloatRect bounds1 = sprite1.getGlobalBounds();
    sf::FloatRect bounds2 = sprite2.getGlobalBounds();
    return bounds1.intersects(bounds2);
}

bool Game::spriteRectangleIntersect(const sf::Sprite &sprite, const sf::RectangleShape &rectangle)
{
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();
    sf::FloatRect rectBounds = rectangle.getGlobalBounds();
    return spriteBounds.intersects(rectBounds);
}

void Game::playSound(const std::string sound_path)
{
    sound.openFromFile(sound_path);
    sound.play();
}

void Game::textUpdated()
{
    if (!font.loadFromFile(UI_FONT_PATH))
    {
        std::cerr << "Error loading font file!" << std::endl;
    }
    sf::Vector2f sunGainedPosition = normalizePosition(-65, -97);
    sunGained.setPosition(sunGainedPosition);
    sunGained.setString(std::to_string(sun_valet));
    sunGained.setFont(font);
    sunGained.setFillColor(sf::Color::Black);
    sunGained.setCharacterSize(60);
}

int generateRandomNumber(int Min, int Max)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    return rand() % (Max - Min + 1) + Min;
}

void Game::generateSun(int x, int y)
{
    assetManager.LoadTexture("Sun_Idle_Animation", SUN_ITEM_MOVING_ANIMATION_PATH);
    assetManager.LoadAnimation("Sun_Idle_Animation", SUN_ITEM_MOVING_ANIMATION_PATH, 1240, 1420, 12, 170, true);
    auto sun = std::make_unique<Sun>(items_properties);
    sun->setTexture(assetManager.GetTexture("Sun_Idle_Animation"));
    sun->addAnimation("Falling", assetManager.GetAnimation("Sun_Idle_Animation"));
    if (x == 0)
    {
        x = generateRandomNumber(-25, 75);
    }
    sf::Vector2f newPosition = normalizePosition(x, -110);
    sun->getSprite().setPosition(newPosition.x, newPosition.y);
    sun->getSprite().setScale(0.07, 0.07);
    sf::Vector2f bottomPosition = normalizePosition(0, generateRandomNumber(-5, 55));
    sun.get()->bottom = bottomPosition.y;
    suns.push_back(std::move(sun));
}

void Game::moveSuns()
{
    sf::Time deltaTime = clock.restart();
    float dtSeconds = deltaTime.asSeconds() * 15;
    sf::Vector2f movement(0, 10 * dtSeconds);
    for (auto &sun : suns)
    {
        if ((sun.get()->MoveStatus) && (sun->getSprite().getPosition().y < sun.get()->bottom))
        {
            sun->getSprite().move(movement);
        }
        if (sun->getSprite().getPosition().y > sun.get()->bottom)
        {
            sun.get()->MoveStatus = false;
        }
    }
}

void Game::setupMusic()
{
    music.openFromFile(MAIN_MUSIC_PLAYGROUND_PATH);
    music.setLoop(true);
    music.play();
}

void Game::setupBackground()
{
    assetManager.LoadTexture("background", BACKGROUND_IMAGE_PATH);
    backgroundSprite.setTexture(assetManager.GetTexture("background"));
    sf::Vector2u textureSize = backgroundSprite.getTexture()->getSize();
    sf::Vector2u windowSize = window.getSize();
    backgroundSprite.setScale(
        static_cast<double>(windowSize.x) / textureSize.x,
        static_cast<double>(windowSize.y) / textureSize.y);
}

void Game::setupCrads()
{
    sf::Vector2f new_card_position = normalizePosition(-95, -80);
    cards.push_back(std::make_unique<Card>("SunFlower", SUNFLOWER_CARD_IMAGE_PATH, new_card_position.x, new_card_position.y));
    new_card_position = normalizePosition(-95, -45);
    cards.push_back(std::make_unique<Card>("PeaShooter", PEA_SHOOTER_CARD_IMAGE_PATH, new_card_position.x, new_card_position.y));
    new_card_position = normalizePosition(-95, -10);
    cards.push_back(std::make_unique<Card>("SnowPea", SNOW_PEA_SHOOTER_CARD_IMAGE_PATH, new_card_position.x, new_card_position.y));
    new_card_position = normalizePosition(-95, 25);
    cards.push_back(std::make_unique<Card>("WallNut", WALL_NUT_CARD_IMAGE_PATH, new_card_position.x, new_card_position.y));
    new_card_position = normalizePosition(-83, -99);
    auto sunBank = std::make_unique<Card>("bank", SUN_BANK_IMAGE_PATH, new_card_position.x, new_card_position.y);
    sunBank->getSprite().setScale(0.8, 0.7);

    for (auto &card : cards)
    {
        resizeSpriteToScreenXPercentage(card->getSprite(), 5.5, window);
    }
    cards.push_back(std::move(sunBank));
}

void Game::setupIcons()
{
    assetManager.LoadTexture("select_icon", SELECT_ICON_IMAGE_PATH);
    select_icon.setTexture(assetManager.GetTexture("select_icon"));
    resizeSpriteToScreenXPercentage(select_icon.getSprite(), 5.5, window);
    select_icon.hide();

    assetManager.LoadTexture("place_plant_icon", PLACE_PLANT_ICON_IMAGE_PATH);
    places.resize(45);
    for (int i = 0; i < 45; ++i)
    {
        places[i] = std::make_unique<Icon>();
        places[i]->setTexture(assetManager.GetTexture("place_plant_icon"));
        int row = i / 9;
        int col = i % 9;
        sf::Vector2f position = normalizePosition(-23 + 12.7 * col, -60 + 27 * row);
        places[i]->setPosition(position.x, position.y);
        resizeSpriteToScreenXPercentage(places[i]->getSprite(), 6, window);
    }
}

void Game::updatePlants(sf::Time elapsedTime)
{
    for (auto &plant : shooterPlant_plants)
    {
        plant->update(elapsedTime);
        plant->increaseTimeSinceLastShot(elapsedTime);
        if (plant->canShoot())
        {
            if (plant->zombieInRange(line1_zombies) || plant->zombieInRange(line2_zombies) || plant->zombieInRange(line3_zombies) || plant->zombieInRange(line4_zombies) || plant->zombieInRange(line5_zombies))
            {
                playSound(PLANT_SHOOTING_SOUND_PATH);
                plant->shoot(bullets, assetManager);
                plant->resetTimeSinceLastShot();
            }
        }
    }
    for (auto &plant : sunProducerPlant_plants)
    {
        plant->update(elapsedTime);
    }
    for (auto &plant : defenderPlant_plants)
    {
        plant->update(elapsedTime);
    }
}

void Game::updateSuns(sf::Time elapsedTime)
{
    for (auto &sun : suns)
    {
        sun->update(elapsedTime);
    }
}

void Game::updateZombiesInLine(sf::Time elapsedTime, std::vector<std::unique_ptr<Zombie>> &lineN_zombies)
{
    for (auto &zombie : lineN_zombies)
    {
        zombie->update(elapsedTime);
        zombie->move(elapsedTime);
        for (auto &bullet : bullets)
        {
            if (spriteRectangleIntersect(bullet->getSprite(), zombie->getHitbox()))
            {
                playSound(SPLAT_SOUND_PATH);
                zombie->takeDamage(bullet->getDamage());
                zombie->freezeFor(sf::seconds(bullet->getSlowDown()));
                bullets.erase(std::remove(bullets.begin(), bullets.end(), bullet), bullets.end());
                break;
            }
        }
        for (auto &plant : shooterPlant_plants)
        {
            if (spriteRectangleIntersect(plant->getSprite(), zombie->getHitbox()))
            {
                playSound(ZOMBIE_EATING_SOUND_PATH);
                zombie->stopMovementFor(sf::seconds(1));
                if (zombie->canHit(elapsedTime))
                {
                    plant->takeDamage(zombie->getDamage());
                    zombie->resetLastHitTime();
                }
                break;
            }
        }
        for (auto &plant : sunProducerPlant_plants)
        {
            if (spriteRectangleIntersect(plant->getSprite(), zombie->getHitbox()))
            {
                playSound(ZOMBIE_EATING_SOUND_PATH);
                zombie->stopMovementFor(sf::seconds(1));
                if (zombie->canHit(elapsedTime))
                {
                    plant->takeDamage(zombie->getDamage());
                    zombie->resetLastHitTime();
                }
                break;
            }
        }
        for (auto &plant : defenderPlant_plants)
        {
            if (spriteRectangleIntersect(plant->getSprite(), zombie->getHitbox()))
            {
                playSound(ZOMBIE_EATING_SOUND_PATH);
                zombie->stopMovementFor(sf::seconds(1));
                if (zombie->canHit(elapsedTime))
                {
                    plant->takeDamage(zombie->getDamage());
                    zombie->resetLastHitTime();
                }
                break;
            }
        }
    }
}

void Game::updateBullets(sf::Time elapsedTime)
{
    for (auto &bullet : bullets)
    {
        bullet->update(elapsedTime);
        bullet->move(elapsedTime);
    }
}

void Game::renderCards()
{
    for (auto &card : cards)
    {
        card->draw(window);
    }
}

void Game::renderPlaces()
{
    for (auto &place : places)
    {
        place->draw(window);
    }
}

void Game::renderShooterPlants()
{
    for (auto &plant : shooterPlant_plants)
    {
        plant->draw(window);
        drawSpriteDebugOutline(window, plant->getSprite());
        if (plant->isDead())
        {
            shooterPlant_plants.erase(std::remove(shooterPlant_plants.begin(), shooterPlant_plants.end(), plant), shooterPlant_plants.end());
        }
    }
}

void Game::renderSunProducerPlants()
{
    for (auto &plant : sunProducerPlant_plants)
    {
        plant->draw(window);
        drawSpriteDebugOutline(window, plant->getSprite());
        if (plant->isDead())
        {
            sunProducerPlant_plants.erase(std::remove(sunProducerPlant_plants.begin(), sunProducerPlant_plants.end(), plant), sunProducerPlant_plants.end());
        }
    }
}

void Game::renderDefenderPlants()
{
    for (auto &plant : defenderPlant_plants)
    {
        plant->draw(window);
        drawSpriteDebugOutline(window, plant->getSprite());
        if (plant->isDead())
        {
            defenderPlant_plants.erase(std::remove(defenderPlant_plants.begin(), defenderPlant_plants.end(), plant), defenderPlant_plants.end());
        }
    }
}

void Game::renderZombiesInLine(std::vector<std::unique_ptr<Zombie>> &lineN_zombies)
{
    for (auto &zombie : lineN_zombies)
    {
        zombie->draw(window);
        zombie->drawHitbox(window);
        drawSpriteDebugOutline(window, zombie->getSprite());
        if (zombie->isDead())
        {
            lineN_zombies.erase(std::remove(line1_zombies.begin(), line1_zombies.end(), zombie), line1_zombies.end());
        }
    }
}

void Game::renderBullets()
{
    for (auto &bullet : bullets)
    {
        bullet->draw(window);
        drawSpriteDebugOutline(window, bullet->getSprite());
        if (bullet->getPosition().x > window.getSize().x)
        {
            bullets.erase(std::remove(bullets.begin(), bullets.end(), bullet), bullets.end());
            break;
        }
    }
}

void Game::renderSuns()
{
    moveSuns();
    for (auto &sun : suns)
    {
        sun->draw(window);
    }
}