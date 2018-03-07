#include <SFML/Graphics.hpp>
#include "main.hpp"

/**
 * END CONSTANT SECTION
 */

int main()
{
    GameManager* manager = new GameManager();
    Game g(manager);
    g.run();
    delete manager;
    return 0;
}