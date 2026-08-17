#ifndef WINDOW_MANAGER_HPP
#define WINDOW_MANAGER_HPP

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <string>

class WindowManager
{
public:
    WindowManager(int width, int height, const char *title);
    ~WindowManager();
    WindowManager(const WindowManager &) = delete;
    WindowManager &operator=(const WindowManager &) = delete;
    WindowManager(WindowManager &&) = delete;
    WindowManager &operator=(WindowManager &&) = delete;

    bool init();
    void shutdown();
    GLFWwindow *getWindow() const;
    bool shouldClose() const;
    void swapBuffers() const;
    void pollEvents() const;
    void setTitle(const std::string &title) const;

private:
    GLFWwindow *window_;
    bool glfwInitialized_;
    const int width_;
    const int height_;
    const char *title_;
};

#endif // WINDOW_MANAGER_HPP
