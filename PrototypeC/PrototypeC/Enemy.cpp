#include "Enemy.h"
#include<iostream>

const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int Enemy::getLevel() const
{
	return this->level;
}

const sf::Vector2f Enemy::getPos() const
{
	return this->shape.getPosition();
}

int Enemy::getExp()
{
	return this->exp;
}

int Enemy::getDamage()
{
	return this->damage;
}

void Enemy::initShape()
{
	this->shape.setRadius((sqrt(this->level)*20));
	this->shape.setPointCount(this->level + 2);
	this->shape.setFillColor(sf::Color((38 * (this->level - 1) > 255 ? 255 : 38 * (this->level - 1)), 255, 0, 255));
}

void Enemy::initVariable(int level)
{
	this->level = level;
	this->hpmax = 8*level*sqrt(level);
	this->hp = hpmax;
	this->damage = level+1;
	this->exp = 10*level*sqrt(level);
	this->movementSpeed = 4/sqrt(level);
}

Enemy::Enemy(float posX, float posY, int level)
{
	this->initVariable(level);
	this->initShape();
	this->shape.setPosition(posX, posY);
}
Enemy::Enemy() {
	this->initVariable(1);
	this->initShape();
	this->shape.setPosition(-10, -10);
}

Enemy::~Enemy()
{
}

void Enemy::update(sf::Vector2f dir)
{
	dir -= sf::Vector2f(this->getBounds().left + this->getBounds().width / 2, this->getBounds().top + this->getBounds().height / 2);
	dir /= sqrt(dir.x * dir.x + dir.y * dir.y);
	dir *= this->movementSpeed;
	this->shape.move(dir.x, dir.y);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

void Enemy::respawn()
{
	--this->level;
	this->initVariable(this->level);
	this->initShape();
	this->shape.setPosition(this->getPos().x, this->getPos().y);
}

bool Enemy::damaged(int damage)
{
	this->hp -= damage;
	if (this->hp <= 0) {
		return true;
	}
	return false;
}
