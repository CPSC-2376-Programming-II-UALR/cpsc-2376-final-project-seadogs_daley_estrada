#ifndef SINGLESHOT_H
#define SINGLESHOT_H

#include <vector>
#include <memory>
#include "Object.h"
#include "GunFactory.h"
#include "SingleShot.h"
#include "AnimatedObject.h"
#include "Bullet.h"

class SingleShot : public GunFactory
{
public:
	void fire(std::vector<std::unique_ptr<Object>>& objects, const AnimatedObject* player, const std::unique_ptr<GUI>& gui) override;
	std::unique_ptr<GunFactory> copyMe() override;

protected:
	int speed{ 16 };
};


#endif // !SINGLESHOT_H
