#ifndef MAIN_HPP
#define MAIN_HPP

#include "GameManager.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Log.hpp"

/** 
 * CONSTANT SECTION
 */ 
#define TAG "[KGB]"
#define FPS 60.f
#define APP_TITLE "SFML first App"
#define DEFAULT_PLAYER_SPEED 50.f
#define DEFAULT_PLAYER_SIZE 20.f

class Game {
    private:
        sf::RenderWindow mWindow;
        sf::Time mTimePerFrame;
        Player mPlayer;
        Map mMap;
        sf::Font mFont;
        sf::Text mPlayerPoints;
        sf::Color mColor;
        sf::Vector2f mGravity;
        float mGravityPoint;
        GameManager* mManager;
    public:
        Game(GameManager* manager) 
            :mWindow(sf::VideoMode(800, 600), APP_TITLE)
            ,mColor(sf::Color::Black)
            ,mFont()
            ,mPlayerPoints()
            ,mGravity(0.f, 5.f)
            ,mMap(manager, 800, 600)
            ,mPlayer(manager, DEFAULT_PLAYER_SIZE, DEFAULT_PLAYER_SPEED)
        {   
            mManager = manager;
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

        Map getMap() {
            return mMap;
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
                    mPlayer.jump(isPressed);
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

#endif //MAIN_HPP