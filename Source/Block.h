#ifndef BLOCK_H
#define BLOCK_H
#include "Object.h"
//Comment for push

class Player;
class Block:public Object
{
public:
	Block() = delete;
	Block(Vector2D columnRow, Object::Type name, const std::unique_ptr<GUI>& gui);
	void update(Object::Command command,  std::vector<std::unique_ptr<Object>>& objects) override {}
	std::unique_ptr<Object> copyMe() override;
private:
	
};
#endif // !BLOCK_H
