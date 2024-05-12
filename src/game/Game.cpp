#include "Game.hpp"


// Constructor
Game::Game() : window(sf::VideoMode::getFullscreenModes()[0], "Plants vs. Zombies", sf::Style::Fullscreen)
, plants_properties(PLANTS_PROPERTIES_PATH) , zombies_properties(ZOMBIES_PROPERTIES_PATH) , items_properties(ITEMS_PROPERTIES_PATH) {
    window.setFramerateLimit(30);

    assetManager.LoadTexture("background", BACKGROUND_IMAGE_PATH);
    backgroundSprite.setTexture(assetManager.GetTexture("background"));


    // Scale the sprite to fit the window
    sf::Vector2u textureSize = backgroundSprite.getTexture()->getSize();
    sf::Vector2u windowSize = window.getSize();
    backgroundSprite.setScale(
        static_cast<double>(windowSize.x) / textureSize.x,
        static_cast<double>(windowSize.y) / textureSize.y
    );

    // Initialize cards
    // Add the cards to the vector
    sf::Vector2f new_card_position = normalizePosition(-95, -80);
    cards.push_back(std::make_unique<Card>("SunFlower",SUNFLOWER_CARD_IMAGE_PATH, new_card_position.x, new_card_position.y));
    new_card_position = normalizePosition(-95, -45);
    cards.push_back(std::make_unique<Card>("PeaShooter",PEA_SHOOTER_CARD_IMAGE_PATH, new_card_position.x, new_card_position.y));
    new_card_position = normalizePosition(-95, -10);
    cards.push_back(std::make_unique<Card>("SnowPea",SNOW_PEA_SHOOTER_CARD_IMAGE_PATH, new_card_position.x, new_card_position.y));
    new_card_position = normalizePosition(-95, 25);
    cards.push_back(std::make_unique<Card>("MelonPlut",MELON_PLUT_CARD_IMAGE_PATH, new_card_position.x, new_card_position.y));
    new_card_position = normalizePosition(-95, 60);
    cards.push_back(std::make_unique<Card>("WallNut",WALL_NUT_CARD_IMAGE_PATH, new_card_position.x, new_card_position.y));

    // Resize the sprites of the cards
    for(auto& card : cards) {
        resizeSpriteToScreenXPercentage(card->getSprite(), 5.5, window);
    }

    // Load select_icon texture
    assetManager.LoadTexture("select_icon", SELECT_ICON_IMAGE_PATH);
    select_icon.setTexture(assetManager.GetTexture("select_icon"));
    resizeSpriteToScreenXPercentage(select_icon.getSprite(), 5.5, window);

    // Hide the select_icon at the start
    select_icon.hide();

    assetManager.LoadTexture("place_plant_icon", PLACE_PLANT_ICON_IMAGE_PATH);  // Load the texture for placement spots

    // Initialize and position the placement icons
    places.resize(45);  // Resize vector to hold 45 icons
    for (int i = 0; i < 45; ++i) {
        places[i] = std::make_unique<Icon>();  // Create a new unique_ptr<Icon> for each place
        places[i]->setTexture(assetManager.GetTexture("place_plant_icon"));

        // Calculate and set the position of each place icon
        int row = i / 9;  // 5 rows if 45/9 icons per row
        int col = i % 9;
        sf::Vector2f position = normalizePosition(-23 + 12.7 * col, -60 + 27 * row);  // Example positions
        places[i]->setPosition(position.x, position.y);
        resizeSpriteToScreenXPercentage(places[i]->getSprite(), 6, window);  // Adjust size to fit the screen
    }

}


// Game loop
void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

