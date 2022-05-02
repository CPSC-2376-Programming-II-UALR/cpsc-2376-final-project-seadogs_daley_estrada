#include "Object.h"
#include "Block.h"
#include "Player.h"
#include "GUI.h"
#include "HealthBar.h"
//Comment for push

Object::Object(Vector2D position, Type name, const std::unique_ptr<GUI>& gui):position(position), name(name), gui(gui)
{
}

Object::~Object()
{
}

Vector2D Object::getPosition() const
{
	return position;
}

void Object::setPosition(Vector2D newPosition)
{
	position = newPosition;
}

Vector2D Object::getDimensions() const
{
	return gui->getDimensions(this);
}

Object::Type Object::getName() const
{
	return name;
}
