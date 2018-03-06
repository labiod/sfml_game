#include <SFML/Graphics.hpp>

/** 
 * CONSTANT SECTION
 */ 
#define TAG "[KGB]"
#define DEFAULT_PLAYER_SPEED 50.f
#define DEFAULT_PLAYER_JUMP 75.f
#define DEFAULT_PLAYER_SIZE 20.f
#define FPS 60.f
#define APP_TITLE "SFML first App"

/**
 * END CONSTANT SECTION
 */

//Class using for loggin debug or error message in terminal
//Works only in debug mode, in release methods are empty
class Log {
    public:
        static void d(const char* tag, const char* msg, ...);

        static void e(const char* tag, const char* msg, ...);
};

#ifndef NDEBUG
/**
 * START DEBUG SECTION
 */
#include <stdio.h>
#include <stdarg.h>
#include <iostream>

#define LOG_BUFFER_SIZE 1024

void Log::d(const char* tag, const char* msg, ...) {

    // debug mode
    va_list args;
    va_start(args, msg);
    char buffer[LOG_BUFFER_SIZE];
    vsnprintf(buffer, LOG_BUFFER_SIZE, msg, args);
    std::string msg_str(buffer);
    std::cout << tag << ": " << msg_str << std::endl;
}

void Log::e(const char* tag, const char* msg, ...) {
    va_list args;
    va_start(args, msg);
    char buffer[LOG_BUFFER_SIZE];
    vsnprintf(buffer, LOG_BUFFER_SIZE, msg, args);
    std::cerr << tag << ": " << buffer << std::endl;
}
/**
 * END DEBUG section
 */
#else
void Log::d(const char* tag, const char* msg, ...) {}

void Log::e(const char* tag, const char* msg, ...) {}
#endif

class Map {
    private:
        sf::RectangleShape mGround;
        const sf::Vector2f* mRenderPosition;
        sf::RectangleShape mSky;
        const sf::Vector2f* mMapSize;
    public:
        Map(float width, float height) 
            :mGround()
            ,mSky()
        {
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
            
        }

        ~Map() {
            delete mMapSize;
            delete mRenderPosition;
        }
        void render(sf::RenderWindow& window) {
            window.draw(mGround);
            window.draw(mSky);
        }

        void setPosition(float x, float y) {
            delete mRenderPosition;
            mRenderPosition = new sf::Vector2f(x, y);
            mSky.setPosition(mRenderPosition->x, mRenderPosition->y);
            mGround.setPosition(mRenderPosition->x, mRenderPosition->y + (mMapSize->y/4 * 3));
        }

        sf::Vector2f getStartPosition() {
            float startX = mRenderPosition->x + 20;
            float startY = mMapSize->y/4 * 3;
            sf::Vector2f result(startX, startY);
            return result;
        }
};

class Player {
        sf::CircleShape mPlayerShape;
        int mJumpValue;
        bool mIsMovingLeft;
        bool mIsMovingRight;
        float mPlayerSpeed;
    public:
        Player(float size, int playerSpeed): mPlayerShape(size/2) 
        {
            mPlayerSpeed = playerSpeed;
            mIsMovingRight = false;
            mIsMovingRight = false;
            mJumpValue = 0;
        }

        void setPlayerColor(sf::Color& color) {
            mPlayerShape.setFillColor(color);
        }

        void setPosition(float x, float y) {
            mPlayerShape.setPosition(x, y);
        }

        void move(float offsetX, float offsetY) {
            mPlayerShape.move(offsetX, offsetY);
        }

        void move(const sf::Vector2f& offset) {
            mPlayerShape.move(offset);
        }