// Process events
void Game::processEvents() {
    sf::Event event;
    sf::Vector2f mousePosition; // Move declaration outside the switch statement
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::MouseMoved:
                // Hide all icons initially
                for (auto& place : places) {
                    place->hide();
                }

                // Check if the mouse is over any icon and show it
                mousePosition = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
                for (auto& place : places) {
                    if (place->getSprite().getGlobalBounds().contains(mousePosition) && select_icon.isHidden()==false) {
                        place->unhide();
                        break;  // Only show the first icon found under the cursor
                    }
                }
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    mousePosition = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                    bool iconToggled = false;  // Flag to check if an icon was toggled

                    for (auto& card : cards) {
                        if (card->getSprite().getGlobalBounds().contains(mousePosition)) {
                            sf::Vector2f cardPosition = card->getSprite().getPosition();

                            // Check if the select_icon is already visible and at this card's position
                            if (!select_icon.isHidden() && select_icon.getSprite().getPosition() == cardPosition) {
                                select_icon.hide();  // Hide the icon if it's already showing on this card
                                selected_plant = "";
                                iconToggled = true;
                                break;  // Exit the loop as the icon has been toggled
                            } else {
                                // Set select_icon position to the clicked card's position and show it
                                select_icon.setPosition(cardPosition.x, cardPosition.y);
                                select_icon.unhide();
                                selected_plant = card->getPlantName();
                                iconToggled = true;
                                break;  // Exit the loop as the icon has been toggled
                            }
                        }
                    }

                    for (auto& place : places) {
                        if (place->getSprite().getGlobalBounds().contains(mousePosition)) {
                            if (selected_plant != "") {
                                addPlant(selected_plant);
                                //scaleSpriteToMatch(plants.back()->getSprite(),place->getSprite());
                                positionSpriteToMatch(plants.back()->getSprite(),place->getSprite());
                                selected_plant = "";

                            }
                        }
                    }

                    // If no card was clicked or the icon was not toggled, hide the select_icon
                    if (!iconToggled) {
                        select_icon.hide();
                    }
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
void Game::update() {
    sf::Time elapsedTime = clock.restart();
    for (auto& plant : plants) {
        plant->update(elapsedTime);
    }
}

// Render the game
void Game::render() {
    window.clear();
    window.draw(backgroundSprite);
    for (auto& card : cards) {
        card->draw(window);
    }
    for (auto& place : places) {
        place->draw(window);  // Draw each placement icon
    }
    for (auto& plant : plants) {
        plant->draw(window); // Draw each plant
        drawSpriteDebugOutline(window,plant->getSprite());
    }
    select_icon.draw(window);
    window.display();
}

sf::Vector2f Game::normalizePosition(int x, int y) {
    // Get the size of the background texture
    sf::FloatRect textureSize = backgroundSprite.getGlobalBounds();

    // Convert input range [-100, 100] to [0, textureSize]
    float newX = (x + 100) / 200.0f * textureSize.width;
    float newY = (y + 100) / 200.0f * textureSize.height;

    return sf::Vector2f(newX, newY);
}
void Game::resizeSpriteToScreenXPercentage(sf::Sprite& sprite, float percentage, sf::RenderWindow& window) {
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

std::unique_ptr<Plant> Game::createPlant(const std::string& plantSubclassName) {
    if (plantSubclassName == "PeaShooter") {
        assetManager.LoadTexture("pea_shooter_idle_animation", PEASHOOTER_PLANT_IDLE_ANIMATION_PATH);
        assetManager.LoadAnimation("pea_shooter_idle_animation", PEASHOOTER_PLANT_IDLE_ANIMATION_PATH, 620, 877, 77, 40, true);

        auto peashooter = std::make_unique<PeaShooter>(plants_properties);
        peashooter->setTexture(assetManager.GetTexture("pea_shooter_idle_animation"));
        peashooter->addAnimation("idle", assetManager.GetAnimation("pea_shooter_idle_animation"));
        peashooter->getSprite().setScale(0.13,0.13);
        return peashooter;
    } else if (plantSubclassName == "SunFlower") {
        assetManager.LoadTexture("sunflower_idle_animation", SUNFLOWER_PLANT_IDLE_ANIMATION_PATH);
        assetManager.LoadAnimation("sunflower_idle_animation", SUNFLOWER_PLANT_IDLE_ANIMATION_PATH, 620, 877, 54, 50, true);

        auto sunflower = std::make_unique<SunFlower>(plants_properties);
        sunflower->setTexture(assetManager.GetTexture("sunflower_idle_animation"));
        sunflower->addAnimation("idle", assetManager.GetAnimation("sunflower_idle_animation"));
        sunflower->getSprite().setScale(0.15,0.15);
        return sunflower;
    } else if (plantSubclassName == "SnowPea") {
        assetManager.LoadTexture("snowpea_idle_animation", SNOW_PEA_PLANT_IDLE_ANIMATION_PATH);
        assetManager.LoadAnimation("snowpea_idle_animation", SNOW_PEA_PLANT_IDLE_ANIMATION_PATH, 620, 877, 20, 100, true);

        auto snowPea = std::make_unique<SnowPea>(plants_properties);
        snowPea->setTexture(assetManager.GetTexture("snowpea_idle_animation"));
        snowPea->addAnimation("idle", assetManager.GetAnimation("snowpea_idle_animation"));
        snowPea->getSprite().setScale(0.15,0.15);
        return snowPea;
    } else if (plantSubclassName == "WallNut") {
        assetManager.LoadTexture("wallnut_idle_animation", WALL_NUT_PLANT_IDLE_ANIMATION_PATH);
        assetManager.LoadAnimation("wallnut_idle_animation", WALL_NUT_PLANT_IDLE_ANIMATION_PATH, 620, 877, 16, 250, true);

        auto wallNut = std::make_unique<WallNut>(plants_properties);
        wallNut->setTexture(assetManager.GetTexture("wallnut_idle_animation"));
        wallNut->addAnimation("idle", assetManager.GetAnimation("wallnut_idle_animation"));
        wallNut->getSprite().setScale(0.15,0.15);
        return wallNut;
    } else if (plantSubclassName == "MelonPlut") {
        assetManager.LoadTexture("melonpult_idle_animation", MELON_PLUT_PLANT_IDLE_ANIMATION_PATH);
        assetManager.LoadAnimation("melonpult_idle_animation", MELON_PLUT_PLANT_IDLE_ANIMATION_PATH, 270, 290, 18, 100, true);

        auto melonPult = std::make_unique<MelonPlut>(plants_properties);
        melonPult->setTexture(assetManager.GetTexture("melonpult_idle_animation"));
        melonPult->addAnimation("idle", assetManager.GetAnimation("melonpult_idle_animation"));
        melonPult->getSprite().setScale(0.4,0.4);
        return melonPult;
    } else {
        // Handle unknown plant subclass
        return nullptr;
    }
}


void Game::addPlant(const std::string& plantSubclassName) {
    std::unique_ptr<Plant> newPlant = createPlant(plantSubclassName);
    if (newPlant) {
        plants.push_back(std::move(newPlant));
    } else {
        // Handle failure to create plant
        std::cout << "Failed to create plant of subclass: " << plantSubclassName << std::endl;
    }
}

void Game::scaleSpriteToMatch(sf::Sprite& newSprite, const sf::Sprite& oldSprite) {
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

void Game::positionSpriteToMatch(sf::Sprite& newSprite, const sf::Sprite& oldSprite) {
    // Get the global position of the old sprite
    sf::Vector2f oldPosition = oldSprite.getPosition();

    // Set the position of the new sprite to match the position of the old sprite
    newSprite.setPosition(oldPosition);
}

void Game::drawSpriteDebugOutline(sf::RenderWindow& window, const sf::Sprite& sprite) {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    sf::RectangleShape outline(sf::Vector2f(bounds.width, bounds.height));
    outline.setPosition(bounds.left, bounds.top);
    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineColor(sf::Color::Red);
    outline.setOutlineThickness(2.0f);
    window.draw(outline);
}