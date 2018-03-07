#include "Player.hpp"
#include "Log.hpp"

#define DEFAULT_PLAYER_JUMP 75.f
#define MAX_JUMP_VALUE 140.f
#define TAG "[KGB]"

void Player::update(sf::Time deltaTime) {
    //reset y position
    mPlayerShape.setPosition(mPlayerShape.getPosition().x, mCachePositionY);

    sf::Vector2f movement(0.f, 0.f);

    if (mIsMovingLeft)
        movement.x -= mPlayerSpeed;
    if (mIsMovingRight)
        movement.x += mPlayerSpeed;
    sf::FloatRect playerBounds = mPlayerShape.getGlobalBounds();
    float left = playerBounds.left;
    float top = playerBounds.top;
    float width = playerBounds.width;
    float height = playerBounds.height;
    sf::FloatRect shapeBounds;
    do { 
        //Log::d(TAG, "test %.2f", left);
        left = playerBounds.left + movement.x * deltaTime.asSeconds();
        sf::FloatRect bounds(left, top, width, height);
        movement.x /= 2;
        shapeBounds = bounds;
    } while (mGameManager->hitTest(shapeBounds));
    //Log::d(TAG, "*********** %.2f", mJumpValue);
    movement.y -= mJumpValue;
    if (mJumpValue > 0) {
        nextJumpValue();
    }
    
    mPlayerShape.move(movement * deltaTime.asSeconds());
}

void Player::jump(bool isPressed) {
    Log::d(TAG, "prev jump: %.2f", mJumpValue);
    if (isPressed) {  
        if (mJumpTo == 0 && mJumpValue == 0) {
            Log::d(TAG, "cache pos: %.2f", mPlayerShape.getPosition().y);
            mCachePositionY = mPlayerShape.getPosition().y;
            mJumpTo = DEFAULT_PLAYER_JUMP;
            mJumpValue = mStep;   
        } else {
            if (mJumpTo < MAX_JUMP_VALUE) {
                mJumpTo += mJumpTo/2;
            }
            
        }
    } else {
        mJumpTo = 0;
    }
    Log::d(TAG, "jump: %.2f", mJumpValue);
}

void Player::nextJumpValue() {
    if (mJumpTo != 0) {
        mJumpValue += mStep;
        if (mJumpValue > mJumpTo) {
            mJumpValue = mJumpTo;
            mJumpTo = 0;
        }
    } else {
        mJumpValue -= mStep;
        if (mJumpValue < mJumpTo) {
            mJumpValue = mJumpTo;
        }
    }
}

