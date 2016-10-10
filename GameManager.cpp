#include "GameManager.h"
#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "StaticFunctions.h"
#include <iostream>
#include <memory>
GameManager::GameManager(sf::RenderWindow *p_window)
	:
	score(0),
	wave(1),
	difficulty(1),
	roundactive(false),
	paused(false),
	player(sf::Vector2<float>(StaticFunctions::WINDOW_WIDTH - 100, StaticFunctions::WINDOW_HEIGHT / 2)),
	hud(p_window, scene, &score, &wave, &gametime),
	window(p_window)
{
	for (int i = 0; i < 4; i++)
		direction[i] = false;

	scene[0] = true;
	scene[1] = false;
	scene[2] = false;
}


GameManager::~GameManager()
{

}

//Change between main menu, play or pause
void GameManager::SetScene(HUD::Option option)
{
	if (option == HUD::Option::MAIN)
	{
		hud.InitializeMainMenu();
		audiomanager.StopSound();
		hud.option = HUD::Option::MAIN;
		score = 0;
		wave = 1;
		gametime.restart();
		roundactive = false;
		scene[0] = true;
		scene[1] = false;
		scene[2] = false;
		paused = false;
		obstacles.clear();
	}
	else if (option == HUD::Option::PLAY)
	{
		hud.InitializePauseHUD();
		hud.option = HUD::Option::PLAY;
		scene[0] = false;
		scene[1] = true;
		scene[2] = false;
		StartGame();
	}
	else if (option == HUD::Option::EXIT)
	{
		hud.option = HUD::Option::EXIT;
		window->close();
	}
}
//Start the game from start
void GameManager::StartGame()
{
	audiomanager.PlaySound();
	std::cout << "GAME START" << std::endl;
	Obstacle::totalobjectspassed = 0;
	StartRound(wave);

}
//New round
void GameManager::StartRound(int wave)
{
	Obstacle::objectspassed = 0;
	roundactive = true;
	roundtimer.restart();

	for (int i = 0; i < 4; i++)
		direction[i] = false;

	if (wave >= 30)
		difficulty = 2;
	if (wave >= 50)
		difficulty = 3;
	if (wave >= 100)
		difficulty = 4;


	for (int i = 0; i < difficulty;i++)
	{
		int random = rand() % 4;
		
		while (direction[random])
		{
			random = rand() % 4;
			if (!direction[random])
			{
				direction[random] = true;
				break;
			}
		}
		direction[random] = true;

	}
	
	std::cout << "LEFT: " << direction[0] << " RIGHT: " << direction[1] << " UP: " << direction[2] << " DOWN: " << direction[3] << std::endl;
	hud.RoundStart();
}
//Update everything (HUD, Obstacles, Player)
void GameManager::Update()
{
	sf::Time dt = clock.restart();
	hud.HUDUpdate(dt);

	if (!paused)
	{
		if (scene[0])
		{
			if (hud.option == HUD::Option::PLAY)
			{
				SetScene(HUD::Option::PLAY);
			}
			if (hud.option == HUD::Option::EXIT)
			{
				SetScene(HUD::Option::EXIT);
			}
		}

		if (scene[1])
		{
			player.Update(dt);
			
			if (roundtimer.getElapsedTime().asSeconds() <= 5.0f)
				hud.FlashDirection(direction);
			else
				hud.SetDirectionTextAlpha(0, direction);

			if (roundactive && roundtimer.getElapsedTime().asSeconds() > 5.f)
			{
				if (obstacles.size() < 10 * wave)
				{
					int randnum = rand() % 1000;
					if (randnum == 5)
					{
						Obstacle obstacle(wave, rand() % 7 + 1, direction);
						obstacles.push_back(obstacle);
					}
				}

				for (int i = 0; i < obstacles.size(); i++)
				{
					if (obstacles[i].IsOutOfBounds())
						score++;
					obstacles[i].Update(dt);
					if (obstacles[i].IsCollidingWithPlayer(player.playerpos, player.playersize))
						SetScene(HUD::Option::MAIN);

				}
			}

			if (Obstacle::objectspassed > 10 * wave)
			{
				roundactive = false;
				Obstacle::objectspassed = 0;
				wave++;
				obstacles.clear();
				StartRound(wave);
			}
		}
	}
	else
	{
		if (hud.option == HUD::Option::MAIN)
		{
			SetScene(HUD::Option::MAIN);
		}
		if (hud.option == HUD::Option::EXIT)
		{
			SetScene(HUD::Option::EXIT);
		}
	}
}
//Draw everything (HUD, Obstacles, Player, Background)
void GameManager::Draw()
{
	hud.DrawBackground();
	if (scene[1])
	{
		for (int i = 0; i < obstacles.size(); i++)
		{
			obstacles[i].Draw(*window);
		}
		
		player.Draw(window);
	}
	hud.Draw();
}
//Real time input
void GameManager::Input()
{
	if (scene[1])
	{
		player.Input();
	}
	hud.Input();
}
//Event polling
void GameManager::Poll(sf::Event &Event)
{
	hud.Poll(Event);
}