#include <GLFW/glfw3.h>

#include "SpdlogConfig.hpp"
#include "GameConfig.hpp"

#include "Game.hpp"

int main()
{
    SpdlogConfig::init(); // Initialize the logging system

    try
    {
        Game pongGame(GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT, GameConfig::WINDOW_TITLE);
        pongGame.run();
    }
    catch (const std::exception &e)
    {
        SPDLOG_CRITICAL("Exception caught in main: {}", e.what());
        return -1;
    }

    return 0;
}
