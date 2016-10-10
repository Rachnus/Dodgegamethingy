#include "StaticFunctions.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
//Normalize vectors
void StaticFunctions::Normalize(sf::Vector2f &v)
{
	double hyp = sqrt(v.x*v.x + v.y*v.y);
	v.x = v.x / hyp;
	v.y = v.y / hyp;
}
//Get vector length (not used, only for experimental purposes)
sf::Vector2f StaticFunctions::GetLength(sf::Vector2f v)
{
	double hyp = sqrt(v.x*v.x + v.y*v.y);
	return v;
}
//Print the length of a vector (not used, only for experimental purposes)
void StaticFunctions::PrintLength(sf::Vector2f &v)
{
	double hyp = sqrt(v.x*v.x + v.y*v.y);
	std::cout << "Length: " << hyp << std::endl;
}
//Round a float to 1 decimal (Used for the ingame timer)
std::string StaticFunctions::RoundOneDecimal(float input)
{
	std::ostringstream out;
	out << std::setprecision(1) << std::fixed << std::showpoint << input;
	std::string roundResult = out.str();

	return roundResult;
}