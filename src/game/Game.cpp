#include "Game.hpp"

// Constructor
Game::Game() : window(sf::VideoMode(1920, 1080), "Plants vs. Zombies", sf::Style::Default), plants_properties(PLANTS_PROPERTIES_PATH), zombies_properties(ZOMBIES_PROPERTIES_PATH), items_properties(ITEMS_PROPERTIES_PATH)
{
    window.setFramerateLimit(60);
    music.openFromFile(MAIN_MUSIC_PLATGROUND_PATH);
    music.setLoop(true);
    music.play();

    assetManager.LoadTexture("background", BACKGROUND_IMAGE_PATH);
    backgroundSprite.setTexture(assetManager.GetTexture("background"));

    // Scale the sprite to fit the window
    sf::Vector2u textureSize = backgroundSprite.getTexture()->getSize();
    sf::Vector2u windowSize = window.getSize();
    backgroundSprite.setScale(
        static_cast<double>(windowSize.x) / textureSize.x,
        static_cast<double>(windowSize.y) / textureSize.y);

    // Initialize cards
    // Add the cards to the vector
    sf::Vector2f new_card_position = normalizePosition(-95, -98);
    cards.push_back(std::make_unique<Card>("SunFlower", SUNFLOWER_CARD_IMAGE_PATH, new_card_position.x, new_card_position.y));
    new_card_position = normalizePosition(-95, -63);
    cards.push_back(std::make_unique<Card>("PeaShooter", PEA_SHOOTER_CARD_IMAGE_PATH, new_card_position.x, new_card_position.y));
    new_card_position = normalizePosition(-95, -28);
    cards.push_back(std::make_unique<Card>("SnowPea", SNOW_PEA_SHOOTER_CARD_IMAGE_PATH, new_card_position.x, new_card_position.y));
    new_card_position = normalizePosition(-95, 7);
    cards.push_back(std::make_unique<Card>("WallNut", WALL_NUT_CARD_IMAGE_PATH, new_card_position.x, new_card_position.y));
    new_card_position = normalizePosition(-83, -99);
    auto sunBank = std::make_unique<Card>("bank", SUN_BANK_IMAGE_PATH, new_card_position.x, new_card_position.y);
    sunBank->getSprite().setScale(0.8, 0.7);

    // Resize the sprites of the cards
    for (auto &card : cards)
    {
        resizeSpriteToScreenXPercentage(card->getSprite(), 5.5, window);
    }
    cards.push_back(std::move(sunBank));

    // Load select_icon texture
    assetManager.LoadTexture("select_icon", SELECT_ICON_IMAGE_PATH);
    select_icon.setTexture(assetManager.GetTexture("select_icon"));
    resizeSpriteToScreenXPercentage(select_icon.getSprite(), 5.5, window);

    // Hide the select_icon at the start
    select_icon.hide();

    assetManager.LoadTexture("place_plant_icon", PLACE_PLANT_ICON_IMAGE_PATH); // Load the texture for placement spots

    // Initialize and position the placement icons
    places.resize(45); // Resize vector to hold 45 icons
    for (int i = 0; i < 45; ++i)
    {
        places[i] = std::make_unique<Icon>(); // Create a new unique_ptr<Icon> for each place
        places[i]->setTexture(assetManager.GetTexture("place_plant_icon"));

        // Calculate and set the position of each place icon
        int row = i / 9; // 5 rows if 45/9 icons per row
        int col = i % 9;
        sf::Vector2f position = normalizePosition(-23 + 12.7 * col, -60 + 27 * row); // Example positions
        places[i]->setPosition(position.x, position.y);
        resizeSpriteToScreenXPercentage(places[i]->getSprite(), 6, window); // Adjust size to fit the screen
    }

    addZombie("RegularZombie", 2);
    addZombie("BucketHeadZombie", 1);
    addZombie("Gargantuar", 3);
    addZombie("RegularZombie", 5);
    generateSun();
}

// Game loop
void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

