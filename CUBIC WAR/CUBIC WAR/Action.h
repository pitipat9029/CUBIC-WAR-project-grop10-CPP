#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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

	sf::SoundBuffer soundBufferclick;
	sf::Sound clicksound;
	sf::SoundBuffer soundBufferatk;
	sf::Sound atksound;
	sf::SoundBuffer backgroundBuffer;
	sf::Sound backgroundsound;

	sf::Font font;
	sf::Text Playerturn;
	sf::Text text;
	sf::Text pointPtext;
	sf::Text endturn;
	sf::Text rolltext;
	sf::Text UcanRolltext;

	sf::RectangleShape bar;
	sf::RectangleShape button;
	sf::RectangleShape rollbtn;

	Map* pMap = 0;

	int countTurn = 0;

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
	bool isButtonPress = false;

	Grid* pGridSelected = 0;
	Grid* pGridPointed = 0;
	ActionButton* pButtonAPointed = 0;

	void initFont();
	void intitText();
	void initAudio();
	void initBar();
	void initButton();
	void DoCommand();
	void ClickEvents();
	void NextTurn();
	void SetToNormalMode();
	void RandomStartPosition();
	ActionButton* GetButtonAPointed(std::vector<ActionButton*>);

	void Move();

	void RenderMenu(int);
	
public:
	bool isGamePlaying = false;
	bool isGameEnd = false;
	bool isWin = false;

	Action(sf::RenderWindow*);
	~Action();

	void renderText(sf::RenderTarget*);
	void Render();
	void StartGame(int);
	void GameEnd();
};