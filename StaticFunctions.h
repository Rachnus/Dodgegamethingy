#pragma once
#include <SFML/Graphics.hpp>

class StaticFunctions
{
public:
	static void Normalize(sf::Vector2f &v);
	static void PrintLength(sf::Vector2f &v);
	static sf::Vector2f GetLength(sf::Vector2f v);
	static std::string RoundOneDecimal(float input);

	static const int WINDOW_WIDTH = 1600;
	static const int WINDOW_HEIGHT = 900;
	static const int HUD_OFFSET = 80;
	
};

