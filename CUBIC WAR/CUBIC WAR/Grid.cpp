#include "Grid.h"

Grid::Grid(int row, int column, sf::Vector2f size)
{
	this->size = size;
	this->column = column;
	this->row = row;
	this->Setup();
}

Grid::~Grid()
{
	for (unsigned int i = 0; i < this->vActionButton.size(); i++) {
		for (unsigned int j = 0; j < this->vActionButton[i].size(); j++) {
			delete this->vActionButton[i][j];
		}
	}
}

void Grid::setActionButtons(int N, std::string type[] , int point[])
{
	std::vector<ActionButton*> vButton;
	for (int i = 0; i < N; i++) {
		vButton.push_back(new ActionButton(type[i], point[i]));
	}
	this->vActionButton.push_back(vButton);
}

void Grid::Setup()
{
	if (!texture.loadFromFile("Textures/Terrain/grass.png")) {
		std::cout << "Error to load Textures/Terrain/grass.png";// +this->imgPath + ".png" << std::endl;
	}

	this->shape.scale(this->size.x / this->texture.getSize().x, this->size.y / this->texture.getSize().y);

	if (this->row % 2 == 0) {
		shape.setPosition(this->column * this->size.x, this->row * 52.f);
	}
	else {
		shape.setPosition((this->column * this->size.x) + this->size.x/2, this->row * 52.f);
	}

	this->centerPos.x = this->shape.getPosition().x + (this->size.x / 2);
	this->centerPos.y = this->shape.getPosition().y + (this->size.y / 2);
}

void Grid::ShowInCreate(sf::Texture texture, sf::RenderTarget* target)
{
	sf::Sprite shape;
	shape.setPosition(this->shape.getPosition());
	shape.setTexture(texture);
	shape.scale(this->size.x / this->texture.getSize().x, this->size.y / this->texture.getSize().y);
	target->draw(shape);
}

void Grid::RenderGrid(sf::RenderTarget *target, int idPlayerNow)
{
	this->shape.setTexture(this->texture);
	target->draw(this->shape);
	if (this->isBuilding) {
		this->RenderHpBar(target, idPlayerNow != this->idPlayerHere);
	}
}

void Grid::RenderUnit(sf::RenderTarget* target, int idPlayerNow)
{
	this->pUnit->Render(target, idPlayerNow);
}

void Grid::RenderHpBar(sf::RenderTarget* target, bool isEnemy)
{
	sf::Vector2f unitPos = this->shape.getPosition();
	this->hpBar.setSize(sf::Vector2f(35.f, 5.f));
	this->hpBar.setOrigin(hpBar.getSize());
	this->hpBar.setPosition(unitPos.x + 47.5f, unitPos.y + 55.f);
	this->hpBar.setFillColor(sf::Color::White);
	target->draw(this->hpBar);
	this->hpBar.setSize(sf::Vector2f(35.f * (this->hp / (float)this->maxhp), 5.f));
	if (isEnemy) {
		this->hpBar.setFillColor(sf::Color::Red);
	}
	else {
		this->hpBar.setFillColor(sf::Color::Green);
	}
	target->draw(this->hpBar);
}

// Grid Action ->

Grid* Grid::CreateBuilding(std::string type, int idPlayer)
{
	this->idPlayerHere = idPlayer;
	this->isBuilding = true;
	this->typeBuilding = type;

	if(type == "B") {
		this->maxhp = this->hp = 50;
		this->atk = 0;
		this->imgPath = "medieval_largeCastle";
	}
	else if (type == "M") {
		this->maxhp = this->hp = 45;
		this->atk = 0;
		this->imgPath = "medieval_training";
		std::string typeActions1[] = { "SelectCreate" };
		int pointAction1[] = {4};
		this->setActionButtons(1, typeActions1, pointAction1);
		std::string typeActions2[] = { "U_Soldier", "U_Archer", "U_Artillery" };
		int pointAction2[] = {4,5,6};

		this->setActionButtons(3, typeActions2, pointAction2);
	}
	else if (type == "A") {
		this->maxhp = this->hp = 45;
		this->atk = 0;
		this->imgPath = "medieval_tower";
		std::string typeActions[] = { "Attack" };
		int pointAction[] = { 3 };
		this->setActionButtons(1, typeActions, pointAction);
	}
	else if (type == "C") {
		this->maxhp = this->hp = 35;
		this->atk = 0;
		this->imgPath = "medieval_canon";
		std::string typeActions[] = { "Attack" };
		int pointAction[] = { 3 };
		this->setActionButtons(1, typeActions, pointAction);
	}

	if (!this->texture.loadFromFile("Textures/Building/" + this->imgPath + ".png")) {
		std::cout << "Error to load Textures/Building/" + this->imgPath + ".png" << std::endl;
	}

	return this;
}

