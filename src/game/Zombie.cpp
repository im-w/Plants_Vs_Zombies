#include "Zombie.hpp"

Zombie::Zombie(int health, int speed, int damage, int timeToSpawn , int hitRate) : health(health), speed(speed), damage(damage), timeToSpawn(timeToSpawn), hitRate(hitRate) {}

Zombie::~Zombie() {}