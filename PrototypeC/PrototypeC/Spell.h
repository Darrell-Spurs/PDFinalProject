#ifndef SPELL_H
#define SPELL_H

#include<SFML/Graphics.hpp>
#include<iostream>


class Spell
{
private:
	sf::Sprite shape;

	sf::Vector2f direction;
	float movementSpeed;


public:
	Spell();
	Spell(sf::Texture* texture, float posX, float posY, float dirX, float dirY, float movementSpeed);
	virtual ~Spell();

	//Accessor
	const sf::FloatRect getBounds() const;


	void update();
	void render(sf::RenderTarget* target);
};


#endif // !SPELL_H