Grid* Grid::AddUnit(std::string type, std::vector<Unit*>& vUnits, int idPlayer)
{
	this->isUnit = true;
	vUnits.push_back(new Unit(type, this->centerPos, idPlayer));
	this->pUnit = vUnits.back();
	if (pUnit->GetType() == "Engineer") {
		std::string typeActions1[] = { "Move", "SelectBuild" };
		int pointAction1[] = { 1, 5 };
		this->setActionButtons(2, typeActions1, pointAction1);
		std::string typeActions2[] = { "B_M", "B_A", "B_C" };
		int pointAction2[] = { 5,8,10 };
		this->setActionButtons(3, typeActions2, pointAction2);
	}
	else if (pUnit->GetType() == "Soldier") {
		std::string typeActions[] = { "Move", "Attack" };
		int pointAction[] = { 1, 1 };
		this->setActionButtons(2, typeActions, pointAction);
	}
	else if (pUnit->GetType() == "Archer") {
		std::string typeActions[] = { "Move", "Attack" };
		int pointAction[] = { 1, 2 };
		this->setActionButtons(2, typeActions, pointAction);
	}
	else if (pUnit->GetType() == "Artillery") {
		std::string typeActions[] = { "Move", "Attack" };
		int pointAction[] = { 4, 2 };
		this->setActionButtons(2, typeActions, pointAction);
	}
	return this;
}

Grid* Grid::AddUnit(Unit* pNewUnit)
{
	this->pUnit = pNewUnit;
	this->pUnit->Move(this->centerPos);
	if (pUnit->GetType() == "Engineer") {
		std::string typeActions1[] = { "Move", "SelectBuild" };
		int pointAction1[] = { 1, 5 };
		this->setActionButtons(2, typeActions1,pointAction1);
		std::string typeActions2[] = { "B_M", "B_A", "B_C" };
		int pointAction2[] = { 5,8,10 };
		this->setActionButtons(3, typeActions2,pointAction2);
	}
	else if(pUnit->GetType() == "Soldier") {
		std::string typeActions[] = { "Move", "Attack" };
		int pointAction[] = { 1, 1 };
		this->setActionButtons(2, typeActions,pointAction);
	}
	else if (pUnit->GetType() == "Archer") {
		std::string typeActions[] = { "Move", "Attack" };
		int pointAction[] = { 1, 2 };
		this->setActionButtons(2, typeActions, pointAction);
	}
	else if (pUnit->GetType() == "Artillery") {
		std::string typeActions[] = { "Move", "Attack" };
		int pointAction[] = { 4, 2 };
		this->setActionButtons(2, typeActions, pointAction);
	}
	this->isUnit = true;
	return this;
}

Unit* Grid::GetUnit()
{
	return this->pUnit;
}

bool Grid::BeAttack(int dmg)
{
	if (this->isUnit) {
		if (this->pUnit->BeAttack(dmg)) {
			this->pUnit = 0;
			this->isUnit = false;
		}
	}
	else if (this->isBuilding) {
		this->hp -= dmg;
		if (this->typeBuilding == "B") {
			if (this->hp <= 0) {
				return true;
			}
		}	
	}
	return false;
}

int Grid::Attack()
{
	if (this->isUnit) {
		return this->pUnit->GetAttackPoint();
	}
	return this->atk;
}

void Grid::ClearUnit()
{
	this->isUnit = false;
	this->pUnit = 0;
	
	for (unsigned int i = 0; i < this->vActionButton.size(); i++) {
		for (unsigned int j = 0; j < this->vActionButton[i].size(); j++) {
			delete this->vActionButton[i][j];
		}
	}
	vActionButton.clear();
}

void Grid::ClearBuilding()
{
	this->isBuilding = false;

	for (unsigned int i = 0; i < this->vActionButton.size(); i++) {
		for (unsigned int j = 0; j < this->vActionButton[i].size(); j++) {
			delete this->vActionButton[i][j];
		}
	}
	vActionButton.clear();
}

bool Grid::isPointed(sf::Vector2i MousePos)
{
	if (this->shape.getGlobalBounds().contains(float(MousePos.x), float(MousePos.y))) return true;
	return false;
}

float Grid::distanceFromMouse(sf::Vector2i MousePos)
{
	float x = float(pow(this->centerPos.x - MousePos.x, 2));
	float y = float(pow(this->centerPos.y - MousePos.y, 2));

	return sqrt(x + y);
}

void Grid::SetEnabled(bool x)
{
	this->enabled = x;
}

sf::Vector2f Grid::GetPosition()
{
	return this->shape.getPosition();
}

sf::Vector2i Grid::GetRC()
{
	int q = this->column - (this->row - (this->row & 1)) / 2;
	int r = this->row;
	return sf::Vector2i(r, q);
}

sf::Vector2f Grid::GetCenterPoint()
{
	return this->centerPos;
}

void Grid::UpdatePlayerVision(int idPlayer)
{
	this->idPlayersVision[idPlayer] = true;
}

bool Grid::GetPlayerVision(int idPlayer)
{
	return this->idPlayersVision[idPlayer];
}

bool Grid::isEnabled()
{
	return this->enabled;
}

bool Grid::isMyBuilding(int idPlayer)
{
	if (this->idPlayerHere == idPlayer) {
		return true;
	}return false;
}


