#include "HealthBar.h"
#include <algorithm>
#include <vector>
#include <memory>
#include <fstream>
#include <iostream>
#include "Object.h"
#include "GUI.h"
#include "Player.h"

//Comment for push

HealthBar::HealthBar(std::string animationFile, Vector2D columnRow, const std::unique_ptr<GUI>& gui)
	: AnimatedObject(animationFile, position, Object::Type::hpbar, gui)
{

}




void HealthBar::update(Object::Command command, std::vector<std::unique_ptr<Object>>& objects)
{
	//This just makes the HealthBar locked into the top left corner 
	position = {0,0};

	//Changes HealthBar sprite based on player health
	for (auto& object : objects) 
	{
		if (object->getName() == Object::Type::player) 
		{
			switch (((Player*)object.get())->getHealth()) 
			{
			case 3:
				currentSprite = 0;
				break;
			case 2:
				currentSprite = 1;
				break;
			case 1:
				currentSprite = 2;
				break;
			case 0:
				currentSprite = 3;
				break;
			}
		}
	
	}
}

Object* HealthBar::copyMe()
{
	return new HealthBar(*this);
}


