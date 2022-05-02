#include <algorithm>
#include <vector>
#include <memory>
#include "Object.h"
#include "Enemy.h"
#include "GUI.h"
#include "Player.h"


Enemy::Enemy(std::string animationFile, Vector2D columnRow, const std::unique_ptr<GUI>& gui)
	: AnimatedObject(animationFile, position, Object::Type::enemy, gui)
{

}

void Enemy::update(Object::Command command,  std::vector<std::unique_ptr<Object>>& objects)
{
	//Gravity and Physics now affect Enemies
	applyGravity();
	doPhysics(objects);

	auto playerIter{ std::find_if(objects.begin(), objects.end(), [](auto& object)
		{
			return object->getName() == Object::Type::player;
		}) };

	if (playerIter != objects.end())
	{
		if (position < (*playerIter)->getPosition())
		{
			state = State::stillRight;
		}
		else
		{
			state = State::stillLeft;
		}
	}
	
	
	updateSprite();
	switch (state) 
	{
	case State::stillLeft:	
		//Created variable of timesJumped so enemies would not jump Everytime player jumps.
			if ((*playerIter)->getPosition().y < position.y && timesJumped == 0)
			{
				position.y -= 35;
				timesJumped++;
			}
			position.x -= walkSpeed - 8;
		break;
	case State::stillRight:
		if ((*playerIter)->getPosition().y < position.y && timesJumped == 0)
		{
			position.y -= 35;
			timesJumped++;
		}
		position.x += walkSpeed - 8;
		break;
	}
}

Object* Enemy::copyMe()
{
	return new Enemy(*this);
}
