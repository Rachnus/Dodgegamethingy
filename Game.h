#pragma once
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include "Obstacle.h"
#include "Player.h"
#include "HUD.h"
#include <vector>
#include "GameManager.h"
class Game
{
public:
	Game();
	~Game();

	void Run();

	void Initialize();

	void Poll();
	void Input();
	void Update();
	void Draw();
private:
	sf::ContextSettings settings;
	sf::RenderWindow window;

	GameManager manager;

};

