#include "Zombie.hpp"

Zombie::Zombie(int health, int speed, int damage, int timeToSpawn, int hitRate)
    : m_health(health), m_speed(speed), m_damage(damage), m_timeToSpawn(timeToSpawn), m_hitRate(hitRate)
{
}

Zombie::~Zombie() {}

void Zombie::drawHitbox(sf::RenderWindow &window)
{
    window.draw(hitbox);
}

void Zombie::initHitbox()
{
    hitbox.setFillColor(sf::Color::Red);
    sf::FloatRect zombieBounds = getSprite().getGlobalBounds();
    float offsetX = (zombieBounds.width - 5) / 2.0f - (hitbox.getSize().x / 2.0f);
    float offsetY = (zombieBounds.height - 5) / 2.0f - (hitbox.getSize().y / 2.0f);
    hitbox.setSize(sf::Vector2f(5, 5));
    hitbox.setPosition(zombieBounds.left + offsetX * 10, zombieBounds.top + offsetY * 10);
}

sf::RectangleShape &Zombie::getHitbox()
{
    return hitbox;
}

void Zombie::takeDamage(int damage)
{
    m_health -= damage;
}

bool Zombie::isDead()
{
    if (m_health <= 0)
    {
        return true;
    }
    return false;
}

void Zombie::stopMovementFor(sf::Time duration)
{
    stopTime = duration;
    isMoving = false;
}

int Zombie::getDamage()
{
    return m_damage;
}

void Zombie::move(sf::Time deltaTime)
{
    int speed = m_speed;
    if (freezeTime > sf::Time::Zero)
    {
        speed = m_speed / 2;
        freezeTime -= deltaTime;
    }

    if (stopTime > sf::Time::Zero)
    {
        stopTime -= deltaTime;
        return;
    }
    sf::Vector2f currentPosition = getPosition();
    float movement = speed * deltaTime.asSeconds();
    float newX = currentPosition.x - movement;
    setPosition(newX, currentPosition.y);
    sf::FloatRect zombieBounds = getSprite().getGlobalBounds();
    float offsetX = zombieBounds.width * 0.05f;
    float offsetY = zombieBounds.height * 0.05f;
    hitbox.setPosition(newX + offsetX * 10, currentPosition.y + offsetY * 10);
}

void Zombie::freezeFor(sf::Time duration)
{
    freezeTime += duration;
}

bool Zombie::canHit(sf::Time elapsedTime)
{
    sf::Time elapsedSinceLastHit = elapsedTime - lastHitTime;
    if (elapsedSinceLastHit >= sf::seconds(m_hitRate))
    {
        return true;
    }
    return false;
}

void Zombie::resetLastHitTime()
{
    lastHitTime = sf::Time::Zero;
}