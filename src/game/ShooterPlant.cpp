#include "ShooterPlant.hpp"

ShooterPlant::ShooterPlant(int health, int cooldown, int price, int damage, float hitRate, float bulletSpeed) : Plant(health, cooldown, price), damage(damage), hitRate(hitRate), bulletSpeed(bulletSpeed) {}

ShooterPlant::~ShooterPlant() {}