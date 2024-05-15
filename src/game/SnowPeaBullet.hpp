#ifndef SNOWPEABULLET_HPP
#define SNOWPEABULLET_HPP

#include "Bullet.hpp"

class SnowPeaBullet : public Bullet {
public:
    SnowPeaBullet(int bullet_speed ,int bullet_damage);
    virtual ~SnowPeaBullet();
    // Add any necessary methods and members specific to SnowPeaBullet
};

#endif // SNOWPEABULLET_HPP