#ifndef SHOOTERPLANT_HPP
#define SHOOTERPLANT_HPP

#include "Plant.hpp"

class ShooterPlant : public Plant {
protected:
    int damage;
    float hitRate;
    float bulletSpeed;

public:
    ShooterPlant(int health, int cooldown, int price, int damage, float hitRate, float bulletSpeed);
    virtual ~ShooterPlant();
};

#endif // SHOOTERPLANT_HPP
