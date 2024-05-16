#ifndef SNOWPEABULLET_HPP
#define SNOWPEABULLET_HPP

#include "Bullet.hpp"

class SnowPeaBullet : public Bullet
{
public:
    SnowPeaBullet(int bullet_speed, int bullet_damage, int m_bullet_slowDown);
    virtual ~SnowPeaBullet();
};

#endif // SNOWPEABULLET_HPP