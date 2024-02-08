#include "Paddle.hpp"

#include "GameConfig.hpp"

Paddle::Paddle(const glm::vec2 &pos, const glm::vec2 &size, const glm::vec2 &velocity)
    : GameObject(pos, size, velocity) {}

// Update method implementation might include constraining the paddle within the game boundaries.
void Paddle::update(float dt)
{
    // Handle basic movement
    GameObject::update(dt);

    // Boundary constraint logic
    if (position_.y < 0.0f)
    {
        position_.y = 0.0f;
    }
    else if (position_.y + size_.y > GameConfig::WINDOW_WIDTH)
    {
        position_.y = static_cast<float>(GameConfig::WINDOW_WIDTH) - size_.y;
    }
}
