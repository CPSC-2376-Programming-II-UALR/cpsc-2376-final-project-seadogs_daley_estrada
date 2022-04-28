#include "Block.h"

Block::Block(Vector2D columnRow, Object::Type name, const std::unique_ptr<GUI>& gui): Object(columnRow, name, gui)
{

}

Object* Block::copyMe()
{
	return new Block(*this);
}
