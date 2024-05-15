#include "PeaShooter.hpp"

PeaShooter::PeaShooter(FileHandler plants_properties)
    : ShooterPlant(
        std::stoi(plants_properties.getData("PeaShooter", "health")), 
        std::stoi(plants_properties.getData("PeaShooter", "cooldown")), 
        std::stoi(plants_properties.getData("PeaShooter", "price")), 
        std::stoi(plants_properties.getData("PeaShooter", "damage")), 
        std::stoi(plants_properties.getData("PeaShooter", "hit rate")), 
        std::stoi(plants_properties.getData("PeaShooter", "bullet speed"))
    ) {}

PeaShooter::~PeaShooter() {}

void PeaShooter::shoot(std::vector<std::unique_ptr<Bullet>>& bullets , AssetManager& assetManager) {
    // Get the position of the PeaShooter sprite
    sf::Vector2f shooterPosition = this->getSprite().getPosition();
    
    // Create a PeaBullet and set its position to the shooter's position
    std::unique_ptr<PeaBullet> peaBullet = std::make_unique<PeaBullet>(bulletSpeed, damage);
    peaBullet->setPosition(shooterPosition.x + 30, shooterPosition.y + 20);
    
    // Load texture and animation
    assetManager.LoadTexture("bullet_texture", PEA_ITEM_SHOOTING_ANIMATION_PATH);
    assetManager.LoadAnimation("bullet_animation", PEA_ITEM_SHOOTING_ANIMATION_PATH, 600,849, 22 , 60 , true);

    // Set texture and animation for the bullet
    peaBullet->setTexture(assetManager.GetTexture("bullet_texture"));
    peaBullet->addAnimation("idle", assetManager.GetAnimation("bullet_animation"));
    peaBullet->setScale(0.05,0.05);


    
    bullets.push_back(std::move(peaBullet));
}