#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

constexpr int windowWidth{800}, windowHeight{600};
constexpr float ballRadius{10.f}, ballVelocity{4.f};

constexpr float paddleWidth{60.f}, paddleHeight{20.f}, paddleVelocity{6.f};
constexpr float brickWidth{60.f}, brickHeight{20.f};
constexpr int countBlocksX{11}, countBlocksY{4};

struct Ball 
{
    CircleShape shape;

    Vector2f velocity{-ballVelocity, -ballVelocity};

    Ball(float x, float y) {
        shape.setPosition(x, y);
        shape.setRadius(ballRadius);
        shape.setFillColor(Color::Red);
        shape.setOrigin(ballRadius, ballRadius);
    }

    void update() 
    { 
        shape.move(velocity); 

        if (left() < 0) velocity.x = ballVelocity;
        else if (right() > windowWidth) velocity.x = -ballVelocity;

        if (top() < 0) velocity.y = ballVelocity;
        else if (bottom() > windowHeight) velocity.y = -ballVelocity;
    }

    float x() { return shape.getPosition().x;}
    float y() { return shape.getPosition().y;}
    float left() { return x() - shape.getRadius();}
    float right() { return x() + shape.getRadius();}
    float top() { return y() - shape.getRadius();}
    float bottom() { return y() + shape.getRadius();}
};

struct Paddle
{
    RectangleShape shape;
    Vector2f velocity;

    Paddle(float x, float y)
    {
        shape.setPosition(x, y);
        shape.setSize({paddleWidth, paddleHeight});
        shape.setFillColor(Color::Red);
        shape.setOrigin(paddleWidth / 2.f, paddleHeight / 2.f);
    }

    void update()
    {
        shape.move(velocity);

        if (Keyboard::isKeyPressed(Keyboard::Key::Left) && left() > 0) 
            velocity.x = -paddleVelocity;
        else if(Keyboard::isKeyPressed(Keyboard::Key::Right) && right() < windowWidth) 
            velocity.x = paddleVelocity;
        else 
            velocity.x = 0;
    }

    float x() { return shape.getPosition().x; }
    float y() { return shape.getPosition().y; }
    float left() { return x() - shape.getSize().x / 2.f; }
    float right() { return x() + shape.getSize().x / 2.f; }
    float top() { return y() - shape.getSize().y / 2.f; }
    float bottom() { return y() + shape.getSize().y / 2.f; }
};

struct Brick
{
    RectangleShape shape;
    Vector2f velocity;

    bool destroyed{false};

    Brick(float x, float y)
    {
        shape.setPosition(x, y);
        shape.setSize({brickWidth, brickHeight});
        shape.setFillColor(Color::Yellow);
        shape.setOrigin(brickWidth / 2.f, brickHeight / 2.f);
    }

    float x() { return shape.getPosition().x; }
    float y() { return shape.getPosition().y; }
    float left() { return x() - shape.getSize().x / 2.f; }
    float right() { return x() + shape.getSize().x / 2.f; }
    float top() { return y() - shape.getSize().y / 2.f; }
    float bottom() { return y() + shape.getSize().y / 2.f; }
};

struct Game {
    RenderWindow window;
    Ball ball;
    Paddle paddle;
    vector<Brick> bricks;

    Game() 
    : ball{windowWidth / 2, windowHeight / 2}
    , paddle{windowWidth / 2.f, windowHeight - 50}
    , window{{windowWidth, windowHeight}, "Arkanoid - 6"}
    {

        for(int iX{0}; iX < countBlocksX; ++iX) {
            for(int iY{0}; iY < countBlocksY; ++iY) {
                bricks.emplace_back((iX + 1) * (brickWidth + 3) + 22,
                    (iY + 2) * (brickHeight + 3));
            } 
        }

        window.setFramerateLimit(60);
    }

    void run() {
        while(window.isOpen()) {
            window.clear(Color::Black);

            if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) break;

            ball.update();
            paddle.update();

            testCollision(paddle, ball);
            for(auto& brick : bricks) 
                testCollision(brick, ball);
            bricks.erase(remove_if(begin(bricks), end(bricks),
                            [](const Brick& mBrick)
                            {
                                return mBrick.destroyed;
                            }),
                end(bricks));
            // Redner block
            window.draw(ball.shape);
            window.draw(paddle.shape);

            for(auto& brick : bricks) 
                window.draw(brick.shape);
            window.display();
        }
    }

    template<class T1, class T2> bool isIntersecting(T1& mA, T2& mB) {
        return mA.right() >= mB.left() && mA.left() <= mB.right() 
            && mA.bottom() >= mB.top() && mA.top() <= mB.bottom();
    }

    void testCollision(Paddle& paddle, Ball& ball) {
        if (!isIntersecting(paddle, ball)) return;

        ball.velocity.y = -ballVelocity;

        if(ball.x() < paddle.x())
            ball.velocity.x = -ballVelocity;
        else 
            ball.velocity.x = ballVelocity;
    }

    void testCollision(Brick& brick, Ball& ball) {
        if (!isIntersecting(brick, ball)) return;

        brick.destroyed = true;

        float overlapLeft{ball.right() - brick.left()};
        float overlapRight{brick.right() - ball.left()};
        float overlapTop{ball.bottom() - brick.top()};
        float overlapBottom{brick.bottom() - ball.top()};

        bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
        bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

        float minOverlapX{ballFromLeft ? overlapLeft : overlapRight};
        float minOverlapY{ballFromTop ? overlapTop : overlapBottom};

        if(abs(minOverlapX) < abs(minOverlapY))
            ball.velocity.x = ballFromLeft ? -ballVelocity : ballVelocity;
        else
            ball.velocity.y = ballFromTop ? -ballVelocity : ballVelocity;

    }
};