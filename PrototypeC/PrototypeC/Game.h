#pragma once
#include<map>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<string>
#include<sstream>
#include"Player.h"
#include"Spell.h"
#include<iostream>
#include"Enemy.h"
#include"Wanderer.h"
#include"Ghost.h"


class Game
{
private:
	//Window
	sf::RenderWindow* window;

	//resoures
	std::map<std::string, sf::Texture*> textures;
	std::vector<Spell*> spells;

	//GUI
	sf::Font font;
	sf::Text pointText;
	sf::Text skillText;

	sf::Text gameoverText;

	sf::Texture bleedingEffect;
	sf::Sprite bleed;

	//world
	sf::Texture backgroungTex;
	sf::Sprite worldBackground;

	//Player
	Player* player;

	//system
	unsigned points;
	bool gameover;
	float isHurting;
	float isHurtingMax;

	//Enemy
	float spawnTimer;
	float spawnTimerMax;
	int WandererSpawnTimer;
	int WandererSpawnTimerMax;
	int GhostSpawnTimer;
	int GhostSpawnTimerMax;
	std::vector<Enemy*> enemies;
	float difficulty_parameter;
	int difficulty;
	
	//private funtions
	void initWindow();
	void initTextures();
	void initGUI();
	void initWorld();
	void initSystem();
	void initPlayer();
	void initEnemies();

public:
	Game();
	virtual ~Game();
	//Funtions


	void run();


	void updatePollEvents();
	void updateInput();
	void updateSpells();
	void updateEnemies();
	void updateGUI();
	void updateWorld();
	void updateCollision();

	void update();
	void render();
	void renderGUI();
	void renderWorld();

};

