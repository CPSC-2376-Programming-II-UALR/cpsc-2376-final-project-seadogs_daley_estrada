#include <fstream>
#include <iostream>
#include "Player.h"
#include "GUI.h"
#include "Block.h"

using namespace std;
Player::Player(std::string animationFile, Vector2D position, const std::unique_ptr<GUI>& gui) : AnimatedObject(animationFile, position, Object::Type::player, gui)
{
}



void Player::update(Object::Command command, std::vector<std::unique_ptr<Object>>& objects)
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
	if (position.x < 0)position.x = 0;
	else if (position.x > gui->screenDimensions.x - gui->getDimensions(this).x)
		position.x = gui->screenDimensions.x - gui->getDimensions(this).x;


	int previousObjectX = 0;
	for (auto& object : objects)
	{
		int x = object->getPosition().x + object->getDimensions().x;
		if (x > previousObjectX && object->getName() != Object::Type::player)
		{
			previousObjectX = x;
		}
		if (object->getName() == Object::Type::enemy &&
			collision(object, true))
		{
			isDead = true;
		}
	}

	bool lastBlockOnScreen{ false };
	if (previousObjectX <= GUI::screenDimensions.x)
	{
		lastBlockOnScreen = true;
	}

	if (position.x > GUI::screenDimensions.x / 2 && !lastBlockOnScreen)
	{
		int diff;
		diff = position.x - GUI::screenDimensions.x / 2;
		for (auto& object : objects)
		{
			Vector2D initialPos = object->getPosition();
			Vector2D newPosition = { initialPos.x - diff, object->getPosition().y };
			object->setPosition(newPosition);

		}

	}

	if (position.y > GUI::screenDimensions.y)
	{
		isDead = true;
	}


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
	case State::walkRight:
		position.x += walkSpeed;
		break;
	case State::jumpLeft:
		state = State::jumpRight;
		break;
	case State::jumpRight:
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
	case AnimatedObject::State::walkLeft:
		position.x -= walkSpeed;
		break;
	case State::jumpLeft:
		state = State::jumpRight;
		break;
	case State::jumpRight:
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
		case::Player::State::crouchLeft:                                     //extra credit
			position.y += getDimensions().y + gravity.y + 1;                 //extra credit
			break;                                                           //extra credit
		case::Player::State::crouchRight:                                    //extra credit
			position.y += getDimensions().y + gravity.y + 1;                 //extra credit
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

bool Player::getIsDead()
{
	return isDead;
}
std::unique_ptr<Object> Player::copyMe()
{
	return std::make_unique<Player>(*this);     //return new Player(*this);
}
