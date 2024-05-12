#include "SnowPea.hpp"

SnowPea::SnowPea(FileHandler plants_properties)
    : ShooterPlant(
        std::stoi(plants_properties.getData("SnowPea", "health")), 
        std::stoi(plants_properties.getData("SnowPea", "cooldown")), 
        std::stoi(plants_properties.getData("SnowPea", "price")), 
        std::stoi(plants_properties.getData("SnowPea", "damage")), 
        std::stoi(plants_properties.getData("SnowPea", "hit rate")), 
        std::stoi(plants_properties.getData("SnowPea", "bullet speed"))
    ) {}

SnowPea::~SnowPea() {}