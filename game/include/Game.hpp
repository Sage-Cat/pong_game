#ifndef GAME_HPP
#define GAME_HPP

#include "WindowManager.hpp"
#include "InputHandler.hpp"
#include "Renderer.hpp"
#include "Physics.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"
#include "Score.hpp"

#include <cstddef>

class Game
{
public:
    Game();
    void run(std::size_t frameLimit = 0);

private:
    void update(float deltaTime);
    void render();
    void resetBall(float horizontalDirection);
    void updateTitle();

private:
    WindowManager windowManager_;
    InputHandler inputHandler_;
    Renderer renderer_;
    Physics physics_;
    Paddle leftPaddle_;
    Paddle rightPaddle_;
    Ball ball_;
    Score score_;
};

#endif // GAME_HPP
