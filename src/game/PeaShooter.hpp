#ifndef PEASHOOTER_HPP
#define PEASHOOTER_HPP

#include "ShooterPlant.hpp"
#include "../utils/FileHandler.hpp"

class PeaShooter : public ShooterPlant {
protected:
    

public:
    PeaShooter(FileHandler plants_csv);
    virtual ~PeaShooter();
};

#endif // PEASHOOTER_HPP
