#ifndef SUNPRODUCERPLANT_HPP
#define SUNPRODUCERPLANT_HPP

#include "Plant.hpp"

class SunProducerPlant : public Plant {
public:
    SunProducerPlant(int health, int cooldown, int price);
    virtual ~SunProducerPlant();
};

#endif // SUNPRODUCERPLANT_HPP
