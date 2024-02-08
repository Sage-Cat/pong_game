#include "Physics.hpp"

#include <spdlog/spdlog.h>

#include "GameConfig.hpp"

Physics::Physics() {}

void Physics::update(std::vector<GameObject *> &objects)
{
    Ball *ball = nullptr;
    std::vector<Paddle *> paddles;

    // Partition the objects for easier processing
    for (auto &obj : objects)
    {
        if (auto p = dynamic_cast<Ball *>(obj))
        {
            ball = p;
        }
        else if (auto p = dynamic_cast<Paddle *>(obj))
        {
            paddles.push_back(p);
        }
    }

    // Check ball against paddles
    for (auto &paddle : paddles)
    {
        if (detectCollision(ball, paddle))
        {
            resolveCollision(ball, paddle);
        }
    }

    // Check for wall collisions
    checkWallCollisions(ball, GameConfig::WINDOW_HEIGHT, GameConfig::WINDOW_WIDTH);
}

bool Physics::detectCollision(const GameObject *obj1, const GameObject *obj2) const
{
    // AABB collision detection
    bool collisionX = obj1->getPosition().x + obj1->getSize().x >= obj2->getPosition().x &&
                      obj2->getPosition().x + obj2->getSize().x >= obj1->getPosition().x;
    bool collisionY = obj1->getPosition().y + obj1->getSize().y >= obj2->getPosition().y &&
                      obj2->getPosition().y + obj2->getSize().y >= obj1->getPosition().y;
    return collisionX && collisionY;
}

void Physics::resolveCollision(Ball *ball, Paddle *paddle)
{
    // Basic collision resolution for Pong: simply invert ball's Y velocity
    ball->setVelocity(glm::vec2(ball->getVelocity().x, -ball->getVelocity().y));
    SPDLOG_INFO("Ball collision with paddle resolved.");
}

void Physics::checkWallCollisions(Ball *ball, const int screenHeight, const int screenWidth)
{
    if (ball->getPosition().y <= 0 || ball->getPosition().y + ball->getSize().y >= screenHeight)
    {
        // Ball hits top or bottom wall
        ball->setVelocity(glm::vec2(ball->getVelocity().x, -ball->getVelocity().y));
        SPDLOG_INFO("Ball collision with wall resolved.");
    }

    if (ball->getPosition().x <= 0 || ball->getPosition().x + ball->getSize().x >= screenWidth)
    {
        // Ball hits left or right wall, could reset ball position or handle scoring
        // For simplicity, just invert X velocity here
        ball->setVelocity(glm::vec2(-ball->getVelocity().x, ball->getVelocity().y));
        SPDLOG_INFO("Ball collision with side wall resolved.");
    }
}
