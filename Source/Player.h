#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>

#include "AnimatedObject.h"
#include "GunFactory.h"
//Comment for push

class GUI;
class Block;
class Player : public AnimatedObject
{
public:
    Player() = delete;
    Player(std::string animationFile, Vector2D columnRow, const std::unique_ptr<GUI>& gui);
    Player(const Player& src) noexcept;
    //write other constructors


    void update(Object::Command command, std::vector<std::unique_ptr<Object>>& objects) override;
    Object* copyMe() override;
    bool getIsDead();
    int getHealth();
private:
    int health{ 3 };
    //Helper functions
    void moveDown();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveJump();
    void noAction();
    bool isDead{ false };
    std::unique_ptr<GunFactory> myGun;


};
#endif // !PLAYER_H
