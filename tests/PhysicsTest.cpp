#include "Ball.hpp"
#include "GameConfig.hpp"
#include "Paddle.hpp"
#include "Physics.hpp"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string_view>

namespace
{
void expect(bool condition, std::string_view message)
{
    if (!condition)
    {
        std::cerr << "FAILED: " << message << '\n';
        std::exit(EXIT_FAILURE);
    }
}

bool nearlyEqual(float lhs, float rhs)
{
    return std::abs(lhs - rhs) < 0.001f;
}
}

int main()
{
    GameObject moving({10.0f, 20.0f}, {5.0f, 5.0f}, {8.0f, -4.0f});
    moving.update(0.5f);
    expect(nearlyEqual(moving.getPosition().x, 14.0f), "object advances on x");
    expect(nearlyEqual(moving.getPosition().y, 18.0f), "object advances on y");

    Paddle paddle({20.0f, 470.0f}, {15.0f, 50.0f}, {0.0f, 100.0f});
    paddle.update(1.0f);
    expect(nearlyEqual(paddle.getPosition().y, 430.0f), "paddle clamps to window height");

    Physics physics;
    Ball wallBall({300.0f, -2.0f}, {15.0f, 15.0f}, {100.0f, -50.0f});
    expect(physics.update(wallBall, {}) == Physics::ScoreEvent::None,
           "missing paddles are handled safely");
    expect(nearlyEqual(wallBall.getPosition().y, 0.0f), "wall collision corrects overlap");
    expect(wallBall.getVelocity().y > 0.0f, "wall collision reflects vertical velocity");

    Paddle leftPaddle({30.0f, 190.0f}, {15.0f, 100.0f});
    Ball paddleBall({40.0f, 220.0f}, {15.0f, 15.0f}, {-250.0f, 10.0f});
    physics.update(paddleBall, {&leftPaddle});
    expect(paddleBall.getVelocity().x > 0.0f, "paddle collision reflects horizontal velocity");
    expect(nearlyEqual(paddleBall.getVelocity().y, 10.0f), "paddle collision preserves vertical velocity");

    Ball scored({static_cast<float>(GameConfig::WINDOW_WIDTH) + 1.0f, 200.0f},
                {15.0f, 15.0f}, {250.0f, 0.0f});
    expect(physics.update(scored, {}) == Physics::ScoreEvent::LeftPlayer,
           "right-side exit scores for left player");

    std::cout << "All pong core tests passed\n";
    return EXIT_SUCCESS;
}
