#ifndef PLANT_HPP
#define PLANT_HPP

#include "AnimatedObject.hpp"

class Plant : public AnimatedObject
{
protected:
    int health;
    int cooldown;
    int price;

public:
    Plant(int health, int cooldown, int price);
    virtual ~Plant();
    void takeDamage(int damage);
    bool isDead();
};

#endif // PLANT_HPP