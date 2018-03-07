#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include "GameManager.hpp"

class Map {
    private:
        sf::RectangleShape mGround;
        const sf::Vector2f* mRenderPosition;
        sf::RectangleShape mSky;
        const sf::Vector2f* mMapSize;
        sf::RectangleShape* mWall;
        GameManager* mManager;
    public:
        Map(GameManager* manager, float width, float height) 
            :mGround()
            ,mSky()
        {
            mManager = manager;
            mMapSize = new sf::Vector2f(width, height);
            mRenderPosition = new sf::Vector2f(0, 0);
            mGround.setFillColor(sf::Color::Green);
            mSky.setFillColor(sf::Color::Cyan);
            sf::Vector2f groundSize(width, height/4);
            mGround.setSize(groundSize);
            sf::Vector2f skySize(width, height/4 * 3);
            mSky.setSize(skySize);
            
            mSky.setPosition(mRenderPosition->x, mRenderPosition->y);
            mGround.setPosition(mRenderPosition->x, mRenderPosition->y + (mMapSize->y/4 * 3));
            mWall = new sf::RectangleShape();
            mWall->setFillColor(sf::Color::Red);
            sf::Vector2f wallSize(40, 130);
            mWall->setSize(wallSize);
            mWall->setPosition(mRenderPosition->x + 300, mRenderPosition->y + (mMapSize->y/4 * 3) - wallSize.y);
            mManager->addWall(mWall);
        }

        ~Map() {
            delete mMapSize;
            delete mRenderPosition;
            delete mWall;
        }
        void render(sf::RenderWindow& window);

        void setPosition(float x, float y);

        sf::Vector2f getStartPosition();
};

#endif //MAP_HPP