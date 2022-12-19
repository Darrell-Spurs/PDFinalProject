#pragma once
#include "Enemy.h"
class Ghost :
    public Enemy
{
private:
    float teleportCooldown;
    int teleportTime;
    void initShape() override;
    void initVariable(int level) override;
public:
    Ghost(float posX, float posY, int level);
    ~Ghost();
    void update(sf::Vector2f dir) override;
    void teleport(sf::Vector2f dir);
};

