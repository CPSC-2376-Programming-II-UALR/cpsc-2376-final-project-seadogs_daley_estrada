#include "SingleShot.h"

std::unique_ptr<GunFactory> SingleShot::copyMe() {
    std::unique_ptr<GunFactory> tmp(new SingleShot(*this));
    return std::move(tmp);
}

void SingleShot::fire(std::vector<std::unique_ptr<Object>>& objects, const AnimatedObject* player, const std::unique_ptr<GUI>& gui)
{
    Vector2D direction{1,0};
    Vector2D bulletPos = player->getPosition();
    Vector2D bulletDimensions {8,8};
    switch (player->getCurrentState()) {

    case AnimatedObject::State::crouchLeft:
    case AnimatedObject::State::jumpLeft:
        direction = { -1,0 }; //left
        bulletPos.y += player->getDimensions().y / 2;
        bulletPos.y -= bulletDimensions.y / 2;
        bulletPos.x -= bulletDimensions.x; //accounting for bullet width to spawn outside of player
        break;
    case AnimatedObject::State::stillLeft:
    case AnimatedObject::State::walkLeft:
        direction = { -1,0 }; //left
        bulletPos.y += player->getDimensions().y / 3;
        bulletPos.x -= bulletDimensions.x; //accounting for bullet width to spawn outside of player
        break;
    case AnimatedObject::State::crouchRight:
    case AnimatedObject::State::jumpRight:
        direction = { 1,0 }; //right
        bulletPos.x += player->getDimensions().x;
        bulletPos.y += player->getDimensions().y / 2;
        bulletPos.y -= bulletDimensions.y / 2;
        break;
    case AnimatedObject::State::stillRight:
    case AnimatedObject::State::walkRight:
        direction = { 1,0 }; //right
        bulletPos.x += player->getDimensions().x;
        bulletPos.y += player->getDimensions().y / 3;
        break;
    case AnimatedObject::State::upLeft:
        direction = { 0,-1 }; //up
        bulletPos.x += player->getDimensions().x * 0.25;
        bulletPos.x -= bulletDimensions.x / 2;
        bulletPos.y -= bulletDimensions.y;//accounting for bullet height to spawn outside of player
        break;
    case AnimatedObject::State::upRight:
        direction = { 0,-1 }; //up
        bulletPos.x += player->getDimensions().x * 0.75;
        bulletPos.x -= bulletDimensions.x / 2;
        bulletPos.y -= bulletDimensions.y;//accounting for bullet height to spawn outside of player
        break;
    }
    std::unique_ptr<Bullet> b = std::make_unique<Bullet>(bulletPos, direction, speed, Object::Type::bullet, gui);
    objects.push_back(std::move(b));
}