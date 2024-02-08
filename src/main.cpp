#include <GLFW/glfw3.h>

int main(int argc, char const *argv[])
{
    // Initialize GLFW
    if (!glfwInit())
        return -1;

    const int WINDOW_WIDTH{640}, WINDOW_HEIGHT{480};
    const char *WINDOW_TITLE{"Pong Game"};

    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // Render here

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
