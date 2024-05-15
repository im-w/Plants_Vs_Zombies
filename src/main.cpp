# include "./game/Game.hpp"





int main() {
    Game game;
    game.run();
    return 0;
}


// void runAnimation(sf::RenderWindow& window) {
//     window.setFramerateLimit(120);
    
//     AssetManager assetManager;
//     FileHandler plants_properties(ZOMBIES_PROPERTIES_PATH);




//     // Create an instance of the Animation class and load animation
//     assetManager.LoadTexture("pea_shooter_idle_animation", REGULAR_ZOMBIE_WALKING_ANIMATION_PATH);
//     assetManager.LoadAnimation("pea_shooter_idle_animation", REGULAR_ZOMBIE_WALKING_ANIMATION_PATH, 620, 877, 12, 100, true);
    
//     // Create a vector to hold PeaShooter instances
//     std::vector<std::unique_ptr<Zombie>> plants;

//     // Create PeaShooter instance
//     auto peashooter = std::make_unique<RegularZombie>(plants_properties);
//     peashooter->setTexture(assetManager.GetTexture("pea_shooter_idle_animation"));
//     peashooter->addAnimation("idle", assetManager.GetAnimation("pea_shooter_idle_animation"));
//     peashooter->setPosition(100, 100);
//     peashooter->initHitbox();

//     // Add PeaShooter to the vector
//     plants.push_back(std::move(peashooter));

//     sf::Clock clock;

//     // Game loop
//     while (window.isOpen()) {
//         sf::Event event;
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed) {
//                 window.close();
//             }
//         }
//         sf::Time elapsedTime = clock.restart();
        
//         // Update all plants' animations
//         for (auto& plant : plants) {
//             plant->update(elapsedTime); // Update with appropriate delta time
//         }

//         window.clear();
        
//         // Draw all plants
//         for (auto& plant : plants) {
//             plant->draw(window);
//             plant->drawHitbox(window);

//         }
        
//         window.display();
//     }
// }


// int main() {
//     sf::RenderWindow window(sf::VideoMode(1080, 1080), "Animation Example");
//     runAnimation(window);
//     return 0;
// }

// #include "./game/MelonPlut.hpp" // Include the header file for MelonPlut instead of PeaShooter

// void runAnimation(sf::RenderWindow& window) {
//     window.setFramerateLimit(120);
    
//     AssetManager assetManager;
//     FileHandler plants_properties(PLANTS_PROPERTIES_PATH);

//     // Load the photo texture
//     sf::Texture photoTexture;
//     if (!photoTexture.loadFromFile(MELON_PLUT_PLANT_IDLE_ANIMATION_PATH)) {
//         // Handle error loading photo
//         return;
//     }

//     // Create an instance of the Animation class and load animation
//     assetManager.LoadTexture("melonplut_idle_animation", MELON_PLUT_PLANT_IDLE_ANIMATION_PATH);
//     assetManager.LoadAnimation("melonplut_idle_animation", MELON_PLUT_PLANT_IDLE_ANIMATION_PATH, 270, 289, 18, 100, true);
    
//     // Create a vector to hold MelonPlut instances
//     std::vector<std::unique_ptr<Plant>> plants;

//     // Create MelonPlut instance
//     auto melonplut = std::make_unique<MelonPlut>(plants_properties);
//     melonplut->setTexture(assetManager.GetTexture("melonplut_idle_animation"));
//     melonplut->addAnimation("idle", assetManager.GetAnimation("melonplut_idle_animation"));
//     melonplut->setPosition(100, 100);

//     // Add MelonPlut to the vector
//     plants.push_back(std::move(melonplut));

//     sf::Clock clock;

//     // Game loop
//     while (window.isOpen()) {
//         sf::Event event;
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed) {
//                 window.close();
//             }
//         }
//         sf::Time elapsedTime = clock.restart();
        
//         // Update all plants' animations
//         for (auto& plant : plants) {
//             plant->update(elapsedTime); // Update with appropriate delta time
//         }

//         window.clear();
        
//         // Draw all plants
//         for (auto& plant : plants) {
//             plant->draw(window);
//         }
        
//         window.display();
//     }
// }


// int main() {
//     sf::RenderWindow window(sf::VideoMode(1080, 1080), "Animation Example");
//     runAnimation(window);
//     return 0;
// }
