#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>

class unit
{
private:
	string name;
	int hp;
	int maxhp;
	int atk;
	int atk range;
	int atk f soldier;
	int atk f building;
	int move range;
	int direction;
	int vision;
	int points;

public:
	void engineering();
	void soldier();
	void archer();
	void artillery();
	void scouts();
};