        void update(sf::Time deltaTime) {
            sf::Vector2f movement(0.f, 0.f);
            //Log::d(TAG, "up: %i", mIsJump);
            //Log::d(TAG,"up: %i", mIsMovingLeft);
            //Log::d(TAG, "up: %i", mIsMovingRight);

            if (mIsMovingLeft)
                movement.x -= mPlayerSpeed;
            if (mIsMovingRight)
                movement.x += mPlayerSpeed;
            
            movement.y -= mJumpValue;
            mPlayerShape.move(movement * deltaTime.asSeconds());

        }

        void render(sf::RenderWindow& window) {
            window.draw(mPlayerShape);
        }

        void jump() {
            mJumpValue = DEFAULT_PLAYER_JUMP;
        }

        void left(bool pressed) {
            mIsMovingLeft = pressed;
        }

        void right(bool pressed) {
            mIsMovingRight = pressed;
        }
};

class Game {
    private:
        sf::RenderWindow mWindow;
        sf::Time mTimePerFrame;
        Player mPlayer;
        Map mMap;
        sf::Font mFont;
        sf::Text mPlayerPoints;
        sf::Color mColor;
    public:
    Game() 
        :mWindow(sf::VideoMode(800, 600), APP_TITLE)
        ,mPlayer(DEFAULT_PLAYER_SIZE, DEFAULT_PLAYER_SPEED)
        ,mColor(sf::Color::Black)
        ,mFont()
        ,mPlayerPoints()
        ,mMap(800, 600)
    {   
        
        mTimePerFrame = sf::seconds(1.f / FPS);
        mFont.loadFromFile("font/Sansation.ttf");
        mPlayerPoints.setFont(mFont);
        mPlayerPoints.setString("0:0");
        mPlayerPoints.setColor(sf::Color::White);
        mPlayerPoints.setStyle(sf::Text::Bold);
        mPlayerPoints.setPosition(5.f, 5.f);
        mPlayerPoints.setCharacterSize(20);
        mMap.setPosition(0, 0);
    }

    void run() 
    {
        sf::Clock clock;
        sf::Time sinceLastUpdate = sf::Time::Zero;
        mPlayer.setPlayerColor(mColor);
        sf::Vector2f startPos = mMap.getStartPosition();
        Log::d(TAG, "run: startPosition: x = %.2f; y = %.2f", startPos.x, startPos.y);
        mPlayer.setPosition(startPos.x, startPos.y - 20);

        while (mWindow.isOpen())
        {      
            checkEvents();
            sinceLastUpdate += clock.restart();
		    while (sinceLastUpdate > mTimePerFrame)
		    {
                sinceLastUpdate -= mTimePerFrame;
                checkEvents();
                update(mTimePerFrame);
            }
            mWindow.clear();
            mMap.render(mWindow);
            mPlayer.render(mWindow);
            mWindow.draw(mPlayerPoints);
            mWindow.display();
        }
    }

    private:
        void checkEvents() {
            sf::Event event;
            while (mWindow.pollEvent(event))
            {
                switch (event.type) {
                    case sf::Event::Closed:
                        mWindow.close();
                        break;
                    case sf::Event::KeyPressed:
				        handlePlayerInput(event.key.code, true);
				        break;
			        case sf::Event::KeyReleased:
				        handlePlayerInput(event.key.code, false);
                        break;
                }      
            }
        }

        void handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
            switch(key) {
                case sf::Keyboard::Space:
                    mPlayer.jump();
                    break;
                case sf::Keyboard::S:
                    break;
                case sf::Keyboard::A:
                    mPlayer.left(isPressed);
                    break;
                case sf::Keyboard::D:
                    mPlayer.right(isPressed);
                    break;
                case sf::Keyboard::L:
                    mColor = nextColor(isPressed);
                    break;
            }
        }

        void update(sf::Time deltaTime)
        {
            mPlayer.update(deltaTime);
            mPlayer.setPlayerColor(mColor);
        }

        sf::Color nextColor(bool isPressed) {
            return isPressed ? sf::Color::Red : sf::Color::Green;
        }
};

int main()
{
    Game g;
    g.run();

    return 0;
}