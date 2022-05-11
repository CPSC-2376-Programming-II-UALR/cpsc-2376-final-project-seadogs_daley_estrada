#include <fstream>
#include <iostream>
#include "AnimatedObject.h"
#include "Block.h"
#include "GUI.h"
//Comment for push

using namespace std;
const Vector2D AnimatedObject::gravity{ 0.0f, 10.0f };
const float AnimatedObject::deltaT{ 0.5f };
AnimatedObject::AnimatedObject(std::string animationFile, Vector2D columnRow, Type name, const std::unique_ptr<GUI>& gui) : Object(position, name, gui), animationFile{animationFile}
{
	fstream fin;
	fin.open(animationFile);
	if (!fin.is_open()) cout << "File does not exist!";


	int numStates;

	fin >> numStates;
	for (int i{ 0 }; i < numStates; i++)
	{
		int numAnimations;
		fin >> numAnimations;
		for (int j{ 0 }; j < numAnimations; j++)
		{
			int spriteSequence;
			fin >> spriteSequence;
			sprites[(State)i].push_back(spriteSequence);
		}
	}
	updateSprite();
}
int AnimatedObject::getCurrentSprite() const
{
	return currentSprite;
}
AnimatedObject::State AnimatedObject::getCurrentState() const
{
	return state;
}
void AnimatedObject::updateSprite()
{
	currentAnimation++;
	currentAnimation %= sprites[state].size();

	currentSprite = sprites[state][currentAnimation];
}
void AnimatedObject::doPhysics(const std::vector<std::unique_ptr<Object>>& objects)
{
	applyGravity();

	for (const auto& object : objects)
	{
		switch (object->getName()) //Only looking for Block Types
		{
		case Object::Type::bridge_center:
		case Object::Type::bridge_end:
		case Object::Type::bridge_start:
		case Object::Type::top_block:
		case Object::Type::water_top:
			if (collision(object))
			{
				position.y = object->getPosition().y - gui->getDimensions(this).y;
				velocity.y = 0;
				if (state == AnimatedObject::State::jumpLeft)
				{
					state = AnimatedObject::State::stillLeft;
				}
				else if (state == AnimatedObject::State::jumpRight)
				{
					state = AnimatedObject::State::stillRight;
				}
			}
		}
	}
}

void AnimatedObject::applyGravity()
{
	position.y += deltaT * velocity.y;
	velocity.y += deltaT * gravity.y;
}

bool AnimatedObject::collision(const std::unique_ptr<Object>& object, bool full)
{
	//If Player collides with an enemy, full needs to be set to true.
	if (full == true)
	{
		bool leftInColumn{ (position.x >= object->getPosition().x
				&& position.x <= object->getPosition().x + object->getDimensions().x) };

		bool rightInColumn{ (position.x + getDimensions().x >= object->getPosition().x
			&& position.x + getDimensions().x <= object->getPosition().x + object->getDimensions().x) };

		bool topInRow{ (position.y >= object->getPosition().y
			&& position.y < object->getPosition().y + object->getDimensions().y) };

		bool bottomInRow{ (position.y + getDimensions().y > object->getPosition().y
			&& position.y + getDimensions().y <= object->getPosition().y + object->getDimensions().y) };

		bool objectTopInThis{ (object->getPosition().y > position.y
			&& object->getPosition().y < position.y + getDimensions().y) };

		bool sameColumn{ leftInColumn || rightInColumn };

		bool sameRow{ topInRow || bottomInRow || objectTopInThis };

		return sameRow && sameColumn;
	}

	else
	{
		bool leftInColumn{ (position.x >= object->getPosition().x
					&& position.x <= object->getPosition().x + object->getDimensions().x) };// determines if the Players left side is in between the Objects left and right side

		bool rightInColumn{ (position.x + getDimensions().x >= object->getPosition().x
			&& position.x + getDimensions().x <= object->getPosition().x + object->getDimensions().x) }; //determines if the Players right side is in between the Objects left and right side

		/*bool topInRow{(position.y >= object->getPosition().y
			&& position.y < object->getPosition().y + object->getDimensions().y) };*/ // checks if the Players top is in betweeen the Objects Top and bottom

		bool bottomInRow{ (position.y + getDimensions().y > object->getPosition().y
			&& position.y + getDimensions().y <= object->getPosition().y + gravity.y) }; // checks if the Players bottom is in between the Objects top and bottom.

		bool objectTopInThis{ (object->getPosition().y > position.y
			&& object->getPosition().y < position.y + getDimensions().y) }; // This varibale determines the Objects top in range of our players top and bottom

		bool sameColumn{ leftInColumn || rightInColumn };

		bool sameRow{ bottomInRow || objectTopInThis };

		return sameRow && sameColumn;
	}


}
