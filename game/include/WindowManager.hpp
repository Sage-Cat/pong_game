#ifndef WindowManager_HPP
#define WindowManager_HPP

#include <GLFW/glfw3.h>

class WindowManager
{
public:
    WindowManager(int width, int height, const char *title);
    ~WindowManager();

    bool init();
    void shutdown();
    GLFWwindow *getWindow() const;
    bool shouldClose() const;
    void swapBuffers() const;
    void pollEvents() const;

private:
    GLFWwindow *window_;
    const int width_;
    const int height_;
    const char *title_;
};

#endif // WindowManager_HPP
