#ifndef PEABULLET_HPP
#define PEABULLET_HPP

#include "Bullet.hpp"

class PeaBullet : public Bullet
{
public:
    PeaBullet(int bullet_speed, int bullet_damage);
    virtual ~PeaBullet();
};

#endif