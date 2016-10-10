#include "Obstacle.h"
#include "StaticFunctions.h"
#include <iostream>

int Obstacle::objectspassed = 0;
int Obstacle::totalobjectspassed = 0;

Obstacle::Obstacle(int p_wave, const unsigned char p_startingflags, bool *p_direction)
	:
	wave(p_wave),
	startingflags(p_startingflags),
	direction(p_direction)
{
	Initialize();
}


Obstacle::~Obstacle()
{

}
//Initialize an object (Setting its starting position, velocity, size and other special movement)
void Obstacle::Initialize()
{
	do
	{
		startingdir = rand() % 4;
	} while (!direction[startingdir]);

	shapepos = sf::Vector2<float>(0, 0);
	shapesize = sf::Vector2<float>(5, 5);
	shapevelocity = sf::Vector2<float>(0, 0);
	
	shapecolor = sf::Color::Green;

	if (startingflags & StartingFlags::SIZE && wave >= 10)
	{
		shapesize = sf::Vector2<float>(rand() % (25 * (1 + (wave / 20))) + 5, rand() % (25 * (1 + (wave / 20))) + 5);
		if (shapesize.y > maxsize)
			shapesize.y = maxsize;
		if (shapesize.x > maxsize)
			shapesize.x = maxsize;
	}


	if (direction[0] && startingdir == 0)
	{
		shapepos.x = 0 - shapesize.x;
		shapepos.y = rand() % (StaticFunctions::WINDOW_HEIGHT + 1) - StaticFunctions::HUD_OFFSET - shapesize.y;
		shapevelocity = sf::Vector2<float>(500.f, 0.f);

		if (startingflags & StartingFlags::SPEED && wave >= 5)
			shapevelocity = sf::Vector2<float>(rand() % maxvelocity + minvelocity, 0.f);
	}
	if (direction[1] && startingdir == 1)
	{
		shapepos.x = StaticFunctions::WINDOW_WIDTH;
		shapepos.y = rand() % (StaticFunctions::WINDOW_HEIGHT + 1) - StaticFunctions::HUD_OFFSET - shapesize.y;
		shapevelocity = sf::Vector2<float>(-500.f, 0.f);

		if (startingflags & StartingFlags::SPEED && wave >= 5)
			shapevelocity = sf::Vector2<float>(-(rand() % maxvelocity + minvelocity), 0.f);
	}
	if (direction[2] && startingdir == 2)
	{
		shapepos.x = rand() % (StaticFunctions::WINDOW_WIDTH + 1) - StaticFunctions::HUD_OFFSET - shapesize.x;
		shapepos.y = 0 - shapesize.y;
		shapevelocity = sf::Vector2<float>(0.f, 500.f);

		if (startingflags & StartingFlags::SPEED && wave >= 5)
			shapevelocity = sf::Vector2<float>(0.f, rand() % maxvelocity + minvelocity);
	}
	if (direction[3] && startingdir == 3)
	{
		shapepos.x = rand() % (StaticFunctions::WINDOW_WIDTH + 1) - StaticFunctions::HUD_OFFSET - shapesize.x;
		shapepos.y = StaticFunctions::WINDOW_HEIGHT;
		shapevelocity = sf::Vector2<float>(0.f, -500.f);

		if (startingflags & StartingFlags::SPEED && wave >= 5)
			shapevelocity = sf::Vector2<float>(0.f, -(rand() % maxvelocity  + minvelocity));
	}
}
//Update the obstacle
void Obstacle::Update(sf::Time &dt)
{

	if (IsOutOfBounds())
	{
		objectspassed++;
		totalobjectspassed++;
		Initialize();
	}


	if (startingflags& StartingFlags::WAVING && wave >= 15 && (shapesize.x > 30 || shapesize.y > 30))
	{
		if ((direction[0] || direction[1]) && shapevelocity.x <= 300.f *(wave / 20) && (startingdir == 0 || startingdir == 1))
			shapevelocity.y = sin(shapepos.x / 50) * (100 * (wave/20));

		if ((direction[2] || direction[3]) && shapevelocity.y <= 300.f *(wave / 20) && (startingdir == 3 || startingdir == 4))
			shapevelocity.x = sin(shapepos.y / 50) * (100 * (wave/20));
	}

	shapepos = shapepos + (shapevelocity * dt.asSeconds());
	
	shape.setSize(shapesize);
	shape.setFillColor(shapecolor);
	shape.setPosition(shapepos);
}
//Draw the obstacle
void Obstacle::Draw(sf::RenderWindow &window)
{
	window.draw(shape);
}
//Check if the obstacle is out of the view port
bool Obstacle::IsOutOfBounds()
{
	if (shapepos.x > (StaticFunctions::WINDOW_WIDTH + 10))
		return true;
	if (shapepos.x < 0 - (shapesize.x + 10))
		return true;
	if (shapepos.y > (StaticFunctions::WINDOW_HEIGHT + 10))
		return true;
	if (shapepos.y < 0 - (shapesize.y + 10))
		return true;

	return false;
}
//Check if the obstacle is colliding with player
bool Obstacle::IsCollidingWithPlayer(sf::Vector2<float> &playerpos, sf::Vector2<float> &playersize)
{
	if (shapepos.x + shapesize.x > playerpos.x &&
		shapepos.x < playerpos.x + playersize.x &&
		shapepos.y + shapesize.y > playerpos.y &&
		shapepos.y < playerpos.y + playersize.y)
	{
		return true;
	}
	return false;
}