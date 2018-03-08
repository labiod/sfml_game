#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "GameManager.hpp"
#include "GravityObject.hpp"

class Player : public GravityObject {
        sf::CircleShape mPlayerShape;
        int mJumpValue;
        int mJumpStep;
        int mFullJump;
        bool mJumping;
        bool mIsMovingLeft;
        bool mIsMovingRight;
        float mPlayerSpeed;
        float mCachePositionY;
        GameManager* mGameManager;
    public:
        Player(GameManager* gameManager, float size, int playerSpeed);

        void setPlayerColor(sf::Color& color) {
            mPlayerShape.setFillColor(color);
        }

        void setPosition(float x, float y) {
            mPlayerShape.setPosition(x, y);
            mCachePositionY = mPlayerShape.getPosition().y;
        }

        void move(float offsetX, float offsetY) {
            mPlayerShape.move(offsetX, offsetY);
        }

        void move(const sf::Vector2f& offset) {
            mPlayerShape.move(offset);
        }

        void update(sf::Time deltaTime);

        void render(sf::RenderWindow& window) {
            window.draw(mPlayerShape);
        }

        void jump(bool isPressed);

        void left(bool pressed) {
            mIsMovingLeft = pressed;
        }

        void right(bool pressed) {
            mIsMovingRight = pressed;
        }

        void nextJumpValue();

        void moveToDirection(sf::Vector2f point, sf::Vector2f vector) override;
};

#endif // PLAYER_HPP