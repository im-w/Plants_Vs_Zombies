#include "ShooterPlant.hpp"

ShooterPlant::ShooterPlant(int health, int cooldown, int price, int damage, int hitRate, int bulletSpeed) : Plant(health, cooldown, price), damage(damage), hitRate(hitRate), bulletSpeed(bulletSpeed) {}

ShooterPlant::~ShooterPlant() {}

void ShooterPlant::shoot(std::vector<std::unique_ptr<Bullet>> &bullets, AssetManager &assetManager) {}

bool ShooterPlant::zombieInRange(std::vector<std::unique_ptr<Zombie>> &zombies)
{
    sf::FloatRect plantBounds = getSprite().getGlobalBounds();
    float plantMiddleY = plantBounds.top + plantBounds.height / 2;

    for (const auto &zombie : zombies)
    {
        sf::FloatRect zombieBounds = zombie->getHitbox().getGlobalBounds();
        float zombieMiddleY = zombieBounds.top + zombieBounds.height / 2;

        if (std::abs(zombieMiddleY - plantMiddleY) < 100.0f
            && zombieBounds.left > plantBounds.left)
        {
            return true;
        }
    }
    return false;
}

int ShooterPlant::getHitrate()
{
    return hitRate;
}

void ShooterPlant::resetTimeSinceLastShot()
{
    timeSinceLastShot = sf::Time::Zero;
}

void ShooterPlant::increaseTimeSinceLastShot(sf::Time elapsedTime)
{
    timeSinceLastShot += elapsedTime;
}

bool ShooterPlant::canShoot()
{
    return timeSinceLastShot >= sf::seconds(hitRate);
}
