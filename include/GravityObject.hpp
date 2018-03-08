#ifndef GRAVITY_OBJECT_HPP
#define GRAVITY_OBJECT_HPP

#include <SFML/Graphics.hpp>

class GravityObject {
    public:
        virtual void moveToDirection(sf::Vector2f point, sf::Vector2f vector) = 0;
};
#endif //GRAVITY_OBJECT_HPP