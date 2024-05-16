#include "SnowPea.hpp"

SnowPea::SnowPea(FileHandler plants_properties)
    : ShooterPlant(
          std::stoi(plants_properties.getData("SnowPea", "health")),
          std::stoi(plants_properties.getData("SnowPea", "cooldown")),
          std::stoi(plants_properties.getData("SnowPea", "price")),
          std::stoi(plants_properties.getData("SnowPea", "damage")),
          std::stoi(plants_properties.getData("SnowPea", "hit rate")),
          std::stoi(plants_properties.getData("SnowPea", "bullet speed"))) {}

SnowPea::~SnowPea() {}

void SnowPea::shoot(std::vector<std::unique_ptr<Bullet>> &bullets, AssetManager &assetManager)
{
    sf::Vector2f shooterPosition = this->getSprite().getPosition();
    std::unique_ptr<SnowPeaBullet> snowPeaBullet = std::make_unique<SnowPeaBullet>(bulletSpeed, damage, 5);
    snowPeaBullet->setPosition(shooterPosition.x + 30, shooterPosition.y + 20);
    assetManager.LoadTexture("snowBullet_texture", SNOWY_PEA_ITEM_SHOOTING_ANIMATION_PATH);
    assetManager.LoadAnimation("snowBullet_animation", SNOWY_PEA_ITEM_SHOOTING_ANIMATION_PATH, 620, 877, 24, 150, true);
    snowPeaBullet->setTexture(assetManager.GetTexture("snowBullet_texture"));
    snowPeaBullet->addAnimation("idle", assetManager.GetAnimation("snowBullet_animation"));
    snowPeaBullet->setScale(0.05, 0.05);
    bullets.push_back(std::move(snowPeaBullet));
}