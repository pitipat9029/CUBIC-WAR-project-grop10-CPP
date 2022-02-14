#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>

#include "Map.h"
#include "Player.h"
#include "Grid.h"

class Action
{
private:
	void Update();
	void updateText();

	sf::RenderWindow* pWindow;

	sf::Font font;
	sf::Text Playerturn;
	sf::Text text;
	sf::Text pointtext;
	sf::Text endturn;
	sf::Text rolltext;

	sf::RectangleShape bar;
	sf::RectangleShape button;
	sf::RectangleShape rollbtn;

	Map* pMap = 0;

	int countTurn = 0;
	int point = 0;

	int idPlayerNow = 0;
	std::vector<Player*> vPlayers;
	
	std::vector<sf::Sprite> grids;

	sf::Vector2f* pMousePosView;
	sf::Vector2i currentMousePos;
	bool isMousePress = false;

	bool isWait = false;
	bool isMoveMode = false;
	bool isCreatdMode = false;

	Grid* pGridMoveStart = 0;
	Grid* pGridPointed = 0;

	Grid* CheckGridPointed();
	void CreateGridArea(int);

	void initFont();
	void intitText();
	void initBar();
	void initButton();

	void ClickEvents();
	void NextTurn();

	void HighlightGridPointed(sf::Color, sf::Color);
	void HighlightGridArea(sf::Color, sf::Color);
	void ShowGridHighlight();
	void RandomStartPosition();

	void RenderUnit();
	void Move();
	
public:
	Action(sf::RenderWindow*, sf::Vector2f*);
	~Action();

	void renderText(sf::RenderTarget*);
	void Render();
	void StartGame(int);
	void GameEnd();
};