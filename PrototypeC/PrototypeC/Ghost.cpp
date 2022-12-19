#include "Ghost.h"

void Ghost::initShape()
{
	this->shape.setRadius((sqrt(this->level) * 20));
	this->shape.setPointCount(this->level + 2);
	this->shape.setFillColor(sf::Color(15 * this->level, 225, 225, 125));
}

void Ghost::initVariable(int level)
{
	this->level = level;
	this->teleportTime = 40;
	this->teleportCooldown = this->teleportTime;
	this->hpmax = 10 * level * sqrt(level);
	this->hp = hpmax;
	this->damage = level;
	this->exp = 100 * level * sqrt(level);
	this->movementSpeed = 3 / sqrt(level);
}

Ghost::Ghost(float posX, float posY, int level)
{
	this->initVariable(level);
	this->initShape();
	this->shape.setPosition(posX, posY);
}

Ghost::~Ghost()
{

}

void Ghost::update(sf::Vector2f dir)
{
	dir -= sf::Vector2f(this->getBounds().left + this->getBounds().width / 2, this->getBounds().top + this->getBounds().height / 2);
	if (dir.x > 0 && dir.y > 0) {
		this->teleport(dir);
	}
	dir /= sqrt(dir.x * dir.x + dir.y * dir.y);
	dir *= this->movementSpeed;
	this->shape.move(dir.x, dir.y);
	this->teleportCooldown += 0.1f;
}

void Ghost::teleport(sf::Vector2f dir)
{
	if ((dir.x * dir.x + dir.y * dir.y) < 70000+(60000 * this->movementSpeed * this->movementSpeed) && this->teleportCooldown>=this->teleportTime) {
		this->shape.move(dir.x, dir.y);
		int degree = rand() % 360;
		float length = sqrt(dir.x * dir.x + dir.y * dir.y);
		this->shape.move(length * (cos(degree)), length * (sin(degree)));
		this->teleportCooldown = 0;
	}
}
