#include <exception>
#include <string_view>

#include "SpdlogConfig.hpp"

#include "Game.hpp"

int main(int argc, char **argv)
{
    SpdlogConfig::init();

    try
    {
        Game game;
        const bool smokeTest = argc == 2 && std::string_view(argv[1]) == "--smoke-test";
        game.run(smokeTest ? 3U : 0U);
    }
    catch (const std::exception &e)
    {
        SPDLOG_CRITICAL("Exception caught in main: {}", e.what());
        return -1;
    }

    return 0;
}
