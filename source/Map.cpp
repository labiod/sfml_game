#include "Map.hpp"

void Map::render(sf::RenderWindow& window) {
    window.draw(*mGround);
    window.draw(mSky);
    for (int i =0; i < mMapObject.size(); ++i) {
        window.draw(*(mMapObject[i]));
    }
}

void Map::setPosition(float x, float y) {
    delete mRenderPosition;
    mRenderPosition = new sf::Vector2f(x, y);
    mSky.setPosition(mRenderPosition->x, mRenderPosition->y);
    mGround->setPosition(mRenderPosition->x, mRenderPosition->y + (mMapSize->y/4 * 3));
}

sf::Vector2f Map::getStartPosition() {
    float startX = mRenderPosition->x + 20;
    float startY = mMapSize->y/4 * 3;
    sf::Vector2f result(startX, startY);
    return result;
}

void Map::prepareMap() {
    sf::RectangleShape* leftWall = new sf::RectangleShape();
    leftWall->setFillColor(sf::Color::Black);
    sf::Vector2f leftWallSize(10, 600);
    leftWall->setSize(leftWallSize);
    leftWall->setPosition(mRenderPosition->x, mRenderPosition->y);
    mManager->addWall(leftWall);
    mMapObject.push_back(leftWall);

    sf::RectangleShape* rightWall = new sf::RectangleShape();
    rightWall->setFillColor(sf::Color::Black);
    sf::Vector2f rightWallSize(10, 600);
    rightWall->setSize(rightWallSize);
    rightWall->setPosition(mRenderPosition->x + mMapSize->x - 10, mRenderPosition->y);
    mManager->addWall(rightWall);
    mMapObject.push_back(rightWall);

    sf::RectangleShape* wall = new sf::RectangleShape();
    wall->setFillColor(sf::Color::Red);
    sf::Vector2f wallSize(40, 200);
    wall->setSize(wallSize);
    wall->setPosition(mRenderPosition->x + 300, mRenderPosition->y + (mMapSize->y/4 * 3) - wallSize.y);
    mManager->addWall(wall);
    mMapObject.push_back(wall);

    sf::RectangleShape* wallGreen = new sf::RectangleShape();
    wallGreen->setFillColor(sf::Color::Green);
    sf::Vector2f wallSize2(40, 100);
    wallGreen->setSize(wallSize2);
    wallGreen->setPosition(mRenderPosition->x + 100, mRenderPosition->y + (mMapSize->y/4 * 3) - wallSize2.y);
    mManager->addWall(wallGreen);
    mMapObject.push_back(wallGreen);
}