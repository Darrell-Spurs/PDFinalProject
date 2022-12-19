#ifndef ENEMY_H
#define ENEMY_H

#include<SFML/Graphics.hpp>

class Enemy
{
protected:
	sf::CircleShape shape;
	int type=0;

	int level;
	int hp;
	int hpmax;
	int damage;
	int exp;
	float movementSpeed;
	

	//private Funtion
	virtual void initShape();
	virtual void initVariable(int level);

public:
	Enemy(float posX, float posY, int level);
	Enemy();
	virtual ~Enemy();

	//Accessors
	const sf::FloatRect getBounds() const;
	const int getLevel() const;
	const sf::Vector2f getPos() const;
	int getExp();
	int getDamage();
	//functions
	virtual void update(sf::Vector2f dir);
	void render(sf::RenderTarget* target);
	virtual void respawn();
	//take damage, if dies, return true
	bool damaged(int damage);

};

#endif // !ENEMY_H