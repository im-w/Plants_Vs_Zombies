#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include "AnimatedObject.hpp"

class Zombie : public AnimatedObject {
protected:
    int health;
    int speed;

public:
    Zombie(int health, int speed);
    virtual ~Zombie();
};

#endif // ZOMBIE_HPP