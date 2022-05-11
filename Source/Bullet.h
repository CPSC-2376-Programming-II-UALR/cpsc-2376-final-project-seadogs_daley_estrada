#ifndef BULLET_H
#define BULLET_H
#include "Block.h"
#include "Object.h"
class Bullet : public Block
{
public:
    Bullet() = delete;
    Bullet(Vector2D position, Vector2D direction, int speed, Object::Type name, const std::unique_ptr<GUI>& gui);
    Object* copyMe() override;
    void update(Object::Command command, std::vector<std::unique_ptr<Object>>& objects);
protected:
    Vector2D direction;
    int speed;


};

#endif // !BULLET_H