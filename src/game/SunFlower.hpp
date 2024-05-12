#ifndef SUNFLOWER_HPP
#define SUNFLOWER_HPP

#include "SunProducerPlant.hpp"
#include "../utils/FileHandler.hpp"

class SunFlower : public SunProducerPlant {
public:
    SunFlower(FileHandler plants_properties);
    virtual ~SunFlower();
};

#endif // SUNFLOWER_HPP
