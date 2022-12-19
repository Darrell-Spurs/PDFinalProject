#include "Spell.h"

Spell::Spell()
{

}

Spell::Spell(sf::Texture * texture,float posX, float posY, float dirX, float dirY, float movementSpeed)
{
	this->shape.setTexture(*texture);
	this->shape.setScale(0.5f, 0.5f);
	this->shape.setOrigin(this->getBounds().width / 2, this->getBounds().height / 2);
	this->shape.setPosition(posX, posY);
	float degree = atan(dirX/dirY) * 180 / 3.14;
	if (dirX > 0 && dirY < 0) {
		degree = -degree;
	}
	else if (dirX < 0 && dirY < 0) {
		degree = 360 - degree;
	}
	else if(dirX > 0 && dirY > 0){
		degree = 180 - degree;
	}
	else {
		degree = 180 - degree;
	}
	this->shape.setRotation(degree);
	this->direction.x = dirX;
	this->direction.y = dirY;
	this->movementSpeed = movementSpeed;

}

Spell::~Spell()
{

}

const sf::FloatRect Spell::getBounds() const
{
	return this->shape.getGlobalBounds();
}

void Spell::update()
{
	//moverment
	this->shape.move(this->movementSpeed * this->direction);

}

void Spell::render(sf::RenderTarget* target)
{
	target->draw(this->shape);

}
