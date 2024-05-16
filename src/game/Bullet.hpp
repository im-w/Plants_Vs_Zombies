#ifndef BULLET_HPP
#define BULLET_HPP

#include "AnimatedObject.hpp"

class Bullet : public AnimatedObject
{
protected:
    int m_bullet_speed;
    int m_bullet_damage;
    int m_bullet_slowDown;

public:
    Bullet(int bullet_speed, int bullet_damage, int bullet_slowDown);
    virtual ~Bullet();
    void move(sf::Time elapsedTime);
    int getDamage();
    int getSlowDown();
};

#endif // BULLET_HPP