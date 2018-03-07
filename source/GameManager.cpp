#include "GameManager.hpp"

void GameManager::addWall(sf::Shape* shape) {
    mHitBounds.push_back(shape);
}
bool GameManager::hitTest(sf::FloatRect& bounds) {
    for (int i =0; i < mHitBounds.size(); ++i) {
        if (mHitBounds[i]->getGlobalBounds().intersects(bounds)){
            return true;
        }
    }
    return false;
}