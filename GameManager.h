#pragma once
#include "HUD.h"
#include "Obstacle.h"
#include "Player.h"
#include "AudioManager.h"
#include <vector>

class GameManager
{
public:
	GameManager(sf::RenderWindow *p_window);
	~GameManager();

	void Update();
	void Draw();
	void Input();
	void Poll(sf::Event &Event);

	int score;
	int wave;
	bool paused;

	void StartGame();
	void StartRound(int wave);
	void SetScene(HUD::Option option);
	bool roundactive;
	bool scene[3];

	sf::Clock clock;
	sf::Clock gametime;
	sf::Clock roundtimer;
private:
	HUD hud;
	AudioManager audiomanager;

	std::vector<Obstacle> obstacles;
	sf::RenderWindow *window;
	Player player;

	int difficulty;
	bool direction[4];

};

