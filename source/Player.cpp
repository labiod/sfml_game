#include "Player.hpp"
#include "Log.hpp"

#define DEFAULT_PLAYER_JUMP 120.f
#define MAX_JUMP_VALUE 120.f
#define TAG "[KGB]"

Player::Player(GameManager* gameManager, float size, int playerSpeed): mPlayerShape(size/2) {
            mPlayerSpeed = playerSpeed;
            mIsMovingLeft = false;
            mIsMovingRight = false;
            mJumpValue = 0;
            mFullJump = 0;
            mJumping = false;
            mCachePositionY = mPlayerShape.getPosition().y;
            mGameManager = gameManager;
}

void Player::update(sf::Time deltaTime) {

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
    float modifier = deltaTime.asSeconds() * 60;
    do { 
        //Log::d(TAG, "test %.2f", left);
        left = playerBounds.left + movement.x * modifier;
        sf::FloatRect bounds(left, top, width, height);
        movement.x /= 2;
        shapeBounds = bounds;
    } while (mGameManager->hitTest(shapeBounds));
    Log::d(TAG, "jump value: %i", mJumpValue);
    Log::d(TAG, "full jump: %i", mFullJump);
    if (mJumpValue > 0  && mFullJump < MAX_JUMP_VALUE) {
        movement.y -= DEFAULT_PLAYER_JUMP;
        mFullJump += DEFAULT_PLAYER_JUMP * modifier;
        mJumpValue -= DEFAULT_PLAYER_JUMP * modifier;
        if (mJumpValue < 0) {
            mJumpValue = 0;
        }
    }
    
    mPlayerShape.move(movement * modifier);
}

void Player::jump(bool isPressed) {
    bool result = isPressed;
    if (isPressed) {  
        if (mFullJump >= MAX_JUMP_VALUE) {
            result = false;
        } else if (mJumpValue <= 0) {
            mJumpValue = DEFAULT_PLAYER_JUMP;
        } else if (mJumpValue > 0) {
            mJumpValue += DEFAULT_PLAYER_JUMP;
        } 
    } else { 
        mJumpValue = 0;
        //to prevent jump in jump
        mFullJump = MAX_JUMP_VALUE;
    }
    mJumping = result;
}

void Player::moveToDirection(sf::Vector2f point, sf::Vector2f vector) {
    // if (mJumping) {
    //     //Do not fall to gravity poin when player jump
    //     return;
    // }

    //Log::d(TAG, "gravity works");
    sf::Vector2f movement(0.f, 0.f);

    movement.x = vector.x;
    movement.y = vector.y;
    sf::FloatRect playerBounds = mPlayerShape.getGlobalBounds();
    float left = playerBounds.left;
    float top = playerBounds.top;
    float width = playerBounds.width;
    float height = playerBounds.height;
    sf::FloatRect shapeBounds;
    int xDirection = point.x > playerBounds.left ? 1 : -1;
    int yDirection = point.y > playerBounds.top ? 1 : -1;
    
    do { 
        //Log::d(TAG, "test %.2f", left);
        left = playerBounds.left + movement.x;
        top = playerBounds.top + movement.y;
        sf::FloatRect bounds(left, top, width, height);
        movement.x /= 2;
        movement.y /= 2;
        shapeBounds = bounds;
    } while (mGameManager->hitTest(shapeBounds));
    Log::d(TAG, "y : %.2f", movement.y);
    if ((int)movement.y == 0) {
        mFullJump = 0;
    }
    mPlayerShape.move(movement);
}

