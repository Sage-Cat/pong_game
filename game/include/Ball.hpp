#ifndef BALL_HPP
#define BALL_HPP

#include "GameObject.hpp"

class Ball : public GameObject
{
public:
    Ball(const glm::vec2 &pos, const glm::vec2 &size, const glm::vec2 &velocity);

    void update(float dt) override;
};

#endif // BALL_HPP
