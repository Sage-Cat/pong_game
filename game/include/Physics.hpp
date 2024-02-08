#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include "GameObject.hpp"
#include "Ball.hpp"   // Assuming Ball is a derived class of GameObject
#include "Paddle.hpp" // Assuming Paddle is also a derived class
#include <vector>

class Physics
{
public:
    Physics();
    void update(std::vector<GameObject *> &objects);

private:
    bool detectCollision(const GameObject *obj1, const GameObject *obj2) const;
    void resolveCollision(Ball *ball, Paddle *paddle);
    void checkWallCollisions(Ball *ball, const int screenHeight, const int screenWidth);
};

#endif // PHYSICS_HPP
