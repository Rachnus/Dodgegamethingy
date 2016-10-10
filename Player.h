#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player(sf::Vector2f pos);
	~Player();

	void Update(sf::Time &dt);
	void Draw(sf::RenderWindow *window);
	void Input();

	sf::RectangleShape playershape;
	sf::Vector2<float> playerpos;
	sf::Vector2<float> playersize;
	sf::Vector2<float> playervelocity;
private:
	unsigned char direction;

	enum Direction
	{
		UP = 0x01,
		DOWN = 0x02,
		LEFT = 0x04,
		RIGHT = 0x08
	};
};

