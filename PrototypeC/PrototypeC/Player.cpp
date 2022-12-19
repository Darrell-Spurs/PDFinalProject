#include "Player.h"

Player::Player()
{
	this->initVariable();
	this->initTexture();
	this->initSprite();

}

void Player::initVariable()
{
	this->movementSpeed = 5.f;
	this->hpMax = 20;
	this->hp = this->hpMax;
	this->cooldownMax = 20.f;
	this->cooldown = 10.f;
	this->level = 1;
	this->exp = 0;
	this->expMax = 5;
	this->damage = 5;

}

void Player::initTexture()
{
	//Load a texture from a file
	if (!this->texture.loadFromFile("Textures/player.png")) {
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could no load texture file." << "\n";
	}
}

void Player::initSprite()
{
	//set the texture to the sprite
	this->sprite.setTexture(this->texture);
	
	//resize the sprite
	this->sprite.scale(0.1f, 0.1f);

	//hp bar
	this->hpBar.setSize(sf::Vector2f(80.f, 10.f));
	this->hpBar.setFillColor(sf::Color::Red);
	this->hpBar.setPosition(this->getpos() + sf::Vector2f(this->getBounds().width / 2 - 40.f, -10.f));
	this->hpBarBack = this->hpBar;
	this->hpBarBack.setFillColor(sf::Color(25, 25, 25, 150));

	//spell bar
	this->skillBar.setSize(sf::Vector2f(360.f, 60.f));
	this->skillBar.setFillColor(sf::Color(255, 95, 31, 50));
	this->skillBar.setPosition(sf::Vector2f(20.f, 192.f));
	this->skillBarBack = this->skillBarBack;
	this->skillBarBack.setFillColor(sf::Color(204, 85, 0, 120));
}

void Player::levelUp()
{
	while (this->exp > this->expMax) {
		++this->level;
		if (level % 10 == 0) {
			--this->cooldownMax;
		}
		if (level % 3 == 0) {
			++this->damage;
		}
		this->hpMax += sqrt(this->level);
		this->hp += 2*sqrt(this->level);
		if (this->hp > this->hpMax) {
			this->hp = this->hpMax;
		}
		this->exp -= this->expMax;
		this->expMax = this->level * log(this->level) * 5;
	}
}

Player::~Player()
{
}

const sf::Vector2f& Player::getpos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int Player::getLevel() const
{
	return this->level;
}

const int Player::getDamage() const
{
	return this->damage;
}

void Player::setPos(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::setPos(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);

}
const bool Player::canAttack()
{
	if (this->cooldown >= this->cooldownMax) {
		this->cooldown = 0.f;
		return true;
	}

	return false;
}
void Player::updateCooldown()
{
	if (this->cooldown < this->cooldownMax) {
		this->cooldown += 0.5f;
	}


}
void Player::updateHpBar()
{
	this->hpBar.setPosition(this->getpos()+sf::Vector2f(this->getBounds().width/2-40.f,-10.f));
	this->hpBarBack.setPosition(this->getpos() + sf::Vector2f(this->getBounds().width / 2 - 40.f, -10.f));
	float hpPersent = (hp*1.f) / hpMax;
	this->hpBar.setScale(hpPersent, 1.f);

}
//Funtions
void Player::update()
{
	this->updateCooldown();
	this->updateHpBar();
	this->levelUp();

}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	target.draw(this->hpBarBack);
	target.draw(this->hpBar);
	target.draw(this->skillBar);
}

void Player::gainExp(int exp)
{
	this->exp += exp;
}

bool Player::damaged(int damage)
{
	this->hp -= damage;
	if (hp <= 0) {
		return true;
	}
	return false;
}

