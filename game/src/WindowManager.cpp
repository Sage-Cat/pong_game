#include "WindowManager.hpp"

#include <spdlog/spdlog.h>

WindowManager::WindowManager(int width, int height, const char *title)
    : window_(nullptr), width_(width), height_(height), title_(title)
{
    init();
}

WindowManager::~WindowManager()
{
    shutdown();
}

bool WindowManager::init()
{
    if (!glfwInit())
    {
        SPDLOG_CRITICAL("Failed to init GLFW");
    }

    window_ = glfwCreateWindow(width_, height_, title_, nullptr, nullptr);
    if (!window_)
    {
        SPDLOG_CRITICAL("Failed to create GLFW window");
        glfwTerminate();
    }

    glfwMakeContextCurrent(window_);
    return true;
}

void WindowManager::shutdown()
{
    if (window_)
    {
        glfwDestroyWindow(window_);
    }
    glfwTerminate();
}

GLFWwindow *WindowManager::getWindow() const
{
    return window_;
}

bool WindowManager::shouldClose() const
{
    return glfwWindowShouldClose(window_);
}

void WindowManager::swapBuffers() const
{
    glfwSwapBuffers(window_);
}

void WindowManager::pollEvents() const
{
    glfwPollEvents();
}
