#ifndef ANIMATEDOBJECT_H
#define ANIMATEDOBJECT_H
#include <map>
#include <vector>
#include <string>
#include "Object.h"
//Comment for push

class AnimatedObject : public Object
{
public:
	AnimatedObject() = delete;
	AnimatedObject(std::string animationFile, Vector2D columnRow, Type name, const std::unique_ptr<GUI>& gui);
	
	int getCurrentSprite() const;
	
	enum class State { stillLeft, stillRight, walkLeft, walkRight, crouchLeft, crouchRight, upLeft, upRight, jumpLeft, jumpRight };
	State getCurrentState() const;


protected:
	void doPhysics(const std::vector<std::unique_ptr<Object>>& objects);
	void applyGravity();
	bool collision(const std::unique_ptr<Object>& object, bool full = false);
	void updateSprite();

	const std::string animationFile;

	const int walkSpeed{ 12 };
	const int jumpStrength{ 35 };
	Vector2D velocity{ 0,0 };
	
	static const float deltaT;
	static const Vector2D gravity;

	int currentSprite{ 0 };
	int currentAnimation{ 0 };
	State state{ State::stillRight };
	std::map<State, std::vector<int>> sprites;


};
#endif // !ANIMATION_H
