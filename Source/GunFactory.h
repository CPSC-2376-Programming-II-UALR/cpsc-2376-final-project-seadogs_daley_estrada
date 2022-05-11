#ifndef GUNFACTORY_H
#define GUNFACTORY_H
#include <vector>
#include <memory>

#include "AnimatedObject.h"

class Object;
class GunFactory{
public:
	enum class GunTypes
	{
		singleShot, 
		tripleShot
	};
	//virtual std::vector<std::unique_ptr<Object>>& Fire() = 0;
	//virtual void update() = 0;

	virtual void fire(std::vector<std::unique_ptr<Object>>& objects, const AnimatedObject* player, const std::unique_ptr<GUI>& gui) = 0;
    static std::unique_ptr<GunFactory> create(GunTypes type);
	virtual std::unique_ptr<GunFactory> copyMe() = 0;
};






#endif // !GUNFACTORY_H
