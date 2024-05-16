#include "BucketHeadZombie.hpp"

BucketHeadZombie::BucketHeadZombie(FileHandler Zombies_csv)
    : Zombie(std::stoi(Zombies_csv.getData("buckethead", "health")), std::stoi(Zombies_csv.getData("buckethead", "speed")), std::stoi(Zombies_csv.getData("buckethead", "damage")), std::stoi(Zombies_csv.getData("buckethead", "time")), std::stoi(Zombies_csv.getData("buckethead", "hit rate"))) {}

BucketHeadZombie::~BucketHeadZombie() {}