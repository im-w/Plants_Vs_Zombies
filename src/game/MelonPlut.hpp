#ifndef MELONPLUT_HPP
#define MELONPLUT_HPP

#include "ShooterPlant.hpp"
#include "../utils/FileHandler.hpp"

class MelonPlut : public ShooterPlant {
public:
    MelonPlut(FileHandler plants_properties);
    virtual ~MelonPlut();
};

#endif // MELONPLUT_HPP
