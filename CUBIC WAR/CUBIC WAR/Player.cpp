#include "Player.h"


void Player::initVariable()
{
	this->movementSpeed = 10.f;

}

void Player::initShape()
{
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setSize(sf::Vector2f(50.f, 50.f));
}

void Player::randomporition()
{
	startposition.x = rand() % 11;
	startposition.y = rand() % 15;
	if (startposition.x <= 6 && startposition.y <= 8)
	{
		std::cout << "spawn at left top\n";
		shape.setPosition(200.f, 150.f);
		
	}
	else if (startposition.x <= 6 && startposition.y > 8)
	{
		std::cout << "spawn at right top\n";
		shape.setPosition(700.f, 150.f);
	}
	else if (startposition.x > 6 && startposition.y <= 8)
	{
		std::cout << "spawn at left down\n";
		shape.setPosition(200.f, 450.f);
	}
	else if (startposition.x > 6 && startposition.y > 8)
	{
		std::cout << "spawn at right down\n";
		shape.setPosition(700.f, 4500.f);
	}
	
}

Player::Player(float x, float y)
{
	this->randomporition();
	this->initVariable();
	this->initShape();
}

Player::~Player()
{

}

void Player::updateInput()
{
	//Keyboard input
	//Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->shape.move(-this->movementSpeed, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->shape.move(this->movementSpeed, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->shape.move(0.f,-this->movementSpeed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->shape.move(0.f,this->movementSpeed);
	}
}

void Player::update(sf::RenderTarget* target)
{
	//Window bounds collision


	this->updateInput();

}

void Player::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
}