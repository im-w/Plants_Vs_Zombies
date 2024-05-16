#ifndef DEFENDERPLANT_HPP
#define DEFENDERPLANT_HPP

#include "Plant.hpp"

class DefenderPlant : public Plant
{
public:
    DefenderPlant(int health, int cooldown, int price);
    virtual ~DefenderPlant();
};

#endif // DEFENDERPLANT_HPP
