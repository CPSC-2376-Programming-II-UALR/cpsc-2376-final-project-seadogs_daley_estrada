#include <fstream>
#include <iostream>
#include <algorithm>
#include "Player.h"
#include "GUI.h"
#include "Block.h"


using namespace std;
Player::Player(std::string animationFile, Vector2D columnRow, const std::unique_ptr<GUI>& gui)
	: AnimatedObject(animationFile, position, Object::Type::player,gui)
{
}


bool lastBlockOnScreen(const std::vector<std::unique_ptr<Object>>& objects)
{
	int maxX{ 0 };
	for (auto& object : objects)
	{
		if (object->getPosition().x + object->getDimensions().x > maxX && object->getName() != Object::Type::player)
		{
			maxX = object->getPosition().x + object->getDimensions().x;
		}
	}
	return maxX <= GUI::screenDimensions.x;
}
void Player::update(Object::Command command,  std::vector<std::unique_ptr<Object>>& objects)
{
	switch (command) {

	case Object::Command::right:moveRight(); break;
	case Object::Command::left:moveLeft(); break;
	case Object::Command::down:moveDown(); break;
	case Object::Command::up:moveUp(); break;
	case Object::Command::jump:moveJump(); break;
	case Object::Command::NA:noAction(); break;
	}
	doPhysics(objects);
	//sprite update and height adjustment
	int tempHeight{ (int)gui->getDimensions(this).y };
	updateSprite();
	position.y -= gui->getDimensions(this).y - tempHeight;

	//border detection.
	//left side of screen.
	if (position.x < 0)position.x = 0;


	//half screen.
	else if (position.x > gui->screenDimensions.x / 2 && !lastBlockOnScreen(objects))
	{
		for (auto& object : objects)
		{
			if (object->getName() != Object::Type::player)
			{
				object->setPosition({ object->getPosition().x - (position.x - gui->screenDimensions.x / 2), object->getPosition().y });
			}
		}
		position.x = gui->screenDimensions.x / 2;
	}
	//at the edge.
	else if (position.x + getDimensions().x >= GUI::screenDimensions.x) position.x = GUI::screenDimensions.x - getDimensions().x;
	
	auto objectIter{ std::find_if(objects.begin(), objects.end(), [this](const std::unique_ptr<Object>& object)
			{
				return object->getName() == Object::Type::enemy && collision(object, true);
			}) };
	if (objectIter != objects.end())
	{
		isDead = true;
	}
	if (position.y > GUI::screenDimensions.y)
	{
		isDead = true;
	}

}

Object* Player::copyMe()
{
	return new Player(*this);
}

bool Player::getIsDead()
{
	return isDead;
}



void Player::moveRight()
{
	switch (state)
	{
	case State::stillLeft:
		state = State::stillRight;
		break;
	case State::stillRight:
		state = State::walkRight;
		break;
	case State::jumpRight:
	case State::walkRight:
		position.x += walkSpeed;
		break;
	
	}
}

void Player::moveLeft()
{
	switch (state)
	{
	case AnimatedObject::State::stillRight:
		state = AnimatedObject::State::stillLeft;
		break;
	case AnimatedObject::State::stillLeft:
		state = AnimatedObject::State::walkLeft;
		break;
	case AnimatedObject::State::jumpLeft:
	case AnimatedObject::State::walkLeft:
		position.x -= walkSpeed;
		break;
	default:
		break;
	}
}

void Player::moveDown()
{
	switch (state)
	{
	case AnimatedObject::State::stillLeft:
		state = AnimatedObject::State::crouchLeft;
		break;
	case AnimatedObject::State::stillRight:
		state = AnimatedObject::State::crouchRight;
		break;
	}
}

void Player::moveJump()
{
	if (velocity.y == 0)
	{
		switch (state)
		{
		case Player::State::stillRight:
			state = State::jumpRight;
 			velocity.y = -jumpStrength;
			break;
		case Player::State::stillLeft:
			state = State::jumpLeft;
			velocity.y = -jumpStrength;
			break;
		case Player::State::jumpRight:
			break;
		case Player::State::jumpLeft:
			break;
		default:
			break;
		}

	}
}

void Player::moveUp()
{
	switch (state)
	{
	case AnimatedObject::State::stillLeft:
		state = AnimatedObject::State::upLeft;
		break;
	case AnimatedObject::State::stillRight:
		state = AnimatedObject::State::upRight;
		break;
	}
}

void Player::noAction()
{
	switch (state)
	{
	case AnimatedObject::State::walkLeft:
	case AnimatedObject::State::crouchLeft:
	case AnimatedObject::State::upLeft:
		state = AnimatedObject::State::stillLeft;
		break;
	case AnimatedObject::State::walkRight:
	case AnimatedObject::State::crouchRight:
	case AnimatedObject::State::upRight:
		state = AnimatedObject::State::stillRight;
		break;
	}
}

