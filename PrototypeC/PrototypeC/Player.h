#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<iostream>

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	float movementSpeed;

	float cooldown;
	float cooldownMax;
	int level;
	int hpMax;
	int hp;
	int exp;
	int damage;
	int expMax;

	//playerGUI
	sf::RectangleShape hpBar;
	sf::RectangleShape hpBarBack;

	sf::RectangleShape skillBar;
	sf::RectangleShape skillBarBack;

	//private funtion
	void initVariable();
	void initTexture();
	void initSprite();
	void levelUp();
public:
	Player();
	virtual ~Player();

	//Accessor
	const sf::Vector2f& getpos() const;
	const sf::FloatRect getBounds() const;
	const int getLevel() const;
	const int getDamage() const;
	//Modifier
	void setPos(const sf::Vector2f pos);
	void setPos(const float x, const float y);
	//Functions
	void move(const float dirX, const float dirY);

	const bool canAttack();
	void updateCooldown();
	void updateHpBar();
	void update();
	void render(sf::RenderTarget& target);
	void gainExp(int exp);
	//if died, return true
	bool damaged(int damage);
};

