#include "MelonPlut.hpp"

MelonPlut::MelonPlut(FileHandler plants_properties)
    : ShooterPlant(
          std::stoi(plants_properties.getData("MelonPlut", "health")),
          std::stoi(plants_properties.getData("MelonPlut", "cooldown")),
          std::stoi(plants_properties.getData("MelonPlut", "price")),
          std::stoi(plants_properties.getData("MelonPlut", "damage")),
          std::stoi(plants_properties.getData("MelonPlut", "hit rate")),
          std::stoi(plants_properties.getData("MelonPlut", "bullet speed"))) {}

MelonPlut::~MelonPlut() {}