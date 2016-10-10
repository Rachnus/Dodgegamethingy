#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
class Obstacle
{
public:
	Obstacle(int p_wave, const unsigned char p_startingflags, bool *p_direction);
	~Obstacle();
	sf::Vector2<float> shapepos;
	sf::Vector2<float> shapesize;
	sf::Vector2<float> shapevelocity;
	sf::Color shapecolor;

	void Initialize();
	void Update(sf::Time &dt);
	void Draw(sf::RenderWindow &window);
	bool IsOutOfBounds();
	bool IsCollidingWithPlayer(sf::Vector2<float> &playerpos, sf::Vector2<float> &playersize);

	static int objectspassed;
	static int totalobjectspassed;
private:
	sf::RectangleShape shape;
	unsigned char startingflags;

	int wave;
	int startingdir;

	const int maxsize = 100.f;

	const int minvelocity = 200.f;
	const int maxvelocity = 500.f;
	bool *direction;



	enum StartingDirections
	{
		LEFT = 0,
		RIGHT,
		UP,
		DOWN
	};

	enum StartingFlags
	{
		WAVING = 1,
		SPEED = 2,
		SIZE = 4
	};
};

