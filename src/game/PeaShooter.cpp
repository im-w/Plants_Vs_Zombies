#include "PeaShooter.hpp"

PeaShooter::PeaShooter(FileHandler plants_csv)
    : ShooterPlant(stoi(plants_csv.getData("peashooter", "health")), stoi(plants_csv.getData("peashooter", "cooldown")), stoi(plants_csv.getData("peashooter", "price")), stoi(plants_csv.getData("peashooter", "damage")), stoi(plants_csv.getData("peashooter", "hit rate")), stoi(plants_csv.getData("peashooter", "bullet speed"))) {}

PeaShooter::~PeaShooter() {}