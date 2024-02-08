#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <GLFW/glfw3.h>

class InputHandler
{
public:
    InputHandler(GLFWwindow *window);
    void setupCallbacks();

private:
    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    void handleKeyPress(int key, int action);

private:
    GLFWwindow *window_;
};

#endif // INPUTHANDLER_HPP