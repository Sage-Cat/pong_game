
#include "Renderer.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <spdlog/spdlog.h>

#include "Ball.hpp"
#include "Paddle.hpp"

// Utilities for internal use (error handling)
void checkShaderCompileErrors(GLuint shader, const std::string &type);
void checkProgramLinkErrors(GLuint program);

Renderer::Renderer(int windowWidth, int windowHeight)
    : windowWidth_(windowWidth), windowHeight_(windowHeight), VAO_(0), VBO_(0), shaderProgram_(0) {}

Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &VAO_);
    glDeleteBuffers(1, &VBO_);
    if (shaderProgram_)
    {
        glDeleteProgram(shaderProgram_);
    }
}

std::string readShaderFile(const std::string &shaderPath)
{
    std::ifstream shaderFile(shaderPath);
    std::stringstream buffer;
    buffer << shaderFile.rdbuf();
    return buffer.str();
}

GLuint Renderer::loadShader(const char *shaderPath, GLenum type)
{
    std::string shaderCode = readShaderFile(SHADERS_DIR + std::string(shaderPath));
    const char *shaderCodeCStr = shaderCode.c_str();

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderCodeCStr, NULL);
    glCompileShader(shader);

    checkShaderCompileErrors(shader, type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT");

    return shader;
}

void Renderer::createShaderProgram()
{
    GLuint vertexShader = loadShader("vertexShader.glsl", GL_VERTEX_SHADER);
    GLuint fragmentShader = loadShader("fragmentShader.glsl", GL_FRAGMENT_SHADER);

    shaderProgram_ = glCreateProgram();
    glAttachShader(shaderProgram_, vertexShader);
    glAttachShader(shaderProgram_, fragmentShader);
    glLinkProgram(shaderProgram_);

    // Check for linking errors...
    // Omitted for brevity

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Renderer::init()
{
    setupRenderData();
    createShaderProgram();
}

void Renderer::setupRenderData()
{
    // Setup VAO/VBO for a rectangle that can be used to draw the ball and paddles
    GLfloat vertices[] = {
        // Position     // Texture
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f};

    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);
    glBindVertexArray(VAO_);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer::drawBall(const Ball &ball)
{
    // Bind texture, setup transformations, and draw rectangle for the ball
    // Transformation logic and actual draw call omitted for brevity
}

void Renderer::drawPaddle(const Paddle &paddle)
{
    // Similar to drawBall, but may adjust size based on the paddle's dimensions
}

void Renderer::drawScore(int scoreP1, int scoreP2)
{
    // Render score text
    // This requires a text rendering setup, which can be done with libraries like FreeType
    // For simplicity, this step is omitted
}

void Renderer::clear()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void checkShaderCompileErrors(GLuint shader, const std::string &type)
{
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        SPDLOG_ERROR("Shader compilation error ({}): {}", type, infoLog);
    }
}

void checkProgramLinkErrors(GLuint program)
{
    GLint success;
    GLchar infoLog[1024];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 1024, NULL, infoLog);
        SPDLOG_ERROR("Shader program linking error: {}", infoLog);
    }
}
