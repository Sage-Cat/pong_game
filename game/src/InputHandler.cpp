#include "InputHandler.hpp"

#include <stdexcept>

InputHandler::InputHandler(GLFWwindow *window) : window_(window)
{
    if (!window_)
    {
        throw std::invalid_argument("InputHandler requires a valid GLFW window");
    }
    setupCallbacks();
}

void InputHandler::setupCallbacks()
{
    glfwSetKeyCallback(window_, keyCallback);
    glfwSetWindowUserPointer(window_, this);
}

void InputHandler::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    (void)scancode;
    (void)mods;
    // Retrieve the instance from the window user pointer and forward the event to the instance method
    auto handler = static_cast<InputHandler *>(glfwGetWindowUserPointer(window));
    if (handler)
    {
        handler->handleKeyPress(key, action);
    }
}

void InputHandler::handleKeyPress(int key, int action) const
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window_, GLFW_TRUE);
    }
}

namespace
{
float directionForKeys(GLFWwindow *window, int upKey, int downKey)
{
    const bool up = glfwGetKey(window, upKey) == GLFW_PRESS;
    const bool down = glfwGetKey(window, downKey) == GLFW_PRESS;
    return static_cast<float>(up) - static_cast<float>(down);
}
}

float InputHandler::leftPaddleDirection() const
{
    return directionForKeys(window_, GLFW_KEY_W, GLFW_KEY_S);
}

float InputHandler::rightPaddleDirection() const
{
    return directionForKeys(window_, GLFW_KEY_UP, GLFW_KEY_DOWN);
}
