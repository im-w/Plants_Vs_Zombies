#ifndef SHOOTERPLANT_HPP
#define SHOOTERPLANT_HPP

#include "Plant.hpp"
#include "Bullet.hpp"
#include "Zombie.hpp"
#include "../utils/AssetManager.hpp"

class ShooterPlant : public Plant
{
protected:
    int damage;
    int hitRate;
    int bulletSpeed;
    sf::Time timeSinceLastShot;

public:
    ShooterPlant(int health, int cooldown, int price, int damage, int hitRate, int bulletSpeed);
    virtual ~ShooterPlant();
    virtual void shoot(std::vector<std::unique_ptr<Bullet>> &bullets, AssetManager &assetManager);
    bool zombieInRange(std::vector<std::unique_ptr<Zombie>> &zombies);
    int getHitrate();
    void increaseTimeSinceLastShot(sf::Time elapsedTime);
    void resetTimeSinceLastShot();
    bool canShoot();
};

#endif // SHOOTERPLANT_HPP
