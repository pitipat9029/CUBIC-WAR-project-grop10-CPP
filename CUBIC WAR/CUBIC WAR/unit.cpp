#include "Unit.h"

Unit::Unit(std::string type, sf::Vector2f centerPos, int idPlayer)
{
	std::cout << "Unit " << type << " was create." << std::endl;

	this->idPlayer = idPlayer;

	this->type = type;
	if (this->type == "Engineer") {
		this->imgPath = "Engineer";
		this->maxhp = this->hp = 30;
	}
	else if (this->type == "Soldier") {
		this->imgPath = "Soldier";
		this->maxhp = this->hp = 25;
		this->atk = 10;
	}
	else if (this->type == "Archer") {
		this->imgPath = "Archer";
		this->maxhp = this->hp = 15;
		this->atk = 10;
	}
	else if (this->type == "Artillery") {
		this->imgPath = "Artillery";
		this->maxhp = this->hp = 20;
		this->atk = 10;
	}

	if (!this->texture.loadFromFile("Textures/Unit/" + this->imgPath + ".png")) {
		std::cout << "Error to load Textures/Unit/" + this->imgPath + ".png" << std::endl;
	}

	this->shape.setOrigin(this->texture.getSize().x / 2, this->texture.getSize().y / 2);
	this->shape.setPosition(centerPos);
	//this->shape.setTextureRect(sf::IntRect(60.f, 0, -60.f, 70.f));
	this->SetSize(-60.f, 70.f);
}

Unit::~Unit()
{
	std::cout << "Unit " << this->type << " was delete." << std::endl;
}

void Unit::Render(sf::RenderTarget* target, int idPlayerNow)
{
	this->shape.setTexture(this->texture);
	target->draw(this->shape);
	if (idPlayerNow == this->idPlayer) this->RenderHpBar(target, false);
	else this->RenderHpBar(target, true);
}

void Unit::RenderHpBar(sf::RenderTarget* target, bool isEnemy)
{
	sf::Vector2f unitPos = this->shape.getPosition();
	this->hpBar.setSize(sf::Vector2f(-5.f, -35.f));
	this->hpBar.setOrigin(hpBar.getSize());
	this->hpBar.setPosition(unitPos.x + 25.f, unitPos.y -17.5f);
	this->hpBar.setFillColor(sf::Color::White);
	target->draw(this->hpBar);
	this->hpBar.setSize(sf::Vector2f(-5.f, -1*(35.f*(this->hp/(float)this->maxhp))));
	if (isEnemy) {
		this->hpBar.setFillColor(sf::Color::Red);
	} else {
		this->hpBar.setFillColor(sf::Color::Green);
	}
	target->draw(this->hpBar);
}

int Unit::GetAttackPoint()
{
	return this->atk;
}

bool Unit::BeAttack(int dmg)
{
	this->hp -= dmg;
	if (hp <= 0) {
		return true;
	}return false;
}

void Unit::SetSize(float x, float y)
{
	this->shape.scale(x / this->texture.getSize().x, y / this->texture.getSize().y);
}

void Unit::Move(sf::Vector2f centerPos)
{
	this->shape.setPosition(centerPos);
}

void Unit::destroy()
{

}

bool Unit::isMyUnit(int idPlayer)
{
	if (this->idPlayer == idPlayer) {
		return true;
	}return false;
}

std::string Unit::GetType()
{
	return this->type;
}


