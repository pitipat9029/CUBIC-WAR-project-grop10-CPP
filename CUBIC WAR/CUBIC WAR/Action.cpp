#include "Action.h"

Action::Action(sf::RenderWindow* pWindow)
{
	this->pWindow = pWindow;
	this->intitText();
	this->initFont();
	this->initBar();
	this->initButton();
	this->initAudio();
}

Action::~Action()
{
	if (this->isGamePlaying) {
		GameEnd();
	}
}

void Action::StartGame(int numPlayer)
{
	backgroundsound.play();
	isGamePlaying = true;
	isGameEnd = false;
	isButtonPress = false;
	this->pMap = new Map(this->pWindow, &this->currentMousePos, &this->idPlayerNow);

	for (int i = 0; i < numPlayer; i++) {
		this->vPlayers.push_back(new Player);
	}
	countTurn = 0;
	RandomStartPosition();
	this->NextTurn();
}

void Action::GameEnd()
{
	this->isGamePlaying = false;
	for (int i = 0; i < this->vPlayers.size(); i++) {
		delete this->vPlayers[i];
	}
	delete this->pMap;
	this->vPlayers.clear();
	backgroundsound.stop();
}

void Action::RandomStartPosition()
{
	int player1Xstart = rand() % 3 + 3;
	int player1Ystart = rand() % 7 + 3;
	int player2Xstart = rand() % 3 + 10;
	int player2Ystart = rand() % 7 + 3;
	this->pMap->UpdatePlayerVision(this->pMap->vGrids[player1Ystart][player1Xstart].CreateBuilding("B", 0), 1,0);
	this->pMap->UpdatePlayerVision(this->pMap->vGrids[player1Ystart + rand()%2][player1Xstart + 1].AddUnit("Engineer", this->pMap->vUnits, 0), 1, 0);
	this->pMap->UpdatePlayerVision(this->pMap->vGrids[player2Ystart][player2Xstart].CreateBuilding("B", 1), 1, 1);
	this->pMap->UpdatePlayerVision(this->pMap->vGrids[player2Ystart - 1][player2Xstart - rand()%2].AddUnit("Engineer", this->pMap->vUnits, 1), 1, 1);
}

