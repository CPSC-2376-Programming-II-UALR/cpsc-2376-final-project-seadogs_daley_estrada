#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <vector>
#include <tuple>
#include <memory>
//Comment for push

class GUI;
class Object;


//Game Utilities
class Engine
{
public:
	Engine(
		std::unique_ptr<GUI>& gui,
		const std::string& levelFile,
		const std::string& playerAnimationFile,
		const std::string& EnemyAnimationFile,
		const std::string& HealthBarAnimationFile);

	bool getGameOver() const;
	bool getGameWon() const;
	void changeGameState(Object::Command command);
	std::vector<std::unique_ptr<Object>>& getObjects();

	~Engine();
	Engine(const Engine& src) noexcept;
	Engine(Engine&& src) noexcept;

	Engine& operator=(const Engine& src) noexcept;
	Engine& operator=(Engine&& src) noexcept;
private:
	bool gameOver{ false };
	bool gameWon{ false };
	std::vector<std::unique_ptr<Object>> objects;
	const std::unique_ptr<GUI>& gui;
};

#endif