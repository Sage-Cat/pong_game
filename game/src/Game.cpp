#include "Game.hpp"

#include <algorithm>
#include <string>

#include "GameConfig.hpp"

Game::Game()
    : windowManager_(GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT, GameConfig::WINDOW_TITLE),
      inputHandler_(windowManager_.getWindow()),
      renderer_(GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT),
      leftPaddle_({30.0f, 190.0f}, {15.0f, 100.0f}),
      rightPaddle_({595.0f, 190.0f}, {15.0f, 100.0f}),
      ball_({312.5f, 232.5f}, {15.0f, 15.0f}, {250.0f, 160.0f})
{
    renderer_.init();
    updateTitle();
}

void Game::run(std::size_t frameLimit)
{
    double previousTime = glfwGetTime();
    std::size_t renderedFrames = 0;
    while (!windowManager_.shouldClose() && (frameLimit == 0 || renderedFrames < frameLimit))
    {
        const double now = glfwGetTime();
        const float deltaTime = std::min(static_cast<float>(now - previousTime), 0.05f);
        previousTime = now;

        windowManager_.pollEvents();
        update(deltaTime);
        render();
        windowManager_.swapBuffers();
        ++renderedFrames;
    }
}

void Game::update(float deltaTime)
{
    constexpr float paddleSpeed = 320.0f;
    leftPaddle_.setVelocity({0.0f, inputHandler_.leftPaddleDirection() * paddleSpeed});
    rightPaddle_.setVelocity({0.0f, inputHandler_.rightPaddleDirection() * paddleSpeed});

    leftPaddle_.update(deltaTime);
    rightPaddle_.update(deltaTime);
    ball_.update(deltaTime);

    const auto scoreEvent = physics_.update(ball_, {&leftPaddle_, &rightPaddle_});
    if (scoreEvent == Physics::ScoreEvent::LeftPlayer)
    {
        score_.scoreLeft();
        resetBall(1.0f);
        updateTitle();
    }
    else if (scoreEvent == Physics::ScoreEvent::RightPlayer)
    {
        score_.scoreRight();
        resetBall(-1.0f);
        updateTitle();
    }
}

void Game::render()
{
    renderer_.clear();
    renderer_.drawPaddle(leftPaddle_);
    renderer_.drawPaddle(rightPaddle_);
    renderer_.drawBall(ball_);
}

void Game::resetBall(float horizontalDirection)
{
    ball_.setPosition({312.5f, 232.5f});
    ball_.setVelocity({horizontalDirection * 250.0f, 160.0f});
}

void Game::updateTitle()
{
    windowManager_.setTitle(std::string(GameConfig::WINDOW_TITLE) + " - " +
                            std::to_string(score_.left()) + " : " +
                            std::to_string(score_.right()));
}
