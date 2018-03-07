#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <vector>

/** 
 * CONSTANT SECTION
 */ 
#define TAG "[KGB]"
#define FPS 60.f
#define APP_TITLE "SFML first App"
#define DEFAULT_PLAYER_SPEED 50.f
#define DEFAULT_PLAYER_SIZE 20.f

class GameManager {
        std::vector<sf::Shape*> mHitBounds;
    public:
        GameManager() : mHitBounds() {
        }

        void addWall(sf::Shape* hitBounds);
        bool hitTest(sf::FloatRect& bounds);
};

#endif //GAME_MANAGER_HPP