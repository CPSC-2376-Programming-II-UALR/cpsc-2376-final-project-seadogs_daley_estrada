#include <cstdlib> 
#include <ctime> 
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>



#include "GUI.h"
#include "Timer.h"

#include "engine.h"
#include "Object.h"
#include "Block.h"
#include "Enemy.h"
#include "Player.h"
#include "HealthBar.h"
using namespace std;

Engine::Engine(
	std::unique_ptr<GUI>& gui,
	const std::string& levelFile,
	const std::string& playerAnimationFile,
	const std::string& EnemyAnimationFile,
	const std::string& HealthBarAnimationFile):gui(gui)
{
	
	ifstream fin;
	fin.open(levelFile);
	int numRows;
	int numColumns;
	fin >> numRows >> numColumns;
	std::unique_ptr<Player> player1{ std::make_unique<Player>(playerAnimationFile, Vector2D{ 0,0 }, gui) };
	for (int row{ 0 }; row < numRows; row++)
	{
		for (int column{ 0 }; column < numColumns; column++)
		{
			int tempType;
			fin >> tempType;
			Vector2D tempPosition{ column * gui->columnRowDimensions.x,row * gui->columnRowDimensions.y };
			if (Object::Type blockType = (Object::Type)(tempType % 100); blockType != Object::Type::none)
			{
				objects.push_back(std::make_unique<Block>(tempPosition, blockType, gui));
			}

			switch ((Object::Type)(tempType - (tempType % 100)))
			{
			case Object::Type::enemy:
				objects.push_back(std::make_unique<Enemy>(EnemyAnimationFile, tempPosition, gui));
				tempPosition.y -= gui->getDimensions(objects.back().get()).y - gui->columnRowDimensions.y;
				objects.back()->setPosition(tempPosition);
				break;
			case Object::Type::player:
			{
				tempPosition.y -= gui->getDimensions(player1.get()).y - gui->columnRowDimensions.y;
				player1->setPosition(tempPosition);
				break;

			}
			case Object::Type::hpbar: 
			{
				//objects.push_back(std::make_unique<HealthBar>(HealthBarAnimationFile, Vector2D{0,0}, gui));
				break;
			}
			}

		}
		
	}
	objects.push_back(std::move(player1));
	
	fin.close();
}
bool Engine::getGameOver() const
{
	return gameOver;
}
bool Engine::getGameWon() const
{
	return gameWon;
}

void Engine::changeGameState(Object::Command command)
{
	if (!gameOver)
	{
		for (auto& object : objects)
		{
			object->update(command, objects);
			if (object->getName() == Object::Type::player)
			{

				gameOver = 
					((Player*)object.get())->getIsDead() 
					|| object->getPosition().x + object->getDimensions().x >=GUI::screenDimensions.x;
				gameWon = object->getPosition().y < GUI::screenDimensions.y && !((Player*)object.get())->getIsDead();
			}
		}
	}
	//cout << gameOver << " ";

}

std::vector<std::unique_ptr<Object>>& Engine::getObjects()
{
	return objects;
}

Engine::~Engine()
{
}

Engine::Engine(const Engine& src) noexcept:gui(src.gui), gameOver(src.gameOver), gameWon(src.gameWon)
{
	for (auto& object : src.objects)
	{
		objects.emplace_back(object->copyMe());
	}
}

Engine::Engine(Engine&& src) noexcept:gui(src.gui), gameOver(src.gameOver), gameWon(src.gameWon)
{
	for (auto& object : src.objects)
	{
		objects.push_back(std::move(object));
		object = nullptr;
	}
	src.objects.clear();
}

Engine& Engine::operator=(const Engine& src) noexcept
{
	objects.clear();

	for (auto& object : src.objects)
	{
		objects.emplace_back(object->copyMe());
	}
	gameOver = src.gameOver;
	gameWon = src.gameWon;
	return *this;
	
}

Engine& Engine::operator=(Engine&& src) noexcept
{
	objects.clear();

	for (auto& object : src.objects)
	{
		objects.push_back(std::move(object));
		object = nullptr;
	}
	src.objects.clear();
	gameOver = src.gameOver;
	gameWon = src.gameWon;
	return *this;
}









