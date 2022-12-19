#include "Game.h"

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(2400, 1800), "Element Lord - Survival", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	this->textures["SPELL"] = new sf::Texture();
	this->textures["SPELL"]->loadFromFile("Textures/spell.png");
	if (!this->bleedingEffect.loadFromFile("Textures/bleed.png")) {
		std::cout << "ERROR::GAME::Bleeding effect not loaded";
	}
	
}

void Game::initGUI()
{
	//Load effect
	this->bleed.setTexture(this->bleedingEffect);
	this->bleed.setColor(sf::Color(225, 0, 0, 125));
	//Load font
	if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf")) {
		std::cout << "ERROR::GAME::Failed to load font" << "\n";
	}
	//init point text
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(80);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("Test");

	this->skillText.setFont(this->font);
	this->skillText.setCharacterSize(80);
	this->skillText.setFillColor(sf::Color(242, 140, 40, 255));
	this->skillText.setString("Test");

	this->gameoverText.setFont(this->font);
	this->gameoverText.setCharacterSize(200);
	this->gameoverText.setFillColor(sf::Color::Red);
	this->gameoverText.setString("GAME OVER!");
	this->gameoverText.setPosition(this->window->getSize().x/2-this->gameoverText.getGlobalBounds().width/2, this->window->getSize().y/2 - 3*this->gameoverText.getGlobalBounds().height);
}

void Game::initWorld()
{
	if (!this->backgroungTex.loadFromFile("Textures/floor.jpg")) {
		std::cout << "ERROR::GAME::Background not loaded";
	}
	this->worldBackground.setTexture(this->backgroungTex);
	this->worldBackground.scale(1.2f, 1.2f);



}

void Game::initSystem()
{
	this->points = 0;
	this->gameover = false;
	this->isHurtingMax = 1.5f;
	this->isHurting = 0.f;


}

void Game::initPlayer()
{

	this->player = new Player();
	this->player->setPos(this->window->getSize().x / 2-this->player->getBounds().width/2, this->window->getSize().y / 2 - this->player->getBounds().height / 2);

}

void Game::initEnemies()
{
	this->spawnTimerMax = 60.f;
	this->spawnTimer = this->spawnTimerMax;
	this->WandererSpawnTimerMax = 10;
	this->WandererSpawnTimer = 0;
	this->GhostSpawnTimerMax = 20;
	this->GhostSpawnTimer = 0;
	this->difficulty_parameter = 10.f;
	this->difficulty = this->difficulty_parameter;
}

Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initGUI();
	this->initPlayer();
	this->initWorld();
	this->initSystem();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
	delete this->player;
	for (auto& i : this->textures) {
		delete i.second;
	}
	//spells
	for (auto* i : this->spells) {
		delete i;
	}
	for (auto* i : this->enemies) {
		delete i;
	}
}



//Funtions
void Game::run()
{
	while (this->window->isOpen()) {
		this->updatePollEvents();
		if (!this->gameover) {
			this->update();
		}
		this->render();
	}



}

void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e)) {
		if (e.Event::type == sf::Event::Closed) {
			this->window->close();
		}
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape) {
			this->window->close();
		}
	}
}

void Game::updateInput()
{
	//Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		this->player->move(-1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		this->player->move(1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		this->player->move(0.f, -1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		this->player->move(0.f, 1.f);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack()) {
		sf::Vector2f dir = sf::Vector2f(sf::Mouse::getPosition(*(this->window)));
		dir = dir - sf::Vector2f(this->player->getBounds().left + this->player->getBounds().width / 2, this->player->getBounds().top + this->player->getBounds().height/2);
		dir /= sqrt(dir.x * dir.x + dir.y * dir.y);
		this->spells.push_back(new Spell(this->textures["SPELL"], this->player->getBounds().left +this->player->getBounds().width/2, this->player->getBounds().top +this->player->getBounds().height/2, dir.x, dir.y, 7.f));
	}
}

void Game::updateSpells()
{
	bool spell_removed = false;
	unsigned counter = 0;
	//check if spells are out of bounds
	for (auto* spell : this->spells)
	{
		spell->update();

		//Bullet culling (top of screen)
		if (spell->getBounds().top + spell->getBounds().height < 0.f)
		{
			//Delete bullet
			delete this->spells.at(counter);
			this->spells.erase(this->spells.begin() + counter);
			spell_removed = true;
			--counter;
		}
		else if (spell->getBounds().left + spell->getBounds().width < 0.f) {
			//Delete bullet
			delete this->spells.at(counter);
			this->spells.erase(this->spells.begin() + counter);
			spell_removed = true;
			--counter;
		}
		else if (spell->getBounds().left > this->window->getSize().x) {
			delete this->spells.at(counter);
			this->spells.erase(this->spells.begin() + counter);
			spell_removed = true;
			--counter;
		}
		else if (spell->getBounds().top>this->window->getSize().y) {
			delete this->spells.at(counter);
			this->spells.erase(this->spells.begin() + counter);
			spell_removed = true;
			--counter;
		}
		//damage enemy
		for (size_t i = 0; i < this->enemies.size() && !spell_removed; i++) {
			if (spell->getBounds().intersects(this->enemies[i]->getBounds())) {
				if (this->enemies[i]->damaged(this->player->getDamage())) {
					this->player->gainExp(this->enemies[i]->getExp());
					this->points += this->enemies[i]->getExp();
					if (this->enemies[i]->getLevel() > 1) {
						this->enemies[i]->respawn();
					}
					else {
						delete this->enemies.at(i);
						this->enemies.erase(this->enemies.begin() + i);
						--i;
					}
				}
				this->spells.erase(this->spells.begin() + counter);
				--counter;
				spell_removed = true;
			}

		}
		++counter;
	}

}

