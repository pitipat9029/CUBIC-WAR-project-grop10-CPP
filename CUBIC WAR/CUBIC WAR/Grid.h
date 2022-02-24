#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <cmath>

#include "Unit.h"
#include "ActionButton.h"

class Grid
{
private:
	bool enabled = true;

	// Figure -----
	int row = 0, column = 0;
	sf::Vector2f size;
	sf::Vector2f centerPos;
	std::string imgPath = "";
	sf::Texture texture;
	sf::Sprite shape;
	
	void Setup();

	bool idPlayersVision[2] = {};
	int idPlayerHere = -1;

	// Building ----
	int hp = 0, maxhp = 0;
	int atk = 0;
	std::string* pListMenu = 0;
	sf::RectangleShape hpBar;
	void RenderHpBar(sf::RenderTarget* target, bool isEnemy);

	// Unit -------
	Unit* pUnit = 0;

	
public:
	bool isBuilding = false;
	bool isUnit = false;
	std::vector<std::vector<ActionButton*>> vActionButton;

	Grid(int, int, sf::Vector2f);
	~Grid();

	void setActionButtons(int, std::string[] , int[]);
	std::string typeBuilding = "";

	void RenderGrid(sf::RenderTarget*, int idPlayerNow);
	void RenderUnit(sf::RenderTarget*, int idPlayerNow);
	Grid* CreateBuilding(std::string type, int);
	void SetEnabled(bool);

	void ShowInCreate(sf::Texture, sf::RenderTarget*);
	bool isPointed(sf::Vector2i);
	bool isEnabled();
	float distanceFromMouse(sf::Vector2i);
	sf::Vector2f GetPosition();
	sf::Vector2i GetRC();
	sf::Vector2f GetCenterPoint();
	void UpdatePlayerVision(int idPlayer);
	bool GetPlayerVision(int idPlayer);

	//Building
	int GetAttackPoint();
	void ClearBuilding();
	bool isMyBuilding(int idPlayer);
	
	// Unit
	Grid* AddUnit(std::string type, std::vector<Unit*>&, int);
	Grid* AddUnit(Unit*);
	void ClearUnit();
	Unit* GetUnit();
	bool BeAttack(int);
	int Attack();
};

