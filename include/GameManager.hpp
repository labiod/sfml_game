#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "GravityObject.hpp"

/** 
 * CONSTANT SECTION
 */ 
#define TAG "[KGB]"

class GameManager {
        std::vector<sf::Shape*> mHitBounds;
        sf::Vector2f mGravityPoint;
        sf::Vector2f mGravityVector;
    public:
        GameManager() : mHitBounds(), mGravityPoint(0, 0), mGravityVector(0, 0) {
        }

        void addWall(sf::Shape* hitBounds);
        bool hitTest(sf::FloatRect& bounds);

        void setGravity(sf::Vector2f gravityPoint, sf::Vector2f gravityVector) {
            mGravityPoint = gravityPoint;
            mGravityVector = gravityVector;
        }

        void pullObject(GravityObject& obj);
};

#endif //GAME_MANAGER_HPP