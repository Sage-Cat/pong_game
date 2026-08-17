#include "Physics.hpp"

#include <cmath>

#include "GameConfig.hpp"

Physics::ScoreEvent Physics::update(Ball &ball, const std::vector<Paddle *> &paddles) const
{
    for (const auto *paddle : paddles)
    {
        if (paddle && detectCollision(ball, *paddle))
        {
            resolveCollision(ball, *paddle);
        }
    }

    checkWallCollisions(ball, GameConfig::WINDOW_HEIGHT);

    if (ball.getPosition().x + ball.getSize().x < 0.0f)
    {
        return ScoreEvent::RightPlayer;
    }
    if (ball.getPosition().x > static_cast<float>(GameConfig::WINDOW_WIDTH))
    {
        return ScoreEvent::LeftPlayer;
    }
    return ScoreEvent::None;
}

bool Physics::detectCollision(const GameObject &obj1, const GameObject &obj2) const
{
    // AABB collision detection
    const bool collisionX = obj1.getPosition().x + obj1.getSize().x >= obj2.getPosition().x &&
                            obj2.getPosition().x + obj2.getSize().x >= obj1.getPosition().x;
    const bool collisionY = obj1.getPosition().y + obj1.getSize().y >= obj2.getPosition().y &&
                            obj2.getPosition().y + obj2.getSize().y >= obj1.getPosition().y;
    return collisionX && collisionY;
}

void Physics::resolveCollision(Ball &ball, const Paddle &paddle) const
{
    const bool paddleIsLeft = paddle.getPosition().x < static_cast<float>(GameConfig::WINDOW_WIDTH) / 2.0f;
    const float horizontalSpeed = std::abs(ball.getVelocity().x);

    if ((paddleIsLeft && ball.getVelocity().x < 0.0f) ||
        (!paddleIsLeft && ball.getVelocity().x > 0.0f))
    {
        const float newX = paddleIsLeft
                               ? paddle.getPosition().x + paddle.getSize().x
                               : paddle.getPosition().x - ball.getSize().x;
        ball.setPosition({newX, ball.getPosition().y});
        ball.setVelocity({paddleIsLeft ? horizontalSpeed : -horizontalSpeed,
                          ball.getVelocity().y});
    }
}

void Physics::checkWallCollisions(Ball &ball, const int screenHeight) const
{
    auto position = ball.getPosition();
    auto velocity = ball.getVelocity();

    if (position.y < 0.0f)
    {
        position.y = 0.0f;
        velocity.y = std::abs(velocity.y);
    }
    else if (position.y + ball.getSize().y > static_cast<float>(screenHeight))
    {
        position.y = static_cast<float>(screenHeight) - ball.getSize().y;
        velocity.y = -std::abs(velocity.y);
    }

    ball.setPosition(position);
    ball.setVelocity(velocity);
}
