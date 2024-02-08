#include "InputHandler.hpp"

#include <spdlog/spdlog.h>

InputHandler::InputHandler(GLFWwindow *window) : window_(window)
{
    setupCallbacks();
}

void InputHandler::setupCallbacks()
{
    glfwSetKeyCallback(window_, keyCallback);
    glfwSetWindowUserPointer(window_, this);
}

void InputHandler::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    // Retrieve the instance from the window user pointer and forward the event to the instance method
    auto handler = static_cast<InputHandler *>(glfwGetWindowUserPointer(window));
    if (handler)
    {
        handler->handleKeyPress(key, action);
    }
}

void InputHandler::handleKeyPress(int key, int action)
{
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        switch (key)
        {
        case GLFW_KEY_UP:
            SPDLOG_INFO("Up key pressed");
            // Handle up movement
            break;
        case GLFW_KEY_DOWN:
            SPDLOG_INFO("Down key pressed");
            // Handle down movement
            break;
        // Add more cases as needed for other keys
        default:
            break;
        }
    }
}
