#include <GL/glew.h>

#include "WindowManager.hpp"

#include <spdlog/spdlog.h>

#include <stdexcept>

WindowManager::WindowManager(int width, int height, const char *title)
    : window_(nullptr), glfwInitialized_(false), width_(width), height_(height), title_(title)
{
    if (!init())
    {
        throw std::runtime_error("Unable to initialize the OpenGL window");
    }
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
        return false;
    }
    glfwInitialized_ = true;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    window_ = glfwCreateWindow(width_, height_, title_, nullptr, nullptr);
    if (!window_)
    {
        SPDLOG_CRITICAL("Failed to create GLFW window");
        shutdown();
        return false;
    }

    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    const GLenum glewStatus = glewInit();
    if (glewStatus != GLEW_OK)
    {
        SPDLOG_CRITICAL("Failed to initialize GLEW: {}",
                       reinterpret_cast<const char *>(glewGetErrorString(glewStatus)));
        shutdown();
        return false;
    }

    // GLEW may generate GL_INVALID_ENUM while probing a core profile.
    glGetError();
    glViewport(0, 0, width_, height_);
    return true;
}

void WindowManager::shutdown()
{
    if (window_)
    {
        glfwDestroyWindow(window_);
        window_ = nullptr;
    }
    if (glfwInitialized_)
    {
        glfwTerminate();
        glfwInitialized_ = false;
    }
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

void WindowManager::setTitle(const std::string &title) const
{
    glfwSetWindowTitle(window_, title.c_str());
}
