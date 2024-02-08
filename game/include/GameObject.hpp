#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <glm/glm.hpp>

class GameObject
{
public:
    GameObject(const glm::vec2 &pos, const glm::vec2 &size, const glm::vec2 &velocity);

    void setPosition(const glm::vec2 &pos);
    void setSize(const glm::vec2 &size);
    void setVelocity(const glm::vec2 &velocity);

    glm::vec2 getPosition() const;
    glm::vec2 getSize() const;
    glm::vec2 getVelocity() const;

    // basic movement mechanism
    virtual void update(float dt);

protected:
    glm::vec2 position_;
    glm::vec2 size_;
    glm::vec2 velocity_;
};

#endif // GAMEOBJECT_HPP
