#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>

#include "AnimatedObject.h"
//Comment for push

class GUI;
class Block;
class Player : public AnimatedObject
{
public:
    Player() = delete;
    Player(std::string animationFile, Vector2D columnRow, const std::unique_ptr<GUI>& gui);


    void update(Object::Command command, std::vector<std::unique_ptr<Object>>& objects) override;
    std::unique_ptr<Object> copyMe() override;
    bool getIsDead();
private:
    //Helper functions
    void moveDown();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveJump();
    void noAction();
    bool isDead{ false };


};
#endif // !PLAYER_H
