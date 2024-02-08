#include "GameObject.hpp"

GameObject::GameObject(const glm::vec2 &pos, const glm::vec2 &size, const glm::vec2 &velocity)
    : position_(pos), size_(size), velocity_(velocity) {}

void GameObject::setPosition(const glm::vec2 &pos)
{
    position_ = pos;
}

void GameObject::setSize(const glm::vec2 &size)
{
    size_ = size;
}

void GameObject::setVelocity(const glm::vec2 &velocity)
{
    velocity_ = velocity;
}

glm::vec2 GameObject::getPosition() const
{
    return position_;
}

glm::vec2 GameObject::getSize() const
{
    return size_;
}

glm::vec2 GameObject::getVelocity() const
{
    return velocity_;
}

void GameObject::update(float dt)
{
    position_ += velocity_ * dt;
}
