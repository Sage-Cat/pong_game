#ifndef GAME_HPP
#define GAME_HPP

#include "WindowManager.hpp"
#include "InputHandler.hpp"

class Game
{
public:
    Game();
    ~Game();

    void run();

private:
    void mainLoop();
    void update();
    void render();

private:
    WindowManager windowManager_;
    InputHandler inputHandler_;
};

#endif // GAME_HPP
