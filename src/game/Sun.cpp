#include "Sun.hpp"

Sun::Sun(FileHandler items_properties)
{
    speed = std::stoi(items_properties.getData("sun", "speed"));
    MoveStatus = true;
}

Sun::~Sun() {}