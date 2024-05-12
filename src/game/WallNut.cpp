#include "WallNut.hpp"

WallNut::WallNut(FileHandler plants_properties)
    : DefenderPlant(
        std::stoi(plants_properties.getData("WallNut", "health")),
        std::stoi(plants_properties.getData("WallNut", "cooldown")),
        std::stoi(plants_properties.getData("WallNut", "price"))
    ) {}

WallNut::~WallNut() {}
