#include "Player.h"
#include <iostream>
#include "StaticFunctions.h"

Player::Player(sf::Vector2f pos)
{
	direction = 0;
	playervelocity = sf::Vector2<float>(0, 0);
	playersize = sf::Vector2<float>(6, 6);
	playerpos = pos;

	playershape.setSize(playersize);
	playershape.setPosition(playerpos);
	playershape.setFillColor(sf::Color::Red);
	
}


Player::~Player()
{
}

//Update players movement
void Player::Update(sf::Time &dt)
{

	playervelocity = sf::Vector2f(0, 0);

	if ((direction & UP))
		playervelocity.y += -700.0f;
	if ((direction & DOWN))
		playervelocity.y += 700.0f;
	if ((direction & LEFT))
		playervelocity.x += -700.0f;
	if ((direction & RIGHT))
		playervelocity.x += 700.0f;

	playerpos = playerpos + (playervelocity * dt.asSeconds());

	if (playerpos.x + playersize.x >= StaticFunctions::WINDOW_WIDTH)
		playerpos.x = StaticFunctions::WINDOW_WIDTH - playersize.x;
	if (playerpos.x <= 0)
		playerpos.x = 0;
	if (playerpos.y + playersize.y >= StaticFunctions::WINDOW_HEIGHT - StaticFunctions::HUD_OFFSET)
		playerpos.y = StaticFunctions::WINDOW_HEIGHT - playersize.y - StaticFunctions::HUD_OFFSET;
	if (playerpos.y <= 0)
		playerpos.y = 0;

	playershape.setPosition(playerpos);
}
//Draw player
void Player::Draw(sf::RenderWindow *window)
{
	window->draw(playershape);
}
//Input handling for player
void Player::Input()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		direction |= RIGHT;
	else 
		direction &= ~RIGHT;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		direction |= LEFT;
	else
		direction &= ~LEFT;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		direction |= UP;
	else
		direction &= ~UP;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		direction |= DOWN;
	else
		direction &= ~DOWN;
}

