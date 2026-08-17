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
    Renderer(const Renderer &) = delete;
    Renderer &operator=(const Renderer &) = delete;
    Renderer(Renderer &&) = delete;
    Renderer &operator=(Renderer &&) = delete;

    void init();
    void drawBall(const Ball &ball);
    void drawPaddle(const Paddle &paddle);
    void clear();

private:
    void setupRenderData();
    GLuint loadShader(const char *shaderPath, GLenum type) const;
    void createShaderProgram();
    void drawObject(const GameObject &object, const glm::vec3 &color) const;

    GLuint VAO_, VBO_;
    GLuint shaderProgram_;
    int windowWidth_, windowHeight_;
};

#endif // RENDERER_HPP