// Process events
void Game::processEvents()
{
    sf::Event event;
    sf::Vector2f mousePosition; // Move declaration outside the switch statement
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::MouseMoved:
            // Hide all icons initially
            for (auto &place : places)
            {
                place->hide();
            }

            // Check if the mouse is over any icon and show it
            mousePosition = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
            for (auto &place : places)
            {
                if (place->getSprite().getGlobalBounds().contains(mousePosition) && select_icon.isHidden() == false)
                {
                    place->unhide();
                    break; // Only show the first icon found under the cursor
                }
            }
            break;
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                mousePosition = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                bool iconToggled = false; // Flag to check if an icon was toggled

                for (auto &card : cards)
                {
                    if (card->getSprite().getGlobalBounds().contains(mousePosition))
                    {
                        sf::Vector2f cardPosition = card->getSprite().getPosition();

                        // Check if the select_icon is already visible and at this card's position
                        if (!select_icon.isHidden() && select_icon.getSprite().getPosition() == cardPosition)
                        {
                            select_icon.hide(); // Hide the icon if it's already showing on this card
                            selected_plant = "";
                            iconToggled = true;
                            break; // Exit the loop as the icon has been toggled
                        }
                        else
                        {
                            // Set select_icon position to the clicked card's position and show it
                            select_icon.setPosition(cardPosition.x, cardPosition.y);
                            select_icon.unhide();
                            selected_plant = card->getPlantName();
                            iconToggled = true;
                            break; // Exit the loop as the icon has been toggled
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
                            // scaleSpriteToMatch(plants.back()->getSprite(),place->getSprite());
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

                // If no card was clicked or the icon was not toggled, hide the select_icon
                if (!iconToggled)
                {
                    select_icon.hide();
                }
            }
            else if (event.mouseButton.button == sf::Mouse::Right)
            {
                // Print the position of the right-click
                mousePosition = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                std::cout << "Right-clicked at position: (" << mousePosition.x << ", " << mousePosition.y << ")" << std::endl;
            }
            break;
        case sf::Event::Closed:
            window.close();
            break;
        default:
            // Handle other event types as needed
            break;
        }
    }
}

