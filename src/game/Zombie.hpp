#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include "AnimatedObject.hpp"

class Zombie : public AnimatedObject
{
protected:
    int m_health;
    int m_speed;
    int m_damage;
    int m_timeToSpawn;
    int m_hitRate;
    sf::RectangleShape hitbox;
    sf::Time stopTime;
    bool isMoving;
    sf::Time freezeTime;
    sf::Time lastHitTime;

public:
    Zombie(int health, int speed, int damage, int timeToSpawn, int hitRate);
    virtual ~Zombie();

    void move(sf::Time deltaTime);
    void drawHitbox(sf::RenderWindow &window);
    void initHitbox();
    sf::RectangleShape &getHitbox();
    void takeDamage(int damage);
    bool isDead();
    void stopMovementFor(sf::Time duration);
    int getDamage();
    void freezeFor(sf::Time duration);
    bool canHit(sf::Time elapsedTime);
    void resetLastHitTime();
};

#endif // ZOMBIE_HPP
