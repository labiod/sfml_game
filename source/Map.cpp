#include "Map.hpp"

void Map::render(sf::RenderWindow& window) {
    window.draw(mGround);
    window.draw(mSky);
    window.draw(*mWall);
}

void Map::setPosition(float x, float y) {
    delete mRenderPosition;
    mRenderPosition = new sf::Vector2f(x, y);
    mSky.setPosition(mRenderPosition->x, mRenderPosition->y);
    mGround.setPosition(mRenderPosition->x, mRenderPosition->y + (mMapSize->y/4 * 3));
}

sf::Vector2f Map::getStartPosition() {
    float startX = mRenderPosition->x + 20;
    float startY = mMapSize->y/4 * 3;
    sf::Vector2f result(startX, startY);
    return result;
}