#include "PeaShooter.hpp"

PeaShooter::PeaShooter(FileHandler plants_properties)
    : ShooterPlant(
        std::stoi(plants_properties.getData("PeaShooter", "health")), 
        std::stoi(plants_properties.getData("PeaShooter", "cooldown")), 
        std::stoi(plants_properties.getData("PeaShooter", "price")), 
        std::stoi(plants_properties.getData("PeaShooter", "damage")), 
        std::stoi(plants_properties.getData("PeaShooter", "hit rate")), 
        std::stoi(plants_properties.getData("PeaShooter", "bullet speed"))
    ) {}

PeaShooter::~PeaShooter() {}