#include "Ball.hpp"

Ball::Ball(const glm::vec2 &pos, const glm::vec2 &size, const glm::vec2 &velocity)
    : GameObject(pos, size, velocity)
{
}

void Ball::update(float dt)
{
    // Keep it simple for now
    GameObject::update(dt);
}
