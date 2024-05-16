#include "Plant.hpp"

Plant::Plant(int health, int cooldown, int price) : health(health), cooldown(cooldown), price(price) {}

Plant::~Plant() {}

void Plant::takeDamage(int damage)
{
    health -= damage;
}

bool Plant::isDead()
{
    if (health <= 0)
    {
        return true;
    }
    return false;
}
