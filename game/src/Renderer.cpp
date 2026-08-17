
#include "Renderer.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Ball.hpp"
#include "Paddle.hpp"

namespace
{
void checkShaderCompileErrors(GLuint shader, const std::string &type);
void checkProgramLinkErrors(GLuint program);

std::string readShaderFile(const std::string &shaderPath)
{
    std::ifstream shaderFile(shaderPath);
    if (!shaderFile)
    {
        throw std::runtime_error("Unable to read shader: " + shaderPath);
    }

    std::stringstream buffer;
    buffer << shaderFile.rdbuf();
    return buffer.str();
}
}

Renderer::Renderer(int windowWidth, int windowHeight)
    : VAO_(0), VBO_(0), shaderProgram_(0), windowWidth_(windowWidth), windowHeight_(windowHeight) {}

Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &VAO_);
    glDeleteBuffers(1, &VBO_);
    if (shaderProgram_)
    {
        glDeleteProgram(shaderProgram_);
    }
}

GLuint Renderer::loadShader(const char *shaderPath, GLenum type) const
{
    const std::string shaderCode = readShaderFile(PONG_SHADER_DIR + std::string(shaderPath));
    const char *shaderCodeCStr = shaderCode.c_str();

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderCodeCStr, NULL);
    glCompileShader(shader);

    checkShaderCompileErrors(shader, type == GL_VERTEX_SHADER ? "vertex" : "fragment");

    return shader;
}

void Renderer::createShaderProgram()
{
    const GLuint vertexShader = loadShader("vertex_shader.glsl", GL_VERTEX_SHADER);
    const GLuint fragmentShader = loadShader("fragment_shader.glsl", GL_FRAGMENT_SHADER);

    shaderProgram_ = glCreateProgram();
    glAttachShader(shaderProgram_, vertexShader);
    glAttachShader(shaderProgram_, fragmentShader);
    glLinkProgram(shaderProgram_);

    checkProgramLinkErrors(shaderProgram_);

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
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f};

    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);
    glBindVertexArray(VAO_);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer::drawBall(const Ball &ball)
{
    drawObject(ball, {1.0f, 0.85f, 0.2f});
}

void Renderer::drawPaddle(const Paddle &paddle)
{
    drawObject(paddle, {0.95f, 0.95f, 0.95f});
}

void Renderer::clear()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::drawObject(const GameObject &object, const glm::vec3 &color) const
{
    const glm::mat4 projection = glm::ortho(
        0.0f, static_cast<float>(windowWidth_), 0.0f, static_cast<float>(windowHeight_));
    glm::mat4 model{1.0f};
    model = glm::translate(model, glm::vec3(object.getPosition(), 0.0f));
    model = glm::scale(model, glm::vec3(object.getSize(), 1.0f));

    glUseProgram(shaderProgram_);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram_, "projection"), 1, GL_FALSE, &projection[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram_, "model"), 1, GL_FALSE, &model[0][0]);
    glUniform3fv(glGetUniformLocation(shaderProgram_, "objectColor"), 1, &color[0]);
    glBindVertexArray(VAO_);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

namespace
{
void checkShaderCompileErrors(GLuint shader, const std::string &type)
{
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        glDeleteShader(shader);
        throw std::runtime_error("Shader compilation error (" + type + "): " + infoLog);
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
        throw std::runtime_error(std::string("Shader program linking error: ") + infoLog);
    }
}
}
