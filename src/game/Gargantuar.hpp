#ifndef GARGANTUAR_HPP
#define GARGANTUAR_HPP

#include "Zombie.hpp"
#include "../utils/FileHandler.hpp"

class Gargantuar : public Zombie {
protected:


public:
    Gargantuar(FileHandler Zombies_csv);
    virtual ~Gargantuar();
};

#endif //GARGANTUAR_HPP