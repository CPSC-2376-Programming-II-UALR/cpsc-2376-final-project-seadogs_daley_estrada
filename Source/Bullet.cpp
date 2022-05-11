#include "Bullet.h"

Bullet::Bullet(Vector2D position, Vector2D direction, int speed, Object::Type name, const std::unique_ptr<GUI>& gui)
    :Block(position, name, gui),direction{ direction }, speed{ speed }
{}

Object* Bullet::copyMe()
{
	return new Bullet(*this);
}

void Bullet::update(Object::Command command, std::vector<std::unique_ptr<Object>>& objects)
{
	position.x += direction.x * speed;
	position.y += direction.y * speed;

}