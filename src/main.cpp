# include "./game/Game.hpp"


int main() {
    Game game;
    game.run();
    return 0;
}


// void runAnimation(sf::RenderWindow& window) {
//     window.setFramerateLimit(120);
//     // Load the photo
//     sf::Texture photoTexture;
//     if (!photoTexture.loadFromFile(PEASHOOTER_PLANT_IDLE_ANIMATION_PATH)) {
//         // Handle error loading photo
//         return;
//     }

//     FileHandler plants_csv(PLANTS_PROPERTIES_PATH);

//     // Create an instance of the AnimatedObject class
//     PeaShooter animatedObject(plants_csv);
//     animatedObject.setTexture(photoTexture);

    
    
//     // Create an instance of the Animation class
//     Animation animation;
//     animation.init(photoTexture, 620, 877, 77, 40, true);
    
//     // Add the animation to the animated object
//     animatedObject.addAnimation("idle",animation);
    
//     // Set the position of the animated object
//     animatedObject.setPosition(100, 100);

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
//         // Update animation
//         animatedObject.update(elapsedTime); // Update with appropriate delta time

//         window.clear();
//         animatedObject.draw(window);
//         window.display();
//     }
// }


// int main() {
//     sf::RenderWindow window(sf::VideoMode(1080, 1080), "Animation Example");
//     runAnimation(window);
//     return 0;
// }