void Action::ClickEvents()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		if (!this->isMousePress) {
			// Mouse Left click
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (this->isWait) {
					this->isWait = false;
				}
				else {
					if (this->isMenuOpen) {
						if (this->pButtonAPointed != 0) {
							this->DoCommand();
						}
						else {
							this->isMenuOpen = false;
							this->pButtonAPointed = 0;
							this->SetToNormalMode();
						}
					}
					else if (this->pGridPointed != 0 && !this->isMenuOpen && this->pGridSelected != 0) {
						if (gMode == "Move") {
							this->vPlayers[this->idPlayerNow]->point -= this->pButtonAPointed->GetUsePoint();
							this->Move();
							this->SetToNormalMode();
							clicksound.play();
						}
						else if (gMode == "Build") {
							this->vPlayers[this->idPlayerNow]->point -= this->pButtonAPointed->GetUsePoint();
							this->pMap->UpdatePlayerVision(this->pGridPointed->CreateBuilding(this->typeToCreate, this->idPlayerNow), 1, this->idPlayerNow);
							this->SetToNormalMode();
							atksound.setBuffer(soundBufferBuild);
							atksound.play();
						}
						else if (gMode == "Create") {
							this->vPlayers[this->idPlayerNow]->point -= this->pButtonAPointed->GetUsePoint();
							this->pMap->UpdatePlayerVision(this->pGridPointed->AddUnit(this->typeToCreate, this->pMap->vUnits, this->idPlayerNow), 1, this->idPlayerNow);
							this->SetToNormalMode();
							clicksound.play();
						}
						else if (gMode == "Attack") {
							this->vPlayers[this->idPlayerNow]->point -= this->pButtonAPointed->GetUsePoint();
							isGameEnd = this->pGridPointed->BeAttack(this->pGridSelected->Attack());
							this->SetToNormalMode();
							atksound.setBuffer(soundBufferatk);
							clicksound.play();
						}
					}
					else if (this->pGridPointed != 0 && !this->isMenuOpen) {
						this->pGridSelected = pGridPointed;
						if (this->pGridSelected->vActionButton.size() > 0 && ((pGridSelected->isUnit && pGridSelected->GetUnit()->isMyUnit(idPlayerNow)) || (pGridSelected->isBuilding && pGridSelected->isMyBuilding(idPlayerNow)))) {
							if (pGridSelected->GetUnit() != 0) {
								if (this->pGridSelected->vActionButton[0][0]->GetUsePoint() <= this->vPlayers[this->idPlayerNow]->point) {
									this->pButtonAPointed = this->pGridSelected->vActionButton[0][0];
									this->DoCommand();
								}
							}
							else if (this->pGridSelected->typeBuilding == "M") {
								if (this->pGridSelected->vActionButton[0][0]->GetUsePoint() <= this->vPlayers[this->idPlayerNow]->point) {
									this->pButtonAPointed = this->pGridSelected->vActionButton[0][0];
									this->isMenuOpen = true;
									this->DoCommand();
								}
							}
							else {
								if (this->pGridSelected->vActionButton[0][0]->GetUsePoint() <= this->vPlayers[this->idPlayerNow]->point) {
									this->pButtonAPointed = this->pGridSelected->vActionButton[0][0];
									this->DoCommand();
								}
							}
						}
					}
					else if (this->pGridPointed == 0) {
						this->SetToNormalMode();
					}
				}
			}
			
			//endturn button click
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (button.getGlobalBounds().contains(sf::Mouse::getPosition(*pWindow).x, sf::Mouse::getPosition(*pWindow).y))
				{
					clicksound.play();
					std::cout << " => End Turn" << std::endl;
					UcanRolltext.setPosition(905.f, 605.f);
					NextTurn();
					isButtonPress = false;
				}
			}
			//roll button click
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (rollbtn.getGlobalBounds().contains(sf::Mouse::getPosition(*pWindow).x, sf::Mouse::getPosition(*pWindow).y))
				{
					clicksound.play();
					int ran1 = rand() % 6 + 1;
					int ran2 = rand() % 6 + 1;
					this->vPlayers[this->idPlayerNow]->point += ran1 + ran2;
					if (ran1 == ran2)
					{
						isButtonPress = false;
						UcanRolltext.setPosition(520.f, 560.f);
						std::cout << "U can roll again";
					}
					else
					{
						UcanRolltext.setPosition(905.f, 605.f);
						isButtonPress = true;
					}
				}
			}
			// Mouse Right click
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				if (this->gMode == "Normal" && !isMenuOpen && this->pGridPointed != 0) {
					if ((pGridPointed->isUnit && pGridPointed->GetUnit()->isMyUnit(idPlayerNow)) || (pGridPointed->isBuilding && pGridPointed->isMyBuilding(idPlayerNow))) {
						if (this->pGridPointed->vActionButton.size() > 0) {
							this->pGridSelected = this->pGridPointed;
							this->isMenuOpen = true;
							this->pGridPointed = 0;
						}
					}
				}
				else {
					//this->SetToNormalMode();
				}
			}
			this->isMousePress = true;
		}
	}
	else {
		this->isMousePress = false;
	}
}

void Action::Move()
{
	this->pGridPointed->AddUnit(this->pGridSelected->GetUnit());
	this->pMap->UpdatePlayerVision(pGridPointed, 1, this->idPlayerNow);
	this->pGridSelected->ClearUnit();
	this->vPlayers[this->idPlayerNow]->whereAttack; //dont know how to do next
}

void Action::RenderMenu(int deep)
{
	float r = 15, grab = 5;
	int x = pGridSelected->vActionButton[deep].size();
	this->vActionButtonNow = pGridSelected->vActionButton[deep];
	sf::Vector2f centerPos = this->pGridSelected->GetCenterPoint();
	float startX = ((r * x * 2) + (grab * (x - 3))) / 2;
	for (int i = 0; i < x; i++) {
		pGridSelected->vActionButton[deep][i]->SetPosition(sf::Vector2f((centerPos.x - startX) + ((grab + r * 2) * i), centerPos.y - 40));
		pGridSelected->vActionButton[deep][i]->Render(this->pWindow, vPlayers[this->idPlayerNow]->point);
	}
}

void Action::NextTurn()
{
	this->isWait = true;
	if (this->countTurn == 0) {
		idPlayerNow = 0;
		this->countTurn++;
	}
	else if (this->idPlayerNow < this->vPlayers.size() - 1) {
		this->idPlayerNow++;
	}
	else {
		this->idPlayerNow = 0;
		this->countTurn++;
	}
	this->SetToNormalMode();
	std::cout << "Turn: " << countTurn;
	std::cout << " ----> Player " << idPlayerNow + 1 << " is playing";
}

