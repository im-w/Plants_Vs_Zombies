#include "Gargantuar.hpp"

Gargantuar::Gargantuar(FileHandler Zombies_csv)
    : Zombie(std::stoi(Zombies_csv.getData("Gragantuar", "health")), std::stoi(Zombies_csv.getData("Gragantuar", "speed")), std::stoi(Zombies_csv.getData("Gragantuar", "damage")), std::stoi(Zombies_csv.getData("Gragantuar", "time")), std::stoi(Zombies_csv.getData("Gragantuar", "hit rate"))) {}

Gargantuar::~Gargantuar() {}