#include "Player.h"

void Player::randomporition()
{
	startposition.x = rand() % 11;
	startposition.y = rand() % 15;
	if (startposition.x <= 6 && startposition.y <= 8)
	{
		std::cout << "spawn at left top\n";
	}
	else if (startposition.x <= 6 && startposition.y > 8)
	{
		std::cout << "spawn at right top\n";
	}
	else if (startposition.x > 6 && startposition.y <= 8)
	{
		std::cout << "spawn at left down\n";
	}
	else if (startposition.x > 6 && startposition.y > 8)
	{
		std::cout << "spawn at right down\n";
	}
	
}

Player::Player(float x, float y)
{
	std::cout << "Player was create" << std::endl;
}

Player::~Player()
{
	std::cout << "Player was delect" << std::endl;
}