#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie(int health, int speed, int damage, int timeToSpawn , int hitRate) 
    : m_health(health), m_speed(speed), m_damage(damage), m_timeToSpawn(timeToSpawn), m_hitRate(hitRate) {
}

Zombie::~Zombie() {}

void Zombie::drawHitbox(sf::RenderWindow& window) {
    window.draw(hitbox);
}

void Zombie::initHitbox() {
    // Initialize hitbox rectangle
    hitbox.setFillColor(sf::Color::Red);

    // Get the zombie sprite's global bounds
    sf::FloatRect zombieBounds = getSprite().getGlobalBounds();
    
    // Calculate the offset to center the hitbox
    float offsetX = (zombieBounds.width - 5) / 2.0f - (hitbox.getSize().x / 2.0f);
    float offsetY = (zombieBounds.height - 5) / 2.0f - (hitbox.getSize().y / 2.0f);

    // Set the size and position of the hitbox
    hitbox.setSize(sf::Vector2f(5, 5)); // Set hitbox size to 5x5px
    hitbox.setPosition(zombieBounds.left + offsetX * 10, zombieBounds.top + offsetY * 10);
}

sf::RectangleShape& Zombie::getHitbox() {
    return hitbox;
}

void Zombie::takeDamage(int damage) {
    m_health -= damage;
}

bool Zombie::isDead() {
    if (m_health <= 0) {
        return true;
    }
    return false;
}

void Zombie::stopMovementFor(sf::Time duration) {
    stopTime = duration;
    isMoving = false;
}

int Zombie::getDamage() {
    return m_damage;
}


void Zombie::move(sf::Time deltaTime) {

    if (stopTime > sf::Time::Zero) {
        stopTime -= deltaTime;
        // Optionally, you can add some visual indication that the zombie is stopped
        return; // Don't move if the stop time is active
    }
    // Move the RegularZombie horizontally from right to left based on its speed
    sf::Vector2f currentPosition = getPosition();
    float movement = m_speed * deltaTime.asSeconds();
    float newX = currentPosition.x - movement;
    setPosition(newX, currentPosition.y);

    // Update hitbox position to match the zombie's position
    sf::FloatRect zombieBounds = getSprite().getGlobalBounds();
    float offsetX = zombieBounds.width * 0.05f; // 5% of the zombie sprite width
    float offsetY = zombieBounds.height * 0.05f; // 5% of the zombie sprite height
    hitbox.setPosition(newX + offsetX * 10, currentPosition.y + offsetY * 10);
}
