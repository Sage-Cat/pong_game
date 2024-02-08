#ifndef GAME_HPP
#define GAME_HPP

#include <GLFW/glfw3.h>

class Game
{
public:
    Game(const int windowWidth, const int windowHeight, const char *windowTitle);
    ~Game();

    void run();

private:
    GLFWwindow *window;

    bool initializeWindow();
    void mainLoop();
    void update();
    void render();
    void cleanup();

private:
    const int windowWidth_;
    const int windowHeight_;
    const char *windowTitle_;
};

#endif // GAME_HPP
