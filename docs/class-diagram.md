
![class diagram](https://dev-to-uploads.s3.amazonaws.com/uploads/articles/th5xamgrr6se0x5ro4g6.png)

## Class Relationships
```
AnimatedObject
  |
  +-- Plant
  |     |
  |     +-- ShooterPlant
  |     |     |
  |     |     +-- PeaShooter
  |     |     +-- SnowPea
  |     |     +-- MelonPlut
  |     |
  |     +-- DefenderPlant
  |     |     |
  |     |     +-- WallNut
  |     |
  |     +-- SunProducerPlant
  |           |
  |           +-- SunFlower
  |
  +-- Zombie
        |
        +-- BucketHeadZombie
        +-- Regular
```

### AnimatedObject
```
------------------------------------
|       AnimatedObject             |
------------------------------------
| - m_sprite: sf::Sprite           |
| - m_animations: std::map<string, Animation> |
| - m_currentAnimation: Animation* |
------------------------------------
| + setPosition(x: float, y: float): void       |
| + setTexture(texture: const sf::Texture&): void |
| + addAnimation(name: const string&, animation: const Animation&): void |
| + setCurrentAnimation(name: const string&): void |
| + play(): void                   |
| + pause(): void                  |
| + stop(): void                   |
| + update(deltaTime: sf::Time): void |
| + draw(window: sf::RenderWindow&): void |
| + setScale(scale_x: float, scale_y: float): void |
| + getPosition(): sf::Vector2f    |
| + getSprite(): sf::Sprite&       |
------------------------------------
```

### Animation
```
------------------------------------
|       Animation                  |
------------------------------------
| - m_frames: vector<sf::IntRect>  |
| - m_spriteSheet: sf::Texture     |
| - m_frameTime: sf::Time          |
| - m_elapsedTime: sf::Time        |
| - m_currentFrame: size_t         |
| - m_isPaused: bool               |
| - m_isLooped: bool               |
------------------------------------
| + init(sheet: const sf::Texture&, each_frame_x_size: int, each_frame_y_size: int, total_frame_number: int, frame_time_in_ms: int, isLoop: bool): void |
| + addFrame(frame: sf::IntRect): void |
| + setSpriteSheet(texture: const sf::Texture&): void |
| + setFrameTime(time: sf::Time): void |
| + play(): void                   |
| + pause(): void                  |
| + stop(): void                   |
| + setLooped(looped: bool): void  |
| + update(deltaTime: sf::Time): void |
| + setFrame(frame: size_t): void  |
| + getFrame(): sf::IntRect        |
| + getSpriteSheet(): const sf::Texture* |
------------------------------------
```

### Plant
```
------------------------------------
|             Plant                |
------------------------------------
| [inherits AnimatedObject]        |
------------------------------------
| - health: int                    |
| - cooldown: int                  |
| - price: int                     |
------------------------------------
| + Plant(health: int, cooldown: int, price: int) |
| + ~Plant(): virtual              |
| + takeDamage(damage: int): void  |
| + isDead(): bool                 |
------------------------------------
```

### ShooterPlant
```
------------------------------------
|          ShooterPlant            |
------------------------------------
| [inherits Plant]                 |
------------------------------------
| - damage: int                    |
| - hitRate: int                   |
| - bulletSpeed: int               |
| - timeSinceLastShot: sf::Time    |
------------------------------------
| + ShooterPlant(health: int, cooldown: int, price: int, damage: int, hitRate: int, bulletSpeed: int) |
| + ~ShooterPlant(): virtual       |
| + shoot(bullets: vector<unique_ptr<Bullet>>&, assetManager: AssetManager&): virtual void |
| + zombieInRange(zombies: vector<unique_ptr<Zombie>>&): bool |
| + getHitrate(): int              |
| + increaseTimeSinceLastShot(elapsedTime: sf::Time): void |
| + resetTimeSinceLastShot(): void |
| + canShoot(): bool               |
------------------------------------
```

### DefenderPlant
```
------------------------------------
|         DefenderPlant            |
------------------------------------
| [inherits Plant]                 |
------------------------------------
| + DefenderPlant(health: int, cooldown: int, price: int) |
| + ~DefenderPlant(): virtual      |
------------------------------------
```

### SunProducerPlant
```
------------------------------------
|       SunProducerPlant           |
------------------------------------
| [inherits Plant]                 |
------------------------------------
| + SunProducerPlant(health: int, cooldown: int, price: int) |
| + ~SunProducerPlant(): virtual   |
------------------------------------
```

### Zombie
```
------------------------------------
|             Zombie               |
------------------------------------
| [inherits AnimatedObject]        |
------------------------------------
| - m_health: int                  |
| - m_speed: int                   |
| - m_damage: int                  |
| - m_timeToSpawn: int             |
| - m_hitRate: int                 |
| - hitbox: sf::RectangleShape     |
| - stopTime: sf::Time             |
| - isMoving: bool                 |
------------------------------------
| + Zombie(health: int, speed: int, damage: int, timeToSpawn: int, hitRate: int) |
| + ~Zombie(): virtual             |
| + move(deltaTime: sf::Time): void|
| + drawHitbox(window: sf::RenderWindow&): void |
| + initHitbox(): void             |
| + getHitbox(): sf::RectangleShape& |
| + takeDamage(damage: int): void  |
| + isDead(): bool                 |
| + stopMovementFor(duration: sf::Time): void |
| + getDamage(): int               |
------------------------------------
```

### Bullet
```
------------------------------------
|             Bullet               |
------------------------------------
| [inherits AnimatedObject]        |
------------------------------------
| - m_bullet_speed: int            |
| - m_bullet_damage: int           |
------------------------------------
| + Bullet(bullet_speed: int, bullet_damage: int) |
| + ~Bullet(): virtual             |
| + move(elapsedTime: sf::Time): void |
| + getDamage(): int               |
------------------------------------
```

### PeaShooter
```
------------------------------------
|           PeaShooter             |
------------------------------------
| [inherits ShooterPlant]          |
------------------------------------
| + PeaShooter(plants_properties: FileHandler) |
| + ~PeaShooter(): virtual         |
| + shoot(bullets: vector<unique_ptr<Bullet>>&, assetManager: AssetManager&): void |
------------------------------------
```

### SnowPea
```
------------------------------------
|            SnowPea               |
------------------------------------
| [inherits ShooterPlant]          |
------------------------------------
| + SnowPea(plants_properties: FileHandler) |
| + ~SnowPea(): virtual            |
| + shoot(bullets: vector<unique_ptr<Bullet>>&, assetManager: AssetManager&): void |
------------------------------------
```

### SunFlower
```
------------------------------------
|           SunFlower              |
------------------------------------
|

 [inherits SunProducerPlant]      |
------------------------------------
| + SunFlower(plants_properties: FileHandler) |
| + ~SunFlower(): virtual          |
------------------------------------
```

### WallNut
```
------------------------------------
|            WallNut                |
------------------------------------
| [inherits DefenderPlant]          |
------------------------------------
| + WallNut(plants_properties: FileHandler) |
| + ~WallNut(): virtual            |
------------------------------------
```

### RegularZombie
```
------------------------------------
|          RegularZombie           |
------------------------------------
| [inherits Zombie]                |
------------------------------------
| + RegularZombie(Zombies_csv: FileHandler) |
| + ~RegularZombie(): virtual      |
------------------------------------
```

### Gargantuar
```
------------------------------------
|           Gargantuar             |
------------------------------------
| [inherits Zombie]                |
------------------------------------
| + Gargantuar(Zombies_csv: FileHandler) |
| + ~Gargantuar(): virtual         |
------------------------------------
```

### PeaBullet
```
------------------------------------
|           PeaBullet              |
------------------------------------
| [inherits Bullet]                |
------------------------------------
| + PeaBullet(bullet_speed: int, bullet_damage: int) |
| + ~PeaBullet(): virtual          |
------------------------------------
```

### SnowPeaBullet
```
------------------------------------
|          SnowPeaBullet           |
------------------------------------
| [inherits Bullet]                |
------------------------------------
| + SnowPeaBullet(bullet_speed: int, bullet_damage: int) |
| + ~SnowPeaBullet(): virtual      |
------------------------------------
```

### MelonPlut
```
------------------------------------
|           MelonPlut              |
------------------------------------
| [inherits ShooterPlant]          |
------------------------------------
| + MelonPlut(plants_properties: FileHandler) |
| + ~MelonPlut(): virtual          |
------------------------------------
```

### SunProducerPlant
```
------------------------------------
|       SunProducerPlant           |
------------------------------------
| [inherits Plant]                 |
------------------------------------
| + SunProducerPlant(health: int, cooldown: int, price: int) |
| + ~SunProducerPlant(): virtual   |
------------------------------------
```

## Bullet
```
------------------------------------
|       AnimatedObject             |
------------------------------------
| - m_sprite: sf::Sprite           |
| - m_animations: std::map<string, Animation> |
| - m_currentAnimation: Animation* |
------------------------------------
| + setPosition(x: float, y: float): void       |
| + setTexture(texture: const sf::Texture&): void |
| + addAnimation(name: const string&, animation: const Animation&): void |
| + setCurrentAnimation(name: const string&): void |
| + play(): void                   |
| + pause(): void                  |
| + stop(): void                   |
| + update(deltaTime: sf::Time): void |
| + draw(window: sf::RenderWindow&): void |
| + setScale(scale_x: float, scale_y: float): void |
| + getPosition(): sf::Vector2f    |
| + getSprite(): sf::Sprite&       |
------------------------------------
        |
        +-- Bullet
              ------------------------------------
              |             Bullet                |
              ------------------------------------
              | - m_bullet_speed: int             |
              | - m_bullet_damage: int            |
              | - m_bullet_slowDown: int          |
              ------------------------------------
              | + Bullet(int, int, int)           |
              | + ~Bullet()                       |
              | + move(sf::Time): void            |
              | + getDamage(): int                |
              | + getSlowDown(): int              |
              ------------------------------------
                    |
                    +-- PeaBullet
                    |     ------------------------------------
                    |     |           PeaBullet              |
                    |     ------------------------------------
                    |     | + PeaBullet(int, int)            |
                    |     | + ~PeaBullet()                   |
                    |     ------------------------------------
                    |
                    +-- SnowPeaBullet
                          ------------------------------------
                          |         SnowPeaBullet            |
                          ------------------------------------
                          | + SnowPeaBullet(int, int, int)   |
                          | + ~SnowPeaBullet()               |
                          ------------------------------------
```