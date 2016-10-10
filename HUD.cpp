#include "HUD.h"
#include "StaticFunctions.h"
#include <string>
#include <iostream>

HUD::HUD(sf::RenderWindow *p_window, bool *p_scene, int *p_score, int *p_wave, sf::Clock *p_clock)
	:
	charactersize(20),
	popupAlpha(255),
	roundstart(false),
	scene(p_scene),
	score(p_score),
    wave(p_wave),
	clock(p_clock),
	window(p_window),
	option(HUD::Option::MAIN)

{

	InitializeHUD();
}


HUD::~HUD()
{
}
//Initialize in game HUD
void HUD::InitializeHUD()
{
	if (!backgroundTexture.loadFromFile("images/background.jpg"))
		std::cout << "Error: Could not load background.jpg" << std::endl;
	backgroundTexture.setRepeated(true);
	for (int i = 0; i < 2; i++)
		backgroundSprite[i].setTexture(backgroundTexture, true);
		
	backgroundSprite[0].setTextureRect(sf::IntRect(0, 0, StaticFunctions::WINDOW_WIDTH, StaticFunctions::WINDOW_HEIGHT));
	backgroundSprite[1].setTextureRect(sf::IntRect(1600, 0, StaticFunctions::WINDOW_WIDTH, StaticFunctions::WINDOW_HEIGHT));

	backgroundSprite[0].setPosition(0, 0);
	backgroundSprite[1].setPosition(StaticFunctions::WINDOW_WIDTH, 0);

	
	if (!fontArial.loadFromFile("fonts/arial.ttf"))
		std::cout << "Error: Could not load font arial.ttf!" << std::endl;


	hudbasesize = sf::Vector2<float>(StaticFunctions::WINDOW_WIDTH, StaticFunctions::HUD_OFFSET);
	hudbaseColor = sf::Color::Blue;
	hudbasepos = sf::Vector2<float>(0, StaticFunctions::WINDOW_HEIGHT - StaticFunctions::HUD_OFFSET);
	hudbase.setSize(hudbasesize);
	hudbase.setFillColor(hudbaseColor);
	hudbase.setPosition(hudbasepos);
	labelColor = sf::Color::Green;
	popupColor = sf::Color(0, 255, 0, popupAlpha);
	buttonsize = sf::Vector2<float>(200, 50);
	buttoncolor = sf::Color::Green;

	textScore.setFont(fontArial);
	textWave.setFont(fontArial);
	textWavePopup.setFont(fontArial);
	textTime.setFont(fontArial);
	for (int i = 0; i < 4; i++)
		textDirection[i].setFont(fontArial);

	textScore.setCharacterSize(charactersize);
	textWave.setCharacterSize(charactersize);
	textWavePopup.setCharacterSize(50);
	textTime.setCharacterSize(charactersize);

	for (int i = 0; i < 4; i++)
		textDirection[i].setCharacterSize(100);

	textScore.setPosition(100, StaticFunctions::WINDOW_HEIGHT - (StaticFunctions::HUD_OFFSET));
	textWave.setPosition(100, StaticFunctions::WINDOW_HEIGHT - (StaticFunctions::HUD_OFFSET / 3));
	textWavePopup.setPosition(StaticFunctions::WINDOW_WIDTH / 2.2, StaticFunctions::WINDOW_HEIGHT / 3);
	textTime.setPosition(StaticFunctions::WINDOW_WIDTH - 200, StaticFunctions::WINDOW_HEIGHT - (StaticFunctions::HUD_OFFSET / 3));
	textDirection[0].setPosition(20, StaticFunctions::WINDOW_HEIGHT / 2 - 100);
	textDirection[1].setPosition(StaticFunctions::WINDOW_WIDTH - 50, StaticFunctions::WINDOW_HEIGHT / 2 - 100);
	textDirection[2].setPosition(StaticFunctions::WINDOW_WIDTH / 2, 0);
	textDirection[3].setPosition(StaticFunctions::WINDOW_WIDTH / 2, StaticFunctions::WINDOW_HEIGHT - StaticFunctions::HUD_OFFSET - 120);

	textWavePopup.setFillColor(popupColor);
	textTime.setFillColor(popupColor);

	for (int i = 0; i < 4; i++)
		textDirection[i].setFillColor(sf::Color(255, 0, 0, 0));

	stringScore = std::to_string(*score);
	stringWave = std::to_string(*wave);

	textScore.setString("Score: " + stringScore);
	textWave.setString("Wave: " + stringWave);
	textWavePopup.setString("Wave: " + stringWave);
	textTime.setString("Time: " + StaticFunctions::RoundOneDecimal(clock->getElapsedTime().asSeconds()));
	for (int i = 0; i < 4; i++)
		textDirection[i].setString("!");

}
//Initialize main menu interface
void HUD::InitializeMainMenu()
{
	for (int i = 0; i < 2; i++)
	{
		mainbuttons[i] = false;
		buttonsmain[i].setSize(buttonsize);
		buttonsmain[i].setFillColor(buttoncolor);
		labelButtonsmain[i].setCharacterSize(40);
		labelButtonsmain[i].setFont(fontArial);
		labelButtonsmain[i].setStyle(sf::Text::Bold);
	}

	buttonsmain[0].setPosition(sf::Vector2<float>(StaticFunctions::WINDOW_WIDTH / 2 - (buttonsize.x / 2), StaticFunctions::WINDOW_HEIGHT / 2));
	buttonsmain[1].setPosition(sf::Vector2<float>(StaticFunctions::WINDOW_WIDTH / 2 - (buttonsize.x / 2), StaticFunctions::WINDOW_HEIGHT / 2 + buttonsize.y + 10));
	labelButtonsmain[0].setPosition(sf::Vector2<float>(StaticFunctions::WINDOW_WIDTH / 2 - (buttonsize.x / 2) + 60, StaticFunctions::WINDOW_HEIGHT / 2));
	labelButtonsmain[1].setPosition(sf::Vector2<float>(StaticFunctions::WINDOW_WIDTH / 2 - (buttonsize.x / 2) + 60, StaticFunctions::WINDOW_HEIGHT / 2 + buttonsize.y + 10));
	labelButtonsmain[0].setString("Play");
	labelButtonsmain[1].setString("Exit");
}
//Initialize pause interface
void HUD::InitializePauseHUD()
{
	for (int i = 0; i < 2; i++)
	{
		pausebuttons[i] = false;
		buttonspause[i].setSize(buttonsize + sf::Vector2<float>(10,0));
		buttonspause[i].setFillColor(buttoncolor);
		labelButtonspause[i].setCharacterSize(40);
		labelButtonspause[i].setFont(fontArial);
		labelButtonspause[i].setStyle(sf::Text::Bold);
	}

	buttonspause[0].setPosition(sf::Vector2<float>(StaticFunctions::WINDOW_WIDTH / 2 - (buttonsize.x / 2), StaticFunctions::WINDOW_HEIGHT / 2));
	buttonspause[1].setPosition(sf::Vector2<float>(StaticFunctions::WINDOW_WIDTH / 2 - (buttonsize.x / 2), StaticFunctions::WINDOW_HEIGHT / 2 + buttonsize.y + 10));
	labelButtonspause[0].setPosition(sf::Vector2<float>(StaticFunctions::WINDOW_WIDTH / 2 - (buttonsize.x / 2), StaticFunctions::WINDOW_HEIGHT / 2));
	labelButtonspause[1].setPosition(sf::Vector2<float>(StaticFunctions::WINDOW_WIDTH / 2 - (buttonsize.x / 2) + 60, StaticFunctions::WINDOW_HEIGHT / 2 + buttonsize.y + 10));
	labelButtonspause[0].setString("Main Menu");
	labelButtonspause[1].setString("Exit");

}
//Update all interfaces
void HUD::HUDUpdate(sf::Time &dt)
{
	if (roundstart)
	{
		popupAlpha -= 300.0 * dt.asSeconds();
		if (popupAlpha <= 0.0)
		{
			roundstart = false;
			popupAlpha = 0;
		}
	}
		
	textWavePopup.setFillColor(sf::Color(0, 255, 0, popupAlpha));
	stringScore = std::to_string(*score);
	stringWave = std::to_string(*wave);

	for (int i = 0; i < 2; i++)
	{
		if (backgroundSprite[i].getPosition().x >= StaticFunctions::WINDOW_WIDTH)
			backgroundSprite[i].setPosition(-StaticFunctions::WINDOW_WIDTH, 0);
		sf::Vector2<float> backgroundvelocity = backgroundSprite[i].getPosition() + sf::Vector2<float>(0.1f, 0.0f) * dt.asSeconds() * 200.f;
		backgroundSprite[i].setPosition(backgroundvelocity);
	}
		

	textWavePopup.setString("Wave: " + stringWave);
	textScore.setString("Score:  " + stringScore);
	textWave.setString("Wave:  " + stringWave);
	textTime.setString("Time:  " + StaticFunctions::RoundOneDecimal(clock->getElapsedTime().asSeconds()));

}
//Draw all interfaces depending on the current scene set by "bool scene" in GameManager.h"
void HUD::Draw()
{
	if (scene[0])
	{
		for (int i = 0; i < 2; i++)
		{
			window->draw(buttonsmain[i]);
			window->draw(labelButtonsmain[i]);
		}
			
	}
	else if (scene[1])
	{
		window->draw(hudbase);
		window->draw(textScore);
		window->draw(textWave);
		window->draw(textWavePopup);
		window->draw(textTime);
		for (int i = 0; i < 4; i++)
			window->draw(textDirection[i]);
	}

	if (scene[2])
	{
		for (int i = 0; i < 2; i++)
		{
			window->draw(buttonspause[i]);
			window->draw(labelButtonspause[i]);
		}
	}

}
//Draw the background (reason for a seperate function is to draw it before everything else)
void HUD::DrawBackground()
{
	for(int i = 0;i<2;i++)
		window->draw(backgroundSprite[i]);
}
//Interface input handling
void HUD::Input()
{
	for (int i = 0; i < 2; i++)
	{
		if (scene[0])
		{
			if (sf::Mouse::getPosition(*window).x >= buttonsmain[i].getPosition().x &&
				sf::Mouse::getPosition(*window).x <= buttonsmain[i].getPosition().x + buttonsmain[i].getSize().x &&
				sf::Mouse::getPosition(*window).y >= buttonsmain[i].getPosition().y &&
				sf::Mouse::getPosition(*window).y <= buttonsmain[i].getPosition().y + buttonsmain[i].getSize().y)
			{
				buttonsmain[i].setFillColor(sf::Color::Blue);
				mainbuttons[i] = true;
			}
			else
			{
				buttonsmain[i].setFillColor(buttoncolor);
				mainbuttons[i] = false;
			}
		}
		if (scene[2])
		{
			if (sf::Mouse::getPosition(*window).x >= buttonspause[i].getPosition().x &&
				sf::Mouse::getPosition(*window).x <= buttonspause[i].getPosition().x + buttonspause[i].getSize().x &&
				sf::Mouse::getPosition(*window).y >= buttonspause[i].getPosition().y &&
				sf::Mouse::getPosition(*window).y <= buttonspause[i].getPosition().y + buttonspause[i].getSize().y)
			{
				buttonspause[i].setFillColor(sf::Color::Blue);
				pausebuttons[i] = true;
			}
			else
			{
				buttonspause[i].setFillColor(buttoncolor);
				pausebuttons[i] = false;
			}
		}
	}
}
//Poll for interface clicks
void HUD::Poll(sf::Event &Event)
{
	for (int i = 0; i < 2; i++)
	{
		if (scene[0])
		{
			if (mainbuttons[i])
			{
				switch (Event.mouseButton.button)
				{
				case sf::Mouse::Button::Left:
					switch (i)
					{
					case 0:
						std::cout << "Play" << std::endl;
						option = PLAY;
						break;
					case 1:
						std::cout << "Exit" << std::endl;
						option = EXIT;
						break;
					}
					break;
				}
			}
			else
			{
				buttonsmain[i].setFillColor(buttoncolor);
			}
		}
		if (scene[2])
		{
			if (pausebuttons[i])
			{
				switch (Event.mouseButton.button)
				{
				case sf::Mouse::Button::Left:
					switch (i)
					{
					case 0:
						std::cout << "Play" << std::endl;
						option = MAIN;
						break;
					case 1:
						std::cout << "Exit" << std::endl;
						option = EXIT;
						break;
					}

					break;
				}
			}
			else
			{
				buttonspause[i].setFillColor(buttoncolor);
			}
		}
	}
}
//On roundstart
void HUD::RoundStart()
{
	roundstart = true;
	popupAlpha = 255;

	for(int i = 0;i<4;i++)
		textDirection[i].setFillColor(sf::Color(255, 0, 0, 0));
}
//Flash the warning symbol "!" in game depending on which direction obstacles appear from
void HUD::FlashDirection(bool *p_direction)
{
	if (flash.getElapsedTime().asSeconds() > 0.5f)
	{
		for (int i = 0; i < 4; i++)
		{
			if (p_direction[i])
			{
				SetDirectionTextAlpha(255, p_direction);
			}
		}	
	}

	if (flash.getElapsedTime().asSeconds() > 1.f)
	{
		for (int i = 0; i < 4; i++)
		{
			if (p_direction[i])
			{
				SetDirectionTextAlpha(0, p_direction);
			}
		}
		flash.restart();
	}		
}
//Set the warning symbol alpha
void HUD::SetDirectionTextAlpha(float alpha, bool *p_direction)
{
	for (int i = 0; i < 4; i++)
	{
		if (p_direction[i])
		{
			textDirection[i].setFillColor(sf::Color(255, 0, 0, alpha));
		}
	}
}