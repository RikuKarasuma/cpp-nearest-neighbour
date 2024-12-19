#include <string>
#include <iostream>
#include <cmath>
#include "point.h"

Point::Point() : name(""), x(0), y(0) {}
Point::Point(std::string name, float x, float y) : name(name), x(x), y(y) {}

float Point::getX() const {
    return x;
}

float Point::getY() const {
    return y;
}

std::string Point::getName() const {
    return name;
}

float Point::findDistance(const Point& toCompare) const {

    return 
        std::sqrt(
            std::pow(this->getX() - toCompare.getX(), 2) + 
            std::pow(this->getY() - toCompare.getY(), 2)
        );
}

void Point::toString() const {
    std::cout << this->getName() << " at points x:" << this->getX() << " y:" << this->getY() << std::endl;
}
