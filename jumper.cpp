#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

constexpr float FPS{60.f};
constexpr int COLISION_LOOP{8};
constexpr int windowWidth{800}, windowHeight{600};
constexpr int maxYPos{windowHeight + 1000};
constexpr float jumperRadius{10.f}, jumperVelocity{180.f}, moveVelocity{10.f};
constexpr float platformWidth{60.f}, platformHeight{20.f};
constexpr float gravityVelocity{20.f};
constexpr float moveSpeed{8};
constexpr float jumpSpeed{10};
constexpr int UP{-30};
constexpr int DOWN{30};

template<class T1, class T2> bool isIntersecting(T1& mA, T2& mB, Vector2f moveVector) {
    return mA.right() >= mB.left() + moveVector.x && mA.left() <= mB.right() + moveVector.x
        && mA.bottom() >= mB.top() + moveVector.y && mA.top() <= mB.bottom() + moveVector.y;
}

struct Platform 
{
    RectangleShape shape;

    bool destroyed{false};

    Platform(float x, float y)
    {
        shape.setPosition(x, y);
        shape.setSize({platformWidth, platformHeight});
        shape.setFillColor(Color::Yellow);
        //shape.setOrigin(platformWidth / 2.f, platformHeight / 2.f);
    }

    void draw(RenderWindow& window) {
        window.draw(shape);
    }

    float x() { return shape.getPosition().x; }
    float y() { return shape.getPosition().y; }
    float left() { return x(); }
    float right() { return x() + shape.getSize().x; }
    float top() { return y(); }
    float bottom() { return y() + shape.getSize().y; }

    void hit(bool isHit) {
        shape.setFillColor(isHit ? Color::Magenta : Color::Yellow);
    }
};

struct ObjectManager {
    vector<Platform> platforms;

    ObjectManager()
    {
        platforms.emplace_back(150.f, 40.f);
        platforms.emplace_back(20.f, 90.f);
        platforms.emplace_back(120.f, 90.f);
        platforms.emplace_back(320.f, 90.f);
        platforms.emplace_back(200.f, 240.f);
        platforms.emplace_back(400.f, 240.f);
        platforms.emplace_back(620.f, 240.f);
        platforms.emplace_back(100.f, 340.f);
        platforms.emplace_back(200.f, 340.f);
        platforms.emplace_back(150.f, 420.f);
        platforms.emplace_back(300.f, 420.f);
        platforms.emplace_back(550.f, 420.f);
        platforms.emplace_back(380.f, 560.f);


        platforms.emplace_back(150.f, 640.f);
        platforms.emplace_back(20.f, 690.f);
        platforms.emplace_back(120.f, 690.f);
        platforms.emplace_back(320.f, 690.f);
        platforms.emplace_back(200.f, 840.f);
        platforms.emplace_back(400.f, 840.f);
        platforms.emplace_back(620.f, 840.f);
        platforms.emplace_back(100.f, 940.f);
        platforms.emplace_back(200.f, 940.f);

        platforms.emplace_back(150.f, 1240.f);
        platforms.emplace_back(20.f, 1290.f);
        platforms.emplace_back(120.f, 1290.f);
        platforms.emplace_back(320.f, 1290.f);
        platforms.emplace_back(200.f, 1440.f);
        platforms.emplace_back(400.f, 1440.f);
        platforms.emplace_back(620.f, 1440.f);
        platforms.emplace_back(100.f, 1540.f);
        platforms.emplace_back(200.f, 1540.f);
    }
};

struct Jumper {
    CircleShape shape;

    Vector2f velocity{0, 0};
    Vector2f moveVector{0, 0};
    Vector2f gravity{0, gravityVelocity};
    float jumpUsed = 0;
    bool mJumpLock = false;
    int jumpSeq = 0;

    Jumper(float x, float y) {
        shape.setPosition(x, y);
        shape.setRadius(jumperRadius);
        shape.setFillColor(Color::Red);
        shape.setOrigin(jumperRadius, jumperRadius);
    }

