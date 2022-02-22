#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Unit
{
private:
	sf::Sprite shape;
	sf::RectangleShape hpBar;
	std::string imgPath = "";
	sf::Texture texture;
	sf::Vector2f size;
	
	std::string type = "";
	int hp;
	int maxhp;
	int price;
	int atk;
	int moveRadius;

	int idPlayer;

public:
	Unit(std::string, sf::Vector2f, int);
	~Unit();
	void Render(sf::RenderTarget* target, int idPlayerNow);
	void RenderHpBar(sf::RenderTarget* target, bool isEnemy);
	int GetAttackPoint();
	bool BeAttack(int);
	void SetSize(float, float);
	void Move(sf::Vector2f);
	void destroy();
	bool isMyUnit(int);
	std::string GetType();
};


