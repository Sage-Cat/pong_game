#include <GLFW/glfw3.h>

#include "SpdlogConfig.hpp"

#include "Game.hpp"

int main()
{
    SpdlogConfig::init();

    try
    {
        Game game;
        game.run();
    }
    catch (const std::exception &e)
    {
        SPDLOG_CRITICAL("Exception caught in main: {}", e.what());
        return -1;
    }

    return 0;
}
