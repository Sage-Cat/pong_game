#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class InputHandler
{
public:
    InputHandler(GLFWwindow *window);
    void setupCallbacks();
    float leftPaddleDirection() const;
    float rightPaddleDirection() const;

private:
    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    void handleKeyPress(int key, int action) const;

private:
    GLFWwindow *window_;
};

#endif // INPUTHANDLER_HPP
