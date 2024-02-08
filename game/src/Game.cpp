#include "Game.hpp"

#include <spdlog/spdlog.h>

#include "GameConfig.hpp"

Game::Game()
    : windowManager_(GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT, GameConfig::WINDOW_TITLE),
      inputHandler_(windowManager_.getWindow())
{
}

Game::~Game()
{
}

void Game::run()
{
    mainLoop();
}

void Game::mainLoop()
{
    while (!windowManager_.shouldClose())
    {
        update();
        render();
        windowManager_.swapBuffers();
        windowManager_.pollEvents();
    }
}

void Game::update()
{
    // Update game objects
}

void Game::render()
{
    // Assuming the context is already made current by WindowManager
    glClear(GL_COLOR_BUFFER_BIT);
    // Render game objects
}