void Action::SetToNormalMode()
{
	this->gMode = "Normal";
	this->typeToCreate = "";
	this->pGridSelected = 0;
	this->pButtonAPointed = 0;
	this->pMap->SetGridAllEnable(true);
}

void Action::Update()
{
	this->currentMousePos = sf::Mouse::getPosition(*this->pWindow);
	this->pGridPointed = this->pMap->UpdatePointedGrid();
	if (this->isMenuOpen) {
		this->pButtonAPointed = this->GetButtonAPointed(this->vActionButtonNow);
	}
	//button change color
	if (button.getGlobalBounds().contains(sf::Mouse::getPosition(*pWindow).x, sf::Mouse::getPosition(*pWindow).y))
	{
		sf::Color lor(128, 128, 128);
		button.setFillColor(lor);
		rollbtn.setFillColor(lor);
	}
	else
	{
		sf::Color col(192, 192, 192);
		button.setFillColor(col);
		rollbtn.setFillColor(col);
	}

	if (rollbtn.getGlobalBounds().contains(sf::Mouse::getPosition(*pWindow).x, sf::Mouse::getPosition(*pWindow).y))
	{
		sf::Color lor(128, 128, 128);
		rollbtn.setFillColor(lor);
	}
	else
	{
		sf::Color col(192, 192, 192);
		rollbtn.setFillColor(col);
	}

	// move roll button
	if (isButtonPress == true)
	{
		rollbtn.setPosition(910.f,610.f);
		rolltext.setPosition(910.f, 610.f);
	}
	else
	{
		rollbtn.setPosition(700.f, 550.f);
		rolltext.setPosition(705.f, 560.f);
	}
	updateText();
	ClickEvents();
}

void Action::Render()
{
	if (isWait == false) {
		this->pMap->RenderMap();
		if (!isMenuOpen && !(gMode == "SelectBuild" || gMode == "SelectCreate")) {
			this->pMap->ShowGridHighlight(this->gMode);
		}
		this->pMap->RenderUnits();
		if (isMenuOpen && (gMode == "SelectBuild" || gMode == "SelectCreate")) {
			this->RenderMenu(1);
		}
		else if(isMenuOpen) {
			this->RenderMenu(0);
		}
			
		pWindow->draw(bar);
		pWindow->draw(button);
		pWindow->draw(rollbtn);
		pWindow->draw(endturn);
		pWindow->draw(rolltext);
		pWindow->draw(UcanRolltext);
		pWindow->draw(pointPtext);
	}
	else
	{
		this->updateText();
		this->renderText(this->pWindow);
		pWindow->draw(text);
	}

	this->Update();

	if (isGameEnd) {
		this->GameEnd();
	}
}

void Action::renderText(sf::RenderTarget *target)
{
	target->draw(this->Playerturn);
}

void Action::initFont()
{
	this->font.loadFromFile("Fonts/gomarice_no_continue.ttf");
}

void Action::intitText()
{
	this->Playerturn.setFont(this->font);
	this->Playerturn.setFillColor(sf::Color::White);
	this->Playerturn.setCharacterSize(32);
	this->Playerturn.setPosition(350.f, 280.f);

	//Click to start text
	this->text.setFont(this->font);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(18);
	this->text.setPosition(680.f, 567.f);
	this->text.setString("-> Click to Start ur turn");
	//point text
	this->pointPtext.setFont(this->font);
	this->pointPtext.setFillColor(sf::Color::White);
	this->pointPtext.setCharacterSize(32);
	this->pointPtext.setPosition(5.f, 550.f);

	//endtuentext
	this->endturn.setFont(this->font);
	this->endturn.setFillColor(sf::Color::White);
	this->endturn.setCharacterSize(20);
	this->endturn.setPosition(805.f, 560.f);
	endturn.setString("End Turn");

	this->rolltext.setFont(this->font);
	this->rolltext.setFillColor(sf::Color::White);
	this->rolltext.setCharacterSize(20);
	this->rolltext.setPosition(705.f, 560.f);
	rolltext.setString("Roll");

	this->UcanRolltext.setFont(this->font);
	this->UcanRolltext.setFillColor(sf::Color::White);
	this->UcanRolltext.setCharacterSize(20);
	this->UcanRolltext.setPosition(905.f, 605.f);
	UcanRolltext.setString("U can roll again!!");
}

