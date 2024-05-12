#ifndef SNOWPEA_HPP
#define SNOWPEA_HPP

#include "ShooterPlant.hpp"
#include "../utils/FileHandler.hpp"

class SnowPea : public ShooterPlant {
public:
    SnowPea(FileHandler plants_properties);
    virtual ~SnowPea();
};

#endif // SNOWPEA_HPP
