#include "Game.h"
#include <SFML/Audio.hpp>
#include <iostream>

int main()
{
	srand(time(NULL));

	Game game;
	game.Run();
}