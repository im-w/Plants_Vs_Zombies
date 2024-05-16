#include "Bullet.hpp"

Bullet::Bullet(int bullet_speed, int bullet_damage, int bullet_slowDown) : m_bullet_speed(bullet_speed), m_bullet_damage(bullet_damage), m_bullet_slowDown(bullet_slowDown)
{
}

Bullet::~Bullet()
{
}

void Bullet::move(sf::Time elapsedTime)
{
    float deltaTime = elapsedTime.asSeconds();
    sf::Vector2f currentPosition = getPosition();
    float newX = currentPosition.x + (m_bullet_speed * deltaTime);
    setPosition(newX, currentPosition.y);
}

int Bullet::getDamage()
{
    return m_bullet_damage;
}

int Bullet::getSlowDown()
{
    return m_bullet_slowDown;
}