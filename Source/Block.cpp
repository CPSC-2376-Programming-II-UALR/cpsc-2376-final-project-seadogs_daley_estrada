#include "Block.h"
//Comment for push

Block::Block(Vector2D columnRow, Object::Type name, const std::unique_ptr<GUI>& gui): Object(columnRow, name, gui)
{

}

std::unique_ptr<Object> Block::copyMe()
{
	return std::make_unique<Block>(*this);
}
