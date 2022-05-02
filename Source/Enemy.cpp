#include "Enemy.h"
#include "GUI.h"
#include "Player.h"

//Enemy::Enemy(Vector2D position, std::string animationFile, const GUI& gui)
//	:animation(animationFile), objectPart{ Object::Type::enemy, position }
//{
//	position.y = position.y + gui.getDimensions(Object::Type::block).y - gui.getDimensions(name).y;
//}



Enemy::Enemy(std::string animationFile, Vector2D position, const std::unique_ptr<GUI>& gui) : AnimatedObject(animationFile, position, Object::Type::enemy, gui)
{

}

void Enemy::update(Object::Command command, std::vector<std::unique_ptr<Object>>& objects)
{
	for (const auto& object : objects)
	{
		switch (object->getName())
		{
		case Object::Type::player:
			if (position < object->getPosition())
			{
				state = State::stillRight;
			}
			else
			{
				state = State::stillLeft;
			}
			updateSprite();
		}
	}
}
std::unique_ptr<Object> Enemy::copyMe()
{
	return std::make_unique<Enemy>(*this);
}
