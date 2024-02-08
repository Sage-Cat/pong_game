#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GameObject.hpp"

class Ball;
class Paddle;

class Renderer
{
public:
    Renderer(int windowWidth, int windowHeight);
    ~Renderer();

    void init();
    void drawBall(const Ball &ball);
    void drawPaddle(const Paddle &paddle);
    void drawScore(int scoreP1, int scoreP2);
    void clear();

private:
    void setupRenderData();
    GLuint loadShader(const char *shaderPath, GLenum type);
    void createShaderProgram();

    GLuint VAO_, VBO_;
    GLuint shaderProgram_; // Shader program ID
    int windowWidth_, windowHeight_;
};

#endif // RENDERER_HPP
