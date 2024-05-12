#include "SunFlower.hpp"

SunFlower::SunFlower(FileHandler plants_properties)
    : SunProducerPlant(
        std::stoi(plants_properties.getData("SunFlower", "health")),
        std::stoi(plants_properties.getData("SunFlower", "cooldown")),
        std::stoi(plants_properties.getData("SunFlower", "price"))
    ) {}

SunFlower::~SunFlower() {}
