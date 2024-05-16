#ifndef SUN_HPP
#define SUN_HPP

#include "AnimatedObject.hpp"
#include "../utils/FileHandler.hpp"

class Sun : public AnimatedObject
{
protected:
    int speed;
public:
    bool MoveStatus;
    int bottom;
    Sun(FileHandler items_properties);
    virtual ~Sun();
};
#endif // SUN_HPP