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

void Grid::Render(sf::RenderTarget *target)
{
	this->shape.setTexture(this->texture);
	target->draw(this->shape);
}

// Grid Action ->

Grid* Grid::CreateBuilding(std::string type, int idPlayer)
{
	this->idPlayerHere = idPlayer;
	this->isBuilding = true;
	this->typeBuilding = type;

	if(type == "B") {
		this->maxLifePoint = this->lifePoint = 50;
		this->damage = 0;
		this->imgPath = "medieval_largeCastle";
	}
	else if (type == "M") {
		this->maxLifePoint = this->lifePoint = 45;
		this->damage = 0;
		this->imgPath = "medieval_training";
	}
	else if (type == "A") {
		this->maxLifePoint = this->lifePoint = 45;
		this->damage = 0;
		this->imgPath = "medieval_tower";
	}
	else if (type == "C") {
		this->maxLifePoint = this->lifePoint = 35;
		this->damage = 0;
		this->imgPath = "medieval_canon";
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
	return this;
}

Grid* Grid::AddUnit(Unit* pNewUnit)
{
	this->pUnit = pNewUnit;
	this->pUnit->Move(this->centerPos);
	this->isUnit = true;
	return this;
}

Unit* Grid::GetUnit()
{
	return this->pUnit;
}

void Grid::ClearUnit()
{
	this->isUnit = false;
	this->pUnit = 0;
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