void Action::initAudio()
{
	soundBufferclick.loadFromFile("Sounds/click.wav");
	clicksound.setBuffer(soundBufferclick);
	clicksound.setVolume(25.f);

	soundBufferatk.loadFromFile("Sounds/attack.wav");
	atksound.setBuffer(soundBufferatk);
	atksound.setVolume(25.f);

	soundBufferBuild.loadFromFile("Sounds/Build.wav");
	atksound.setVolume(25.f);

	backgroundBuffer.loadFromFile("Sounds/background.wav");
	backgroundsound.setBuffer(backgroundBuffer);
	backgroundsound.setVolume(10.f);
	backgroundsound.setLoop(true);
}

void Action::initBar()
{
	sf::Color temp(196, 164, 132);
	this->bar.setFillColor(temp);
	this->bar.setSize(sf::Vector2f(900.f, 100.f));
	this->bar.setPosition(0.f, 550.f);
}

void Action::initButton()
{
	sf::Color col(192, 192, 192);
	this->button.setFillColor(col);
	this->button.setSize(sf::Vector2f(100.f, 50.f));
	this->button.setPosition(800.f, 550.f);

	this->rollbtn.setFillColor(col);
	this->rollbtn.setSize(sf::Vector2f(50.f, 50.f));
	this->rollbtn.setPosition(700.f, 550.f);
}	

void Action::DoCommand()
{
	std::string command = pButtonAPointed->GetActionCommand(this->vPlayers[this->idPlayerNow]->point);
	if (command == "Move") {
		this->gMode = "Move";
		this->pMap->CreateGridArea(pGridSelected, 1, this->gMode);
		this->isMenuOpen = false;
	}
	else if (command == "Attack") {
		this->gMode = "Attack";
		this->pMap->CreateGridArea(pGridSelected, 1, this->gMode);
		this->isMenuOpen = false;
		//this->vPlayers[idPlayerNow]->whereAttack.push_back(this->pGridPointed);
	}
	else if (command == "SelectBuild") {
		this->gMode = "SelectBuild";
	}
	else if (command == "SelectCreate") {
		this->gMode = "SelectCreate";
	}
	else if (command.find("B_") != std::string::npos) {
		this->gMode = "Build";
		this->typeToCreate = command.substr(2, -1);
		this->pMap->SetExample(command);
		this->pMap->CreateGridArea(pGridSelected, 1, this->gMode);
		this->isMenuOpen = false;
	}
	else if (command.find("U_") != std::string::npos) {
		this->gMode = "Create";
		this->typeToCreate = command.substr(2, -1);
		this->pMap->SetExample(command);
		this->pMap->CreateGridArea(pGridSelected, 1, this->gMode);
		this->isMenuOpen = false;
	}
	else if (command == "null") {
		this->isMenuOpen = false;
		this->SetToNormalMode();
		this->pButtonAPointed = 0;
	}
	else {
		this->isMenuOpen = false;
		this->SetToNormalMode();
		this->pButtonAPointed = 0;
	}
}

void Action::updateText()
{
	std::stringstream textt;

	textt << "Player " << this->idPlayerNow+1 << " turn";
	this->Playerturn.setString(textt.str());

	//point update
	std::stringstream pointp;

	pointp << "P" << idPlayerNow+1 << " Points : " << this->vPlayers[this->idPlayerNow]->point;
	this->pointPtext.setString(pointp.str());
}

ActionButton* Action::GetButtonAPointed(std::vector<ActionButton*> vButtonA)
{
	std::vector<ActionButton*> gridHovered;
	for (unsigned int i = 0; i < vButtonA.size(); i++) {
			if (vButtonA[i]->isPointed(this->currentMousePos))
			{
				gridHovered.push_back(vButtonA[i]);
			}
	}
	if (gridHovered.size() > 0) {
		for (unsigned int i = 0; i < gridHovered.size() - 1; i++) {
			bool isTemp = 0;
			for (unsigned int j = 0; j < gridHovered.size() - i - 1; j++) {
				float distanceOne = gridHovered[j]->distanceFromMouse(this->currentMousePos);
				float distanceTwo = gridHovered[j + 1]->distanceFromMouse(this->currentMousePos);
				if (distanceOne > distanceTwo) {
					std::swap(gridHovered[j + 1], gridHovered[j]);
					isTemp = 1;
				}
			}
			if (!isTemp) break;
		}
		return gridHovered[0];
	}
	this->pButtonAPointed = 0;
	return 0;
}
