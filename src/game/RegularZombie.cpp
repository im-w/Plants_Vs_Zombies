#include "RegularZombie.hpp"

RegularZombie::RegularZombie(FileHandler Zombies_csv)
       : Zombie(std::stoi(Zombies_csv.getData("regular","health")),std::stoi(Zombies_csv.getData("regular", "speed")),std::stoi(Zombies_csv.getData("regular", "damage")),std::stoi(Zombies_csv.getData("regular","time")),std::stoi(Zombies_csv.getData("regular", "hit rate"))) {}

RegularZombie::~RegularZombie() {}