#pragma once
#include "Enemy.h"
class Wanderer :
    public Enemy
{
private:
    sf::Vector2f des;
    void initShape() override;
    void initVariable(int level) override;
public:
    Wanderer(float posX, float posY, int level);
    ~Wanderer();
    void update(sf::Vector2f dir) override;
    void respawn() override;
};

