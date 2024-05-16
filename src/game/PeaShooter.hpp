#ifndef PEASHOOTER_HPP
#define PEASHOOTER_HPP

#include "ShooterPlant.hpp"
#include "../utils/FileHandler.hpp"
#include "PeaBullet.hpp"
#include "GamePaths.hpp"

class PeaShooter : public ShooterPlant
{
protected:
public:
    PeaShooter(FileHandler plants_properties);
    virtual ~PeaShooter();
    virtual void shoot(std::vector<std::unique_ptr<Bullet>> &bullets, AssetManager &assetManager);
};

#endif // PEASHOOTER_HPP