void Game::updateEnemies()
{
	if (this->difficulty_parameter < 0) {
		++this->difficulty;
		this->difficulty_parameter = 100/log(difficulty);
		this->spawnTimerMax = 870 / sqrt(this->difficulty+200);
		this->WandererSpawnTimerMax = 10 - this->difficulty / 25;
		this->GhostSpawnTimerMax = 20 - this->difficulty / 20;
	}
	this->difficulty_parameter -= 0.1f;

	this->spawnTimer += 0.02*(this->difficulty);
	if (this->spawnTimer >= this->spawnTimerMax) {
		++this->WandererSpawnTimer;
		++this->GhostSpawnTimer;
		int windowX = this->window->getSize().x;
		int windowY = this->window->getSize().y;
		//adjust spawn position
		sf::Vector2f spawnPos = sf::Vector2f(rand() % windowX, rand() % windowY);
		if (spawnPos.x/windowX >= spawnPos.y/windowY) {
			if (spawnPos.x / windowX >= -(spawnPos.y / windowY) +1) {
				spawnPos.x += windowX / 2;
			}
			else {
				spawnPos.y -= windowY / 2;
			}
		}
		else {
			if (spawnPos.x / windowX >= -(spawnPos.y / windowY) + 1) {
				spawnPos.y += windowY / 2;
			}
			else {
				spawnPos.x -= windowX / 2;
			}
		}
		
		this->enemies.push_back(new Enemy(spawnPos.x, spawnPos.y, rand()%(this->difficulty/25 +1)+1));
		if (WandererSpawnTimer >= WandererSpawnTimerMax) {
			this->enemies.push_back(new Wanderer(spawnPos.x, spawnPos.y, rand() % (this->difficulty / 30 + 1) + 1));
			this->WandererSpawnTimer = 0;
		}
		
		if (GhostSpawnTimer >= GhostSpawnTimerMax) {
			this->enemies.push_back(new Ghost(spawnPos.x, spawnPos.y, rand() % (this->difficulty / 35 + 1) + 1));
			this->GhostSpawnTimer = 0;
		}
		

		this->spawnTimer = 0.f;
	}
	//get player's pos
	sf::Vector2f dir = sf::Vector2f(this->player->getBounds().left + this->player->getBounds().width / 2, this->player->getBounds().top + this->player->getBounds().height / 2);
	for (int i = 0; i < this->enemies.size();i++) {
		bool enemy_removed = false;
		this->enemies[i]->update(dir);
		//touch player
		if (!enemy_removed) {
			if (this->enemies[i]->getBounds().intersects(this->player->getBounds())) {
				if (this->player->damaged(this->enemies[i]->getDamage())) {
					this->gameover = true;
				}
				this->isHurting = this->isHurtingMax;
				delete this->enemies.at(i);
				this->enemies.erase(this->enemies.begin() + i);
				--i;
				enemy_removed = true;
			}
		}


		//Remove enemy if they are too far away from the player
		if (!enemy_removed) {
			if (abs(this->enemies[i]->getBounds().top - this->player->getBounds().top) > 2 * this->window->getSize().y || abs(this->enemies[i]->getBounds().left - this->player->getBounds().left) > 2 * this->window->getSize().x) {
				delete this->enemies.at(i);
				this->enemies.erase(this->enemies.begin() + i);
				--i;
				enemy_removed = true;
			}
		}
		

	}
}

void Game::updateGUI()
{
	std::stringstream ss, ss2;
	ss << "Points:" << this->points;
	this->pointText.setString(ss.str());

	ss2 << "Power UP:";
	this->skillText.setString(ss2.str());
}

void Game::updateWorld()
{

}

void Game::updateCollision()
{
	//left
	if (this->player->getBounds().left < 0.f) {
		this->player->setPos(0.f, this->player->getBounds().top);
	}
	//top
	if (this->player->getBounds().top < 0.f) {
		this->player->setPos(this->player->getBounds().left, 0.f);
	}
	//right
	if (this->player->getBounds().left + this->player->getBounds().width > this->window->getSize().x) {
		this->player->setPos(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}
	//down
	if (this->player->getBounds().top + this->player->getBounds().height > this->window->getSize().y) {
		this->player->setPos(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}
}

void Game::update()
{
	this->player->update();
	this->updateInput();
	this->updateCollision();
	this->updateSpells();
	this->updateEnemies();
	this->updateGUI();
}

void Game::render()
{
	this->window->clear();
	//Draw all the stuff
	this->renderWorld();

	this->player->render(*this->window);


	for (auto* spell : this->spells) {
		spell->render(this->window);
	}
	for (auto* enemy : this->enemies) {
		enemy->render(this->window);
	}

	this->renderGUI();
	this->window->display();
}

void Game::renderGUI()
{
	if (this->gameover) {
		this->window->draw(this->gameoverText);
		this->pointText.setCharacterSize(80);
		this->pointText.setPosition(this->window->getSize().x / 2 - this->pointText.getGlobalBounds().width / 2, this->window->getSize().y / 2 );
	}
	if (this->isHurting > 0) {
		this->window->draw(this->bleed);
		this->isHurting -= 0.1f;
	}
	this->pointText.setPosition(20.f, 12.f);
	this->window->draw(this->pointText);

	this->skillText.setPosition(20.f, 92.f);
	this->window->draw(this->skillText);
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}
