#ifndef BULLET_HPP
#define BULLET_HPP

#include "AnimatedObject.hpp"

class Bullet : public AnimatedObject {
protected:
    int m_bullet_speed;
    int m_bullet_damage;

public:
    Bullet(int bullet_speed, int bullet_damage);
    virtual ~Bullet();
    // Add any necessary methods and members
    void move(sf::Time elapsedTime);
    int getDamage();
};

#endif // BULLET_HPP