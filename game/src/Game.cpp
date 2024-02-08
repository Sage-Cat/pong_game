#include "Game.hpp"
#include "SpdlogConfig.hpp"
#include <spdlog/spdlog.h>

Game::Game(const int windowWidth, const int windowHeight, const char *windowTitle)
    : windowWidth_(windowWidth),
      windowHeight_(windowHeight),
      windowTitle_(windowTitle),
      window(nullptr)
{
    if (!initializeWindow())
    {
        SPDLOG_CRITICAL("Failed to initialize GLFW window");
        throw std::runtime_error("Failed to initialize GLFW window");
    }
}

Game::~Game()
{
    cleanup();
}

bool Game::initializeWindow()
{
    SPDLOG_INFO("Initializing GLFW");
    if (!glfwInit())
    {
        SPDLOG_CRITICAL("Failed to initialize GLFW");
        return false;
    }

    window = glfwCreateWindow(windowWidth_, windowHeight_, windowTitle_, nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    return true;
}

void Game::run()
{
    mainLoop();
}

void Game::mainLoop()
{
    while (!glfwWindowShouldClose(window))
    {
        update();
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Game::update()
{
    // Update game objects
}

void Game::render()
{
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Render game objects
}

void Game::cleanup()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}
