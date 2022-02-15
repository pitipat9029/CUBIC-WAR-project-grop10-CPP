#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>

#include "Map.h"
#include "Player.h"
#include "Grid.h"
#include "ActionButton.h"

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
	std::vector<ActionButton*> vActionButtonNow;
	
	std::vector<sf::Sprite> grids;

	sf::Vector2f* pMousePosView;
	sf::Vector2i currentMousePos;
	bool isMousePress = false;

	std::string gMode = "Normal";
	std::string typeToCreate = "";
	bool isWait = false;
	bool isMenuOpen = false;

	Grid* pGridSelected = 0;
	Grid* pGridPointed = 0;
	ActionButton* pButtonAPointed = 0;

	void initFont();
	void intitText();
	void initBar();
	void initButton();

	void ClickEvents();
	void NextTurn();
	void SetToNormalMode();
	void RandomStartPosition();
	ActionButton* GetButtonAPointed(std::vector<ActionButton*>);

	void Move();

	void RenderMenu(int);
	
public:
	Action(sf::RenderWindow*);
	~Action();

	void renderText(sf::RenderTarget*);
	void Render();
	void StartGame(int);
	void GameEnd();
};