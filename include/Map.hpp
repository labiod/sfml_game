#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include "GameManager.hpp"

class Map {
    private:
        sf::RectangleShape* mGround;
        const sf::Vector2f* mRenderPosition;
        sf::RectangleShape mSky;
        const sf::Vector2f* mMapSize;
        std::vector<sf::Shape*> mMapObject;
        GameManager* mManager;
    public:
        Map(GameManager* manager, float width, float height) :mSky(), mMapObject() {
            mManager = manager;
            mMapSize = new sf::Vector2f(width, height);
            mRenderPosition = new sf::Vector2f(0, 0);
            mSky.setFillColor(sf::Color::Cyan);
            sf::Vector2f skySize(width, height/4 * 3);
            mSky.setSize(skySize);
            mSky.setPosition(mRenderPosition->x, mRenderPosition->y);

            prepareMap();

            mGround = new sf::RectangleShape();
            mGround->setFillColor(sf::Color::Green);
             sf::Vector2f groundSize(width, height/4);
            mGround->setSize(groundSize);
            mGround->setPosition(mRenderPosition->x, mRenderPosition->y + (mMapSize->y/4 * 3));
            mManager->addWall(mGround);
        }

        ~Map() {
            delete mMapSize;
            delete mRenderPosition;
            for (int i = 0; i < mMapObject.size(); ++i) {
                delete mMapObject[i];
            }
        }
        void render(sf::RenderWindow& window);

        void setPosition(float x, float y);

        sf::Vector2f getStartPosition();

    private:
        void prepareMap();
};

#endif //MAP_HPP