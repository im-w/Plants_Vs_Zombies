#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include "AnimatedObject.hpp"

class Zombie : public AnimatedObject {
protected:
    int health;
    int speed;
    int damage;
    int timeToSpawn;
    int hitRate;

public:
    Zombie(int health, int speed,int damage, int timeToSpawn, int hitRate);
    virtual ~Zombie();
};

#endif // ZOMBIE_HPP