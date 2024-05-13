#ifndef BUCKETHEADZOMBIE_HPP
#define BUCKETHEADZOMBIE_HPP

#include "Zombie.hpp"
#include "../utils/FileHandler.hpp"

class BucketHeadZombie : public Zombie {
protected:


public:
    BucketHeadZombie(FileHandler Zombies_csv);
    virtual ~BucketHeadZombie();
};

#endif //BUCKETHEADZOMBIE_HPP