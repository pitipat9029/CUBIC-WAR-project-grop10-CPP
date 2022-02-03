#include "Building.h"

Building::Building(int type)
{
	this->type = type;
	switch (type)
	{
	case 0:
		this->maxLifePoint = this->lifePoint = 50;
		this->damage = 0;
		break;
	case 1:
		this->maxLifePoint = this->lifePoint = 45;
		this->damage = 0;
		break;
	case 2:
		this->maxLifePoint = this->lifePoint = 45;
		this->damage = 0;
		break;
	case 3:
		this->maxLifePoint = this->lifePoint = 35;
		this->damage = 0;
		break;
	case 4:
		this->maxLifePoint = this->lifePoint = 50;
		this->damage = 0;
		break;
	default:
		break;
	}
}

Building::~Building()
{
}


