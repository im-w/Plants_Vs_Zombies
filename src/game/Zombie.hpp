#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include "AnimatedObject.hpp"

class Zombie : public AnimatedObject {
protected:
    int m_health;
    int m_speed;
    int m_damage;
    int m_timeToSpawn;
    int m_hitRate;
    sf::RectangleShape hitbox; // New rectangle for hitbox
    sf::Time stopTime; // Time for which the zombie should stop moving
    bool isMoving; // Flag to indicate if the zombie is currently moving

public:
    Zombie(int health, int speed, int damage, int timeToSpawn, int hitRate);
    virtual ~Zombie();

    void move(sf::Time deltaTime);
    void drawHitbox(sf::RenderWindow& window);
    void initHitbox();
    sf::RectangleShape& getHitbox();
    void takeDamage(int damage);
    bool isDead();
    // Function to stop the zombie's movement for a specified duration
    void stopMovementFor(sf::Time duration);
    int getDamage();
};

#endif // ZOMBIE_HPP