    void update(ObjectManager& manager, float dt) 
    { 
        
        float gravityV = gravity.y;
        //setGravity
        if (bottom() + gravityV * dt * moveSpeed <= maxYPos) {
            velocity.y = gravityV * dt * moveSpeed; 
        } else {
            velocity.y = maxYPos - bottom();
        }

        if (moveVector.y > 0) {
            velocity.y -= moveVector.y * dt * jumpSpeed;
            jumpUsed += moveVector.y * dt * jumpSpeed;
            if (jumpUsed > moveVector.y) {
                moveVector.y = 0;
            }
        }

        if (moveVector.x != 0) 
        {
            velocity.x = moveVector.x * dt * moveSpeed;
        } 
        else 
        {
            velocity.x = 0;
        }
       
        for(auto& platform : manager.platforms) 
        {
            bool hit = isIntersecting(platform, *this, velocity);
            platform.hit(hit);
            if (hit) 
            {
                if (platform.top() > bottom() && platform.top() < bottom() + velocity.y) 
                {
                    velocity.y = platform.top() - (bottom() + 1);
                } 
                else if (platform.bottom() < top() && platform.bottom() > top() + velocity.y) {
                    velocity.y = platform.bottom() - (top() - 1);
                } 

                if (platform.left() > right() && platform.left() < right() + velocity.x) 
                {
                    velocity.x = platform.left() - (right() + 1);
                } 
                else if (platform.right() < left() && platform.right() > left() + velocity.x) {
                    velocity.x = platform.right() - (left() - 1);
                } 
            }
        }
        
        if (velocity.y == 0) {
            jumpSeq = 0;
        }
        shape.move(velocity);
    }

    void draw(RenderWindow& window) {
        window.draw(shape);
    }

    void jump(bool isPressed) {
        if ((isPressed && mJumpLock)) {
            return;
        } else if (!isPressed) {
            mJumpLock = false;
            return;
        }
        if (jumpSeq >= 2) {
            return;
        }
        jumpSeq++;
        mJumpLock = true;
        moveVector.y = jumperVelocity;
        jumpUsed = 0;
    }

    void moveToLeft(bool isPressed) {
        if (isPressed) {
            moveVector.x = -moveVelocity;
        } else {
            moveVector.x = 0;
        }
    }

    void moveToRight(bool isPressed) {
        if (isPressed) {
            moveVector.x = moveVelocity;
        } else {
            moveVector.x = 0;
        }
    }

    float x() { return shape.getPosition().x;}
    float y() { return shape.getPosition().y;}
    float left() { return x() - shape.getRadius();}
    float right() { return x() + shape.getRadius();}
    float top() { return y() - shape.getRadius();}
    float bottom() { return y() + shape.getRadius();}
};

struct Game {
    RenderWindow mWindow;
    View camera;
    Jumper jumper;
    ObjectManager manager;

    Game() 
        : mWindow{{windowWidth, windowHeight}, "Jumper"}
        , jumper{windowWidth / 2, windowHeight / 2}
    {
        camera.setSize({windowWidth, windowHeight});
        camera.setCenter(windowWidth / 2, windowHeight / 2);
        mWindow.setView(camera);
    }

    void run()
    {
        sf::Clock clock;
        
        sf::Time sinceLastUpdate = sf::Time::Zero;
        mWindow.setFramerateLimit(FPS);
        float lastTime = 0;
        float currTime = 0;
        while (mWindow.isOpen())
        {      
            checkEvents();
            sinceLastUpdate += clock.restart();
            currTime = sinceLastUpdate.asSeconds();

            jumper.update(manager, currTime - lastTime);

            if (jumper.top() < windowHeight / 4.f)
            {
                updateCamera(UP);
            } 
            else if (jumper.top() > camera.getCenter().y)
            {
                updateCamera(DOWN);
            }
            lastTime = currTime;
            mWindow.clear();
            jumper.draw(mWindow);
            for(auto& platform : manager.platforms) 
                platform.draw(mWindow);
            mWindow.display();
        }
    }

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
                jumper.jump(isPressed);
                break;
            case sf::Keyboard::S:
                break;
            case sf::Keyboard::A:
                jumper.moveToLeft(isPressed);
                break;
            case sf::Keyboard::D:
                jumper.moveToRight(isPressed);
                break;
            case sf::Keyboard::L:
                //mColor = nextColor(isPressed);
                break;
        }
    }

    void updateCamera(int value) 
    {
        if (camera.getCenter().y + value + windowHeight / 2 < maxYPos) 
        {
            cout << "move camera: " << value << endl;
            camera.move(0, value);
            mWindow.setView(camera);
        }
        
    }
};