// Update game state
void Game::update()
{
    sf::Time elapsedTime = clock.restart();

    // Update plants
    for (auto &plant : shooterPlant_plants)
    {
        plant->update(elapsedTime);
        plant->increaseTimeSinceLastShot(elapsedTime); // Increase time since last shot for each plant
        if (plant->canShoot())
        { // Check if plant can shoot based on its hit rate
            if (plant->zombieInRange(line1_zombies) || plant->zombieInRange(line2_zombies) || plant->zombieInRange(line3_zombies) || plant->zombieInRange(line4_zombies) || plant->zombieInRange(line5_zombies))
            {
                playSound(PLANT_SHOOTING_SOUND_PATH);
                plant->shoot(bullets, assetManager);
                plant->resetTimeSinceLastShot(); // Reset time since last shot after shooting
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

    for (auto &sun : suns)
    {
        sun->update(elapsedTime);
    }

    // Update zombies
    for (auto &zombie : line1_zombies)
    {
        zombie->update(elapsedTime);
        zombie->move(elapsedTime);
        for (auto &bullet : bullets)
        {
            if (spriteRectangleIntersect(bullet->getSprite(), zombie->getHitbox()))
            {
                playSound(SPLAT_SOUND_PATH);
                zombie->takeDamage(bullet->getDamage());
                bullets.erase(std::remove(bullets.begin(), bullets.end(), bullet), bullets.end());
                break;
            }
        }
        for (auto &plant : shooterPlant_plants)
        {
            if (spriteRectangleIntersect(plant->getSprite(), zombie->getHitbox()))
            {
                zombie->stopMovementFor(sf::seconds(1));
                playSound(ZOMBIE_EATING_SOUND_PATH);
                plant->takeDamage(zombie->getDamage());
            }
        }
        for (auto &plant : sunProducerPlant_plants)
        {
            if (spriteRectangleIntersect(plant->getSprite(), zombie->getHitbox()))
            {
                zombie->stopMovementFor(sf::seconds(1));
                playSound(ZOMBIE_EATING_SOUND_PATH);
                plant->takeDamage(zombie->getDamage());
            }
        }
        for (auto &plant : defenderPlant_plants)
        {
            if (spriteRectangleIntersect(plant->getSprite(), zombie->getHitbox()))
            {
                zombie->stopMovementFor(sf::seconds(1));
                playSound(ZOMBIE_EATING_SOUND_PATH);
                plant->takeDamage(zombie->getDamage());
            }
        }
    }
    for (auto &zombie : line2_zombies)
    {
        zombie->update(elapsedTime);
        zombie->move(elapsedTime);
        for (auto &bullet : bullets)
        {
            if (spriteRectangleIntersect(bullet->getSprite(), zombie->getHitbox()))
            {
                playSound(SPLAT_SOUND_PATH);
                zombie->takeDamage(bullet->getDamage());
                bullets.erase(std::remove(bullets.begin(), bullets.end(), bullet), bullets.end());
                break;
            }
        }
        for (auto &plant : shooterPlant_plants)
        {
            if (spriteRectangleIntersect(plant->getSprite(), zombie->getHitbox()))
            {
                zombie->stopMovementFor(sf::seconds(1));
                playSound(ZOMBIE_EATING_SOUND_PATH);
                plant->takeDamage(zombie->getDamage());
            }
        }
        for (auto &plant : sunProducerPlant_plants)
        {
            if (spriteRectangleIntersect(plant->getSprite(), zombie->getHitbox()))
            {
                zombie->stopMovementFor(sf::seconds(1));
                playSound(ZOMBIE_EATING_SOUND_PATH);
                plant->takeDamage(zombie->getDamage());
            }
        }
        for (auto &plant : defenderPlant_plants)
        {
            if (spriteRectangleIntersect(plant->getSprite(), zombie->getHitbox()))
            {
                zombie->stopMovementFor(sf::seconds(1));
                playSound(ZOMBIE_EATING_SOUND_PATH);
                plant->takeDamage(zombie->getDamage());
            }
        }
    }
    for (auto &zombie : line3_zombies)
    {
        zombie->update(elapsedTime);
        zombie->move(elapsedTime);
        for (auto &bullet : bullets)
        {
            if (spriteRectangleIntersect(bullet->getSprite(), zombie->getHitbox()))
            {
                playSound(SPLAT_SOUND_PATH);
                zombie->takeDamage(bullet->getDamage());
                bullets.erase(std::remove(bullets.begin(), bullets.end(), bullet), bullets.end());
                break;
            }
        }
        for (auto &plant : shooterPlant_plants)
        {
            if (spriteRectangleIntersect(plant->getSprite(), zombie->getHitbox()))
            {
                zombie->stopMovementFor(sf::seconds(1));
                playSound(ZOMBIE_EATING_SOUND_PATH);
                plant->takeDamage(zombie->getDamage());
            }
        }
        for (auto &plant : sunProducerPlant_plants)
        {
            if (spriteRectangleIntersect(plant->getSprite(), zombie->getHitbox()))
            {
                zombie->stopMovementFor(sf::seconds(1));
                playSound(ZOMBIE_EATING_SOUND_PATH);
                plant->takeDamage(zombie->getDamage());
            }
        }
        for (auto &plant : defenderPlant_plants)
        {
            if (spriteRectangleIntersect(plant->getSprite(), zombie->getHitbox()))
            {
                zombie->stopMovementFor(sf::seconds(1));
                playSound(ZOMBIE_EATING_SOUND_PATH);
                plant->takeDamage(zombie->getDamage());
            }
        }
    }
    for (auto &zombie : line4_zombies)
    {
        zombie->update(elapsedTime);
        zombie->move(elapsedTime);
        for (auto &bullet : bullets)
        {
            if (spriteRectangleIntersect(bullet->getSprite(), zombie->getHitbox()))
            {
                playSound(SPLAT_SOUND_PATH);
                zombie->takeDamage(bullet->getDamage());
                bullets.erase(std::remove(bullets.begin(), bullets.end(), bullet), bullets.end());
                break;
            }
        }
        for (auto &plant : shooterPlant_plants)
        {
            if (spriteRectangleIntersect(plant->getSprite(), zombie->getHitbox()))
            {
                zombie->stopMovementFor(sf::seconds(1));
                playSound(ZOMBIE_EATING_SOUND_PATH);
                plant->takeDamage(zombie->getDamage());
            }
        }
        for (auto &plant : sunProducerPlant_plants)
        {
            if (spriteRectangleIntersect(plant->getSprite(), zombie->getHitbox()))
            {
                zombie->stopMovementFor(sf::seconds(1));
                playSound(ZOMBIE_EATING_SOUND_PATH);
                plant->takeDamage(zombie->getDamage());
            }
        }
        for (auto &plant : defenderPlant_plants)
        {
            if (spriteRectangleIntersect(plant->getSprite(), zombie->getHitbox()))
            {
                zombie->stopMovementFor(sf::seconds(1));
                playSound(ZOMBIE_EATING_SOUND_PATH);
                plant->takeDamage(zombie->getDamage());
            }
        }
    }
    for (auto &zombie : line5_zombies)
    {
        zombie->update(elapsedTime);
        zombie->move(elapsedTime);
        for (auto &bullet : bullets)
        {
            if (spriteRectangleIntersect(bullet->getSprite(), zombie->getHitbox()))
            {
                playSound(SPLAT_SOUND_PATH);
                zombie->takeDamage(bullet->getDamage());
                bullets.erase(std::remove(bullets.begin(), bullets.end(), bullet), bullets.end());
                break;
            }
        }
        for (auto &plant : shooterPlant_plants)
        {
            if (spriteRectangleIntersect(plant->getSprite(), zombie->getHitbox()))
            {
                zombie->stopMovementFor(sf::seconds(1));
                playSound(ZOMBIE_EATING_SOUND_PATH);
                plant->takeDamage(zombie->getDamage());
            }
        }
        for (auto &plant : sunProducerPlant_plants)
        {
            if (spriteRectangleIntersect(plant->getSprite(), zombie->getHitbox()))
            {
                zombie->stopMovementFor(sf::seconds(1));
                playSound(ZOMBIE_EATING_SOUND_PATH);
                plant->takeDamage(zombie->getDamage());
            }
        }
        for (auto &plant : defenderPlant_plants)
        {
            if (spriteRectangleIntersect(plant->getSprite(), zombie->getHitbox()))
            {
                zombie->stopMovementFor(sf::seconds(1));
                playSound(ZOMBIE_EATING_SOUND_PATH);
                plant->takeDamage(zombie->getDamage());
            }
        }
    }
    for (auto &bullet : bullets)
    {
        bullet->update(elapsedTime);
        bullet->move(elapsedTime);
    }
}

// Render the game
void Game::render()
{
    window.clear();
    window.draw(backgroundSprite);
    for (auto &card : cards)
    {
        card->draw(window);
    }
    for (auto &place : places)
    {
        place->draw(window); // Draw each placement icon
    }
    for (auto &zombie : line1_zombies)
    {
        zombie->draw(window);
        zombie->drawHitbox(window);
        drawSpriteDebugOutline(window, zombie->getSprite());
        if (zombie->isDead())
        {
            line1_zombies.erase(std::remove(line1_zombies.begin(), line1_zombies.end(), zombie), line1_zombies.end());
        }
    }
    for (auto &zombie : line2_zombies)
    {
        zombie->draw(window);
        zombie->drawHitbox(window);
        drawSpriteDebugOutline(window, zombie->getSprite());
        if (zombie->isDead())
        {
            line2_zombies.erase(std::remove(line2_zombies.begin(), line2_zombies.end(), zombie), line2_zombies.end());
        }
    }
    for (auto &zombie : line3_zombies)
    {
        zombie->draw(window);
        zombie->drawHitbox(window);
        drawSpriteDebugOutline(window, zombie->getSprite());
        if (zombie->isDead())
        {
            line3_zombies.erase(std::remove(line3_zombies.begin(), line3_zombies.end(), zombie), line3_zombies.end());
        }
    }
    for (auto &zombie : line4_zombies)
    {
        zombie->draw(window);
        zombie->drawHitbox(window);
        drawSpriteDebugOutline(window, zombie->getSprite());
        if (zombie->isDead())
        {
            line4_zombies.erase(std::remove(line4_zombies.begin(), line4_zombies.end(), zombie), line4_zombies.end());
        }
    }
    for (auto &zombie : line5_zombies)
    {
        zombie->draw(window);
        zombie->drawHitbox(window);
        drawSpriteDebugOutline(window, zombie->getSprite());
        if (zombie->isDead())
        {
            line5_zombies.erase(std::remove(line5_zombies.begin(), line5_zombies.end(), zombie), line5_zombies.end());
        }
    }
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
    for (auto &plant : shooterPlant_plants)
    {
        plant->draw(window);
        drawSpriteDebugOutline(window, plant->getSprite());
        if (plant->isDead())
        {
            shooterPlant_plants.erase(std::remove(shooterPlant_plants.begin(), shooterPlant_plants.end(), plant), shooterPlant_plants.end());
        }
    }
    for (auto &plant : sunProducerPlant_plants)
    {
        plant->draw(window);
        drawSpriteDebugOutline(window, plant->getSprite());
        if (plant->isDead())
        {
            sunProducerPlant_plants.erase(std::remove(sunProducerPlant_plants.begin(), sunProducerPlant_plants.end(), plant), sunProducerPlant_plants.end());
        }
    }
    for (auto &plant : defenderPlant_plants)
    {
        plant->draw(window);
        drawSpriteDebugOutline(window, plant->getSprite());
        if (plant->isDead())
        {
            defenderPlant_plants.erase(std::remove(defenderPlant_plants.begin(), defenderPlant_plants.end(), plant), defenderPlant_plants.end());
        }
    }

    textUpdated();
    window.draw(sunGained);
    moveSuns();
    for (auto &sun : suns)
    {
        sun->draw(window);
    }

    select_icon.draw(window);
    window.display();
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
        // Handle font loading failure
    }
    sf::Vector2f sunGainedPosition = normalizePosition(-65, -97);
    sunGained.setPosition(sunGainedPosition);
    sunGained.setString(std::to_string(sun_valet));
    sunGained.setFont(font);
    sunGained.setFillColor(sf::Color::Black);
    sunGained.setCharacterSize(60);
}

int generateRandomNumber(int Min, int Max) // Generate a number in a range of numbers
{
    srand(static_cast<unsigned int>(time(nullptr)));
    return rand() % (Max - Min + 1) + Min;
}

sf::Vector2f Game::normalizePosition(int x, int y)
{
    // Get the size of the background texture
    sf::FloatRect textureSize = backgroundSprite.getGlobalBounds();

    // Convert input range [-100, 100] to [0, textureSize]
    float newX = (x + 100) / 200.0f * textureSize.width;
    float newY = (y + 100) / 200.0f * textureSize.height;

    return sf::Vector2f(newX, newY);
}
void Game::resizeSpriteToScreenXPercentage(sf::Sprite &sprite, float percentage, sf::RenderWindow &window)
{
    // Get the current size of the sprite
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();

    // Calculate the new size
    float newWidth = window.getSize().x * percentage / 100;

    // Calculate the scale factors
    float scaleX = newWidth / spriteBounds.width;
    float scaleY = newWidth / spriteBounds.width;

    // Set the scale
    sprite.setScale(scaleX, scaleY);
}

void Game::generateSun(int x , int y)
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
        if ((sun.get()->MoveStatus) && (sun->getSprite().getPosition().y < sun.get()->bottom)) // Object reached the bottom
        {
            sun->getSprite().move(movement);
        }
        if (sun->getSprite().getPosition().y > sun.get()->bottom)
        {
            sun.get()->MoveStatus = false;
        }
    }
}

void Game::createPlant(const std::string &plantSubclassName)
{
    playSound(IMPLANT_SOUND_PATH);
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
        // Handle unknown plant subclass
        return;
    }
}

std::unique_ptr<Zombie> Game::createZombie(const std::string &zombieSubclassName)
{
    if (zombieSubclassName == "RegularZombie")
    {
        assetManager.LoadTexture("regular_zombie_walking_animation", REGULAR_ZOMBIE_WALKING_ANIMATION_PATH);
        assetManager.LoadAnimation("regular_zombie_walking_animation", REGULAR_ZOMBIE_WALKING_ANIMATION_PATH, 620, 877, 15, 174, true);

        auto regularZombie = std::make_unique<RegularZombie>(zombies_properties);
        regularZombie->setTexture(assetManager.GetTexture("regular_zombie_walking_animation"));
        regularZombie->addAnimation("walking", assetManager.GetAnimation("regular_zombie_walking_animation"));
        regularZombie->getSprite().setScale(0.3, 0.3);
        regularZombie->initHitbox();
        playSound(ZOMBIE_INTERVAL_SOUND_PATH);
        return regularZombie;
    }
    else if (zombieSubclassName == "BucketHeadZombie")
    {
        assetManager.LoadTexture("buckethead_zombie_walking_animation", BUCKETHEAD_ZOMBIE_WALKING_ANIMATION_PATH);
        assetManager.LoadAnimation("buckethead_zombie_walking_animation", BUCKETHEAD_ZOMBIE_WALKING_ANIMATION_PATH, 620, 877, 14, 140, true);

        auto bucketHeadZombie = std::make_unique<BucketHeadZombie>(zombies_properties);
        bucketHeadZombie->setTexture(assetManager.GetTexture("buckethead_zombie_walking_animation"));
        bucketHeadZombie->addAnimation("walking", assetManager.GetAnimation("buckethead_zombie_walking_animation"));
        bucketHeadZombie->getSprite().setScale(0.3, 0.3);
        bucketHeadZombie->initHitbox();
        playSound(ZOMBIE_INTERVAL_SOUND_PATH);
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
        // Handle unknown zombie subclass
        return nullptr;
    }
}

void Game::addZombie(const std::string &zombieSubclassName, int line)
{
    std::unique_ptr<Zombie> newZombie = createZombie(zombieSubclassName);
    if (newZombie)
    {
        // Add the zombie to the corresponding line vector
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
        // Handle failure to create zombie
        std::cout << "Failed to create zombie of subclass: " << zombieSubclassName << std::endl;
    }
}

void Game::scaleSpriteToMatch(sf::Sprite &newSprite, const sf::Sprite &oldSprite)
{
    // Get the global bounds of the old sprite
    sf::FloatRect oldBounds = oldSprite.getGlobalBounds();

    // Get the global bounds of the new sprite
    sf::FloatRect newBounds = newSprite.getGlobalBounds();

    // Calculate the scale factors to match the size of the old sprite
    float scaleX = oldBounds.width / newBounds.width;
    float scaleY = oldBounds.height / newBounds.height;

    std::cout << "oldBounds.width" << scaleX << "scaleY" << scaleY << std::endl;
    std::cout << "scaleX" << scaleX << "scaleY" << scaleY << std::endl;

    // Apply the scale factors to the new sprite
    newSprite.setScale(scaleY, scaleY);
}

void Game::positionSpriteToMatch(sf::Sprite &newSprite, const sf::Sprite &oldSprite)
{
    // Get the global position of the old sprite
    sf::Vector2f oldPosition = oldSprite.getPosition();

    // Set the position of the new sprite to match the position of the old sprite
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
    // Get the global bounds of the sprites
    sf::FloatRect bounds1 = sprite1.getGlobalBounds();
    sf::FloatRect bounds2 = sprite2.getGlobalBounds();

    // Check if the bounds intersect
    return bounds1.intersects(bounds2);
}

bool Game::spriteRectangleIntersect(const sf::Sprite &sprite, const sf::RectangleShape &rectangle)
{
    // Get the global bounds of the sprite and the rectangle
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();
    sf::FloatRect rectBounds = rectangle.getGlobalBounds();

    // Check if the bounds intersect
    return spriteBounds.intersects(rectBounds);
}
