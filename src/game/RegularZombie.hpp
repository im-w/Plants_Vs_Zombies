#ifndef REGULARZOMBIE_HPP
#define REGULARZOMBIE_HPP

#include "Zombie.hpp"
#include "../utils/FileHandler.hpp"

class RegularZombie : public Zombie
{
protected:
public:
    RegularZombie(FileHandler Zombies_csv);
    virtual ~RegularZombie();
};

#endif // REGULARZOMBIE_HPP