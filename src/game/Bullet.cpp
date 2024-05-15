#include "Bullet.hpp"

Bullet::Bullet(int bullet_speed,int bullet_damage)  : m_bullet_speed(bullet_speed) , m_bullet_damage(bullet_damage) {
    // Initialize bullet properties
}

Bullet::~Bullet() {
    // Cleanup
}

void Bullet::move(sf::Time elapsedTime) {
    // Convert elapsed time to seconds
    float deltaTime = elapsedTime.asSeconds();

    // Move the bullet horizontally based on its speed
    sf::Vector2f currentPosition = getPosition();
    float newX = currentPosition.x + (m_bullet_speed * deltaTime);
    setPosition(newX, currentPosition.y);
}

int Bullet::getDamage() {
    return m_bullet_damage;
}