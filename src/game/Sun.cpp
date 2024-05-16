#include "Sun.hpp"

Sun::Sun(FileHandler Item_csv){
    speed = std::stoi(Item_csv.getData("sun","speed"));
    MoveStatus = true;
}

Sun::~Sun() {}