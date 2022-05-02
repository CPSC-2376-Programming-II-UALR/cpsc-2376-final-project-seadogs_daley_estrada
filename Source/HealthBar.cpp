#include "HealthBar.h"
#include <algorithm>
#include <vector>
#include <memory>
#include <fstream>
#include <iostream>
#include "GUI.h"
#include "Player.h"


HealthBar::HealthBar(std::string animationFile, Vector2D columnRow, const std::unique_ptr<GUI>& gui)
	: AnimatedObject(animationFile, position, Object::Type::hpbar, gui)
{

}




void HealthBar::update(Object::Command command, std::vector<std::unique_ptr<Object>>& objects)
{
	position = {0,0};
}

Object* HealthBar::copyMe()
{
	return new HealthBar(*this);
}


