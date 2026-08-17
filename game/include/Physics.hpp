#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include "Ball.hpp"
#include "Paddle.hpp"
#include <vector>

class Physics
{
public:
    enum class ScoreEvent
    {
        None,
        LeftPlayer,
        RightPlayer
    };

    ScoreEvent update(Ball &ball, const std::vector<Paddle *> &paddles) const;

private:
    bool detectCollision(const GameObject &obj1, const GameObject &obj2) const;
    void resolveCollision(Ball &ball, const Paddle &paddle) const;
    void checkWallCollisions(Ball &ball, int screenHeight) const;
};

#endif // PHYSICS_HPP
