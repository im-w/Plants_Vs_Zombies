#ifndef SNOWPEA_HPP
#define SNOWPEA_HPP

#include "ShooterPlant.hpp"
#include "../utils/FileHandler.hpp"
#include "SnowPeaBullet.hpp"
#include "GamePaths.hpp"

class SnowPea : public ShooterPlant {
public:
    SnowPea(FileHandler plants_properties);
    virtual ~SnowPea();
    virtual void shoot(std::vector<std::unique_ptr<Bullet>>& bullets , AssetManager& assetManager);
};

#endif // SNOWPEA_HPP
