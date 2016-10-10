#include "Game.h"
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <iostream>
#include <ctime>
#include "Triangle.h"
#include "StaticFunctions.h"


Game::Game()
	:
	manager(&window)
{
	Initialize();
}


Game::~Game()
{
}
//Initialize window and settings
void Game::Initialize()
{
	settings.antialiasingLevel = 8;
	window.create(sf::VideoMode(StaticFunctions::WINDOW_WIDTH, StaticFunctions::WINDOW_HEIGHT), "Dodging game thingy", sf::Style::Default, settings);
}
//Main game loop
void Game::Run()
{
	manager.SetScene(HUD::Option::MAIN);
	while (window.isOpen())
	{
		Poll();
		Input();
		Update();
		Draw();
	}
}
//Event polling
void Game::Poll()
{
	sf::Event Event;
	while (window.pollEvent(Event))
	{
		switch (Event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseButtonPressed:
			manager.Poll(Event);
		case sf::Event::KeyPressed:
			switch (Event.key.code)
			{
			case sf::Keyboard::Escape:
				if (!manager.paused && manager.scene[1])
				{
					manager.paused = true;
					manager.scene[2] = true;
				}
				else if(manager.paused && manager.scene[1])
				{
					manager.paused = false;
					manager.scene[2] = false;
				}
				break;
			}
			break;
		case sf::Event::MouseMoved:

			break;
		}
	}
}
//Input handling
void Game::Input()
{
	manager.Input();
}
//Update
void Game::Update()
{
	manager.Update();
}
//Draw
void Game::Draw()
{
	window.clear();
	////////////////DRAW START///////////////////
	manager.Draw();
	/////////////////DRAW END////////////////////
	window.display();
}
