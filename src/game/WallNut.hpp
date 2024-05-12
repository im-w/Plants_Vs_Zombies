#ifndef WALLNUT_HPP
#define WALLNUT_HPP

#include "DefenderPlant.hpp"
#include "../utils/FileHandler.hpp"

class WallNut : public DefenderPlant {
public:
    WallNut(FileHandler plants_properties);
    virtual ~WallNut();
};

#endif // WALLNUT_HPP
