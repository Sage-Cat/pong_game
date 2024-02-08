#ifndef PADDLE_HPP
#define PADDLE_HPP

#include "GameObject.hpp"

class Paddle : public GameObject
{
public:
    Paddle(const glm::vec2 &pos, const glm::vec2 &size, const glm::vec2 &velocity = glm::vec2(0.0f));

    void update(float dt) override;
};

#endif // PADDLE_HPP
