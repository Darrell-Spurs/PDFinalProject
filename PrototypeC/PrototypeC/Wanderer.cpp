#include "Wanderer.h"

void Wanderer::initShape()
{
	this->shape.setOrigin(0,0);
	this->shape.setRadius((sqrt(this->level) * 20));
	this->shape.setPointCount(this->level + 2);
	this->shape.setFillColor(sf::Color(225, 225, 15 * this->level, 255));
}

void Wanderer::initVariable(int level)
{
	this->type = 225;
	this->level = level;
	this->hpmax = 3 * level * sqrt(level);
	this->hp = hpmax;
	this->damage = level/2+1;
	this->exp = 50 * level * sqrt(level);
	this->movementSpeed = 5 / sqrt(level);
}

Wanderer::Wanderer(float posX, float posY, int level)
{
	this->des = sf::Vector2f(0, 0);
	this->initVariable(level);
	this->initShape();
	this->shape.setPosition(posX, posY);

}

Wanderer::~Wanderer()
{

}

void Wanderer::update(sf::Vector2f dir)
{
	if (this->des != sf::Vector2f(0, 0)) {
		this->shape.move(this->des.x, this->des.y);
		this->shape.rotate(3.f);
	}
	else {
		dir -= sf::Vector2f(this->getBounds().left + this->getBounds().width / 2, this->getBounds().top + this->getBounds().height / 2);
		dir /= sqrt(dir.x * dir.x + dir.y * dir.y);
		dir *= this->movementSpeed;
		this->des = dir;
		this->shape.move(this->des.x, this->des.y);
	}
}

void Wanderer::respawn()
{
	--this->level;
	this->initVariable(this->level);
	this->initShape();
}
