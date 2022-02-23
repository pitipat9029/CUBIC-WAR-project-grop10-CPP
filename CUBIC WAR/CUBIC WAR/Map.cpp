#include "Map.h"

void Map::InitMap()
{
	std::vector<Grid> gridRow;
	for (int r = -1; r < this->maxRow; r += 1) {
		gridRow.clear();
		for (int c = -1; c < this->maxColumn; c += 1) {
			Grid grid(r, c, this->gridSize);
			if (!((c < 0 || (c > this->maxColumn - 2 && (r % 2) != 0)) || (r < 0 || r >= this->maxRow))) {
				grid.SetEnabled(true);
			} else {
				grid.SetEnabled(false);
			}
			gridRow.push_back(grid);
		}
		this->vGrids.push_back(gridRow);
	}
}

Map::Map(sf::RenderWindow* pWindow, sf::Vector2i* currentMousePos, int* pIdPlayerNow)
{
	this->pWindow = pWindow;
	this->pIdPlayerNow = pIdPlayerNow;
	this->currentMousePos = currentMousePos;
	std::cout << "Map was create" << std::endl;

	// Set map properties
	gridSize.x = 60.f;
	gridSize.y = 70.f;

	maxRow = 11;
	maxColumn = (900 / gridSize.x);

	InitMap();
}

Map::~Map()
{
	for (unsigned int i = 0; i < this->vUnits.size(); i++) {
		delete this->vUnits[i];
	}
	std::cout << "Map was delect" << std::endl;
}

void Map::RenderMap()
{
	for (unsigned int i = 0; i < this->vGrids.size(); i++) {
		for (unsigned int j = 0; j < this->vGrids[i].size(); j++) {
			if (vGrids[i][j].GetPlayerVision(*this->pIdPlayerNow)) {
				vGrids[i][j].RenderGrid(this->pWindow, *this->pIdPlayerNow);
			}
		}
	}
}

void Map::RenderUnits()
{
	for (unsigned int i = 0; i < this->vGrids.size(); i++) {
		for (unsigned int j = 0; j < this->vGrids[i].size(); j++) {
			if (vGrids[i][j].GetPlayerVision(*this->pIdPlayerNow)) {
				if (vGrids[i][j].isUnit)
				{
					vGrids[i][j].RenderUnit(this->pWindow, *this->pIdPlayerNow);
				}
			}
		}
	}
}

void Map::UpdatePlayerVision(Grid* pGrid, int radius2, int idPlayer)
{
	if (pGrid->isUnit) {
		if (pGrid->GetUnit()->GetType() == "Soldier") {
			int radius = 2;
			for (int q = pGrid->GetRC().y - radius; q <= pGrid->GetRC().y + radius; q++) {
				for (int r = pGrid->GetRC().x - radius; r <= pGrid->GetRC().x + radius; r++) {
					if (abs(-(q - pGrid->GetRC().y) - (r - pGrid->GetRC().x)) <= radius) {
						if ((-(q - pGrid->GetRC().y) - (r - pGrid->GetRC().x)) == 0 || (q - pGrid->GetRC().y) == 0 || (r - pGrid->GetRC().x) == 0) {
							int col = q + (r - (r & 1)) / 2;
							int row = r;
							if (row >= 0 && row < this->maxRow && col >= 0 && col < this->maxColumn) {
								this->vGrids[row + 1][col + 1].UpdatePlayerVision(idPlayer);
							}
						}
					}
				}
			}
		}
		else if (pGrid->GetUnit()->GetType() == "Archer") {
			int radius = 2;
			for (int q = pGrid->GetRC().y - radius; q <= pGrid->GetRC().y + radius; q++) {
				for (int r = pGrid->GetRC().x - radius; r <= pGrid->GetRC().x + radius; r++) {
					if (abs(-(q - pGrid->GetRC().y) - (r - pGrid->GetRC().x)) <= radius) {
						int col = q + (r - (r & 1)) / 2;
						int row = r;
						if (row >= 0 && row < this->maxRow && col >= 0 && col < this->maxColumn) {
							this->vGrids[row + 1][col + 1].UpdatePlayerVision(idPlayer);
						}
					}
				}
			}
		}
		else {
			int radius = 1;
			for (int q = pGrid->GetRC().y - radius; q <= pGrid->GetRC().y + radius; q++) {
				for (int r = pGrid->GetRC().x - radius; r <= pGrid->GetRC().x + radius; r++) {
					if (abs(-(q - pGrid->GetRC().y) - (r - pGrid->GetRC().x)) <= radius) {
						int col = q + (r - (r & 1)) / 2;
						int row = r;
						if (row >= 0 && row < this->maxRow && col >= 0 && col < this->maxColumn) {
							this->vGrids[row + 1][col + 1].UpdatePlayerVision(idPlayer);
						}
					}
				}
			}
		}
	}
	else if (pGrid->isBuilding) {
		if (pGrid->typeBuilding == "A") {
			int radius = 2;
			for (int q = pGrid->GetRC().y - radius; q <= pGrid->GetRC().y + radius; q++) {
				for (int r = pGrid->GetRC().x - radius; r <= pGrid->GetRC().x + radius; r++) {
					if (abs(-(q - pGrid->GetRC().y) - (r - pGrid->GetRC().x)) <= radius) {
						int col = q + (r - (r & 1)) / 2;
						int row = r;
						if (row >= 0 && row < this->maxRow && col >= 0 && col < this->maxColumn) {
							this->vGrids[row + 1][col + 1].UpdatePlayerVision(idPlayer);
						}
					}
				}
			}
		}
		else if (pGrid->typeBuilding == "C") {
			int radius = 3;
			for (int q = pGrid->GetRC().y - radius; q <= pGrid->GetRC().y + radius; q++) {
				for (int r = pGrid->GetRC().x - radius; r <= pGrid->GetRC().x + radius; r++) {
					if (abs(-(q - pGrid->GetRC().y) - (r - pGrid->GetRC().x)) <= radius) {
						int col = q + (r - (r & 1)) / 2;
						int row = r;
						if (row >= 0 && row < this->maxRow && col >= 0 && col < this->maxColumn) {
							this->vGrids[row + 1][col + 1].UpdatePlayerVision(idPlayer);
						}
					}
				}
			}
		}
		else {
			int radius = 1;
			for (int q = pGrid->GetRC().y - radius; q <= pGrid->GetRC().y + radius; q++) {
				for (int r = pGrid->GetRC().x - radius; r <= pGrid->GetRC().x + radius; r++) {
					if (abs(-(q - pGrid->GetRC().y) - (r - pGrid->GetRC().x)) <= radius) {
						int col = q + (r - (r & 1)) / 2;
						int row = r;
						if (row >= 0 && row < this->maxRow && col >= 0 && col < this->maxColumn) {
							this->vGrids[row + 1][col + 1].UpdatePlayerVision(idPlayer);
						}
					}
				}
			}
		}
	}
	else {
		int radius = 1;
		for (int q = pGrid->GetRC().y - radius; q <= pGrid->GetRC().y + radius; q++) {
			for (int r = pGrid->GetRC().x - radius; r <= pGrid->GetRC().x + radius; r++) {
				if (abs(-(q - pGrid->GetRC().y) - (r - pGrid->GetRC().x)) <= radius) {
					int col = q + (r - (r & 1)) / 2;
					int row = r;
					if (row >= 0 && row < this->maxRow && col >= 0 && col < this->maxColumn) {
						this->vGrids[row + 1][col + 1].UpdatePlayerVision(idPlayer);
					}
				}
			}
		}
	}
}

Grid* Map::UpdatePointedGrid()
{
	std::vector<Grid*> gridHovered;
	for (unsigned int i = 0; i < this->vGrids.size(); i++) {
		for (unsigned int j = 0; j < this->vGrids[i].size(); j++) {
			if (this->vGrids[i][j].GetPlayerVision(*this->pIdPlayerNow) && \
				this->vGrids[i][j].isPointed(*this->currentMousePos))
			{
				gridHovered.push_back(&this->vGrids[i][j]);
			}
		}
	}
	if (gridHovered.size() > 0) {
		for (unsigned int i = 0; i < gridHovered.size() - 1; i++) {
			bool isTemp = 0;
			for (unsigned int j = 0; j < gridHovered.size() - i - 1; j++) {
				float distanceOne = gridHovered[j]->distanceFromMouse(*this->currentMousePos);
				float distanceTwo = gridHovered[j + 1]->distanceFromMouse(*this->currentMousePos);
				if (distanceOne > distanceTwo) {
					std::swap(gridHovered[j + 1], gridHovered[j]);
					isTemp = 1;
				}
			}
			if (!isTemp) break;
		}
		if (gridHovered[0]->isEnabled()) {
			this->pPointedGrid = gridHovered[0];
			return gridHovered[0];
		}
	}
	this->pPointedGrid = 0;
	return 0;
}

void Map::ShowGridHighlight(std::string gMode)
{
	if (gMode == "Move") {
		this->HighlightGridPointed(sf::Color(0, 255, 0, 100), sf::Color::Green);
		this->HighlightGridArea(sf::Color(0, 255, 0, 80), sf::Color(0, 0, 0, 0));
	}
	else if (gMode == "Attack") {
		this->HighlightGridPointed(sf::Color(255, 0, 0, 100), sf::Color::Red);
		this->HighlightGridArea(sf::Color(255, 0, 0, 120), sf::Color(0, 0, 0, 0));
	}
	else if (gMode == "Build" || gMode == "Create") {
		if (this->pPointedGrid != 0) {
			this->pPointedGrid->ShowInCreate(this->textureExample, this->pWindow);
		}
		this->HighlightGridArea(sf::Color(255, 255, 255, 60), sf::Color(0, 0, 0, 0));
		this->HighlightGridPointed(sf::Color(0, 0, 0, 0), sf::Color::White);
	}
	else {
		this->HighlightGridPointed(sf::Color(0, 0, 0, 0), sf::Color::White);
	}
}

void Map::SetGridAllEnable(bool b)
{
	for (unsigned int i = 0; i < this->vGrids.size(); i++) {
		for (unsigned int j = 0; j < this->vGrids[i].size(); j++) {
			if (!((j <= 0 || (j > this->maxColumn-1 && (i % 2) == 0)) || (i <= 0 || i >= this->maxRow+1))) {
				vGrids[i][j].SetEnabled(b);
			}
		}
	}
}

void Map::SetGridEdgeDisable()
{
	for (unsigned int i = 0; i < this->vGrids.size(); i++) {
		for (unsigned int j = 0; j < this->vGrids[i].size(); j++) {
			if ((j <= 0 || (j > this->maxColumn - 1 && (i % 2) == 0)) || (i <= 0 || i >= this->maxRow + 1)) {
				vGrids[i][j].SetEnabled(false);
			}
		}
	}
}

void Map::SetExample(std::string type)
{
	std::string imgPath;

	if (type == "B_M") {
		imgPath = "medieval_training";
	}
	else if (type == "B_A") {
		
		imgPath = "medieval_tower";
	}
	else if (type == "B_C") {
		imgPath = "medieval_canon";
	}
	else if (type == "U_Soldier") {
		imgPath = "Soldier";
	}
	else if (type == "U_Archer") {
		imgPath = "Archer";
	}
	else if (type == "U_Artillery") {
		imgPath = "Artillery";
	}
	if (type.find("U_") != std::string::npos) {
		if (!this->textureExample.loadFromFile("Textures/Unit/" + imgPath + ".png")) {
			std::cout << "Error to load Textures/Unit/" + imgPath + ".png" << std::endl;
		}
	}
	else if(type.find("B_") != std::string::npos)
	{
		if (!this->textureExample.loadFromFile("Textures/Building/" + imgPath + ".png")) {
			std::cout << "Error to load Textures/Building/" + imgPath + ".png" << std::endl;
		}
	}
}

void Map::CreateGridArea(Grid* pGridCenter, int radius1, std::string gMode)
{
	this->pPointedGrid = 0;
	this->SetGridAllEnable(false);

	if (gMode == "Attack") {
		if (pGridCenter->isUnit) {
			if (pGridCenter->GetUnit()->GetType() == "Archer") {
				int radius = 2;
				for (int q = pGridCenter->GetRC().y - radius; q <= pGridCenter->GetRC().y + radius; q++) {
					for (int r = pGridCenter->GetRC().x - radius; r <= pGridCenter->GetRC().x + radius; r++) {
						if (abs(-(q - pGridCenter->GetRC().y) - (r - pGridCenter->GetRC().x)) <= radius) {
							int col = q + (r - (r & 1)) / 2;
							int row = r;
							if (row >= 0 && row < this->maxRow && col >= 0 && col < this->maxColumn) {
								Grid* pGrid = &this->vGrids[row + 1][col + 1];
								if (pGrid != pGridCenter) {
									pGrid->SetEnabled(true);
								}
							}
						}
					}
				}
			}
			else {
				int radius = 1;
				for (int q = pGridCenter->GetRC().y - radius; q <= pGridCenter->GetRC().y + radius; q++) {
					for (int r = pGridCenter->GetRC().x - radius; r <= pGridCenter->GetRC().x + radius; r++) {
						if (abs(-(q - pGridCenter->GetRC().y) - (r - pGridCenter->GetRC().x)) <= radius) {
							int col = q + (r - (r & 1)) / 2;
							int row = r;
							if (row >= 0 && row < this->maxRow && col >= 0 && col < this->maxColumn) {
								Grid* pGrid = &this->vGrids[row + 1][col + 1];
								if (pGrid != pGridCenter) {
									pGrid->SetEnabled(true);
								}
							}
						}
					}
				}
			}
		}
		else if (pGridCenter->isBuilding) {
			if (pGridCenter->typeBuilding == "C") {
				int radius = 3;
				for (int q = pGridCenter->GetRC().y - radius; q <= pGridCenter->GetRC().y + radius; q++) {
					for (int r = pGridCenter->GetRC().x - radius; r <= pGridCenter->GetRC().x + radius; r++) {
						if (abs(-(q - pGridCenter->GetRC().y) - (r - pGridCenter->GetRC().x)) <= radius) {
							if (!(abs(-(q - pGridCenter->GetRC().y) - (r - pGridCenter->GetRC().x)) + abs(q - pGridCenter->GetRC().y) + abs(r - pGridCenter->GetRC().x) == 2)) {
								int col = q + (r - (r & 1)) / 2;
								int row = r;
								if (row >= 0 && row < this->maxRow && col >= 0 && col < this->maxColumn) {
									Grid* pGrid = &this->vGrids[row + 1][col + 1];
									if (pGrid != pGridCenter) {
										pGrid->SetEnabled(true);
									}
								}
							}
						}
					}
				}
			}
			else {
				int radius = 1;
				for (int q = pGridCenter->GetRC().y - radius; q <= pGridCenter->GetRC().y + radius; q++) {
					for (int r = pGridCenter->GetRC().x - radius; r <= pGridCenter->GetRC().x + radius; r++) {
						if (abs(-(q - pGridCenter->GetRC().y) - (r - pGridCenter->GetRC().x)) <= radius) {
							int col = q + (r - (r & 1)) / 2;
							int row = r;
							if (row >= 0 && row < this->maxRow && col >= 0 && col < this->maxColumn) {
								Grid* pGrid = &this->vGrids[row + 1][col + 1];
								if (pGrid != pGridCenter) {
									pGrid->SetEnabled(true);
								}
							}
						}
					}
				}
			}
		}
		else {
			int radius = 1;
			for (int q = pGridCenter->GetRC().y - radius; q <= pGridCenter->GetRC().y + radius; q++) {
				for (int r = pGridCenter->GetRC().x - radius; r <= pGridCenter->GetRC().x + radius; r++) {
					if (abs(-(q - pGridCenter->GetRC().y) - (r - pGridCenter->GetRC().x)) <= radius) {
						int col = q + (r - (r & 1)) / 2;
						int row = r;
						if (row >= 0 && row < this->maxRow && col >= 0 && col < this->maxColumn) {
							Grid* pGrid = &this->vGrids[row + 1][col + 1];
							if (pGrid != pGridCenter) {
								pGrid->SetEnabled(true);
							}
						}
					}
				}
			}
		}
	}
	else if (gMode == "Move") {
		if (pGridCenter->GetUnit()->GetType() == "Soldier") {
			int radius = 2;
			for (int q = pGridCenter->GetRC().y - radius; q <= pGridCenter->GetRC().y + radius; q++) {
				for (int r = pGridCenter->GetRC().x - radius; r <= pGridCenter->GetRC().x + radius; r++) {
					if (abs(-(q - pGridCenter->GetRC().y) - (r - pGridCenter->GetRC().x)) <= radius) {
						if ((-(q - pGridCenter->GetRC().y) - (r - pGridCenter->GetRC().x)) == 0 || (q - pGridCenter->GetRC().y) == 0 || (r - pGridCenter->GetRC().x) == 0) {
							int col = q + (r - (r & 1)) / 2;
							int row = r;
							Grid* pGrid = &this->vGrids[row + 1][col + 1];
							if (pGrid != pGridCenter && !pGrid->isBuilding && !pGrid->isUnit) {
								pGrid->SetEnabled(true);
							}
						}
					}
				}
			}
		}
		else if (pGridCenter->GetUnit()->GetType() == "Archer") {
			int radius = 1;
			for (int q = pGridCenter->GetRC().y - radius; q <= pGridCenter->GetRC().y + radius; q++) {
				for (int r = pGridCenter->GetRC().x - radius; r <= pGridCenter->GetRC().x + radius; r++) {
					if (abs(-(q - pGridCenter->GetRC().y) - (r - pGridCenter->GetRC().x)) <= radius) {
						int col = q + (r - (r & 1)) / 2;
						int row = r;
						Grid* pGrid = &this->vGrids[row + 1][col + 1];
						if (pGrid != pGridCenter && !pGrid->isBuilding && !pGrid->isUnit) {
							pGrid->SetEnabled(true);
						}
					}
				}
			}
		}
		else {
			int radius = 1;
			for (int q = pGridCenter->GetRC().y - radius; q <= pGridCenter->GetRC().y + radius; q++) {
				for (int r = pGridCenter->GetRC().x - radius; r <= pGridCenter->GetRC().x + radius; r++) {
					if (abs(-(q - pGridCenter->GetRC().y) - (r - pGridCenter->GetRC().x)) <= radius) {
						int col = q + (r - (r & 1)) / 2;
						int row = r;
						Grid* pGrid = &this->vGrids[row + 1][col + 1];
						if (pGrid != pGridCenter && !pGrid->isBuilding && !pGrid->isUnit) {
							pGrid->SetEnabled(true);
						}
					}
				}
			}
		}
	}
	else {
		int radius = 1;
		for (int q = pGridCenter->GetRC().y - radius; q <= pGridCenter->GetRC().y + radius; q++) {
			for (int r = pGridCenter->GetRC().x - radius; r <= pGridCenter->GetRC().x + radius; r++) {
				if (abs(-(q - pGridCenter->GetRC().y) - (r - pGridCenter->GetRC().x)) <= radius) {
					int col = q + (r - (r & 1)) / 2;
					int row = r;
					if (row >= 0 && row < this->maxRow && col >= 0 && col < this->maxColumn) {
						Grid* pGrid = &this->vGrids[row + 1][col + 1];
						if (pGrid != pGridCenter && !pGrid->isBuilding && !pGrid->isUnit) {
							pGrid->SetEnabled(true);
						}
					}
				}
			}
		}
	}
	this->SetGridEdgeDisable();
}

void Map::HighlightGridArea(sf::Color cFill, sf::Color cOutline)
{
	sf::CircleShape rect(35, 6);
	rect.setFillColor(cFill);
	for (unsigned int i = 0; i < this->vGrids.size(); i++) {
		for (unsigned int j = 0; j < this->vGrids[i].size(); j++) {
			if (this->vGrids[i][j].isEnabled())
			{
				rect.setPosition(this->vGrids[i][j].GetPosition().x - 5, this->vGrids[i][j].GetPosition().y);
				this->pWindow->draw(rect);
			}
		}
	}
}

void Map::HighlightGridPointed(sf::Color cFill, sf::Color cOutline)
{
	if (this->pPointedGrid != 0) {
		sf::CircleShape rect(35, 6);
		rect.setPosition(this->pPointedGrid->GetPosition().x - 5, this->pPointedGrid->GetPosition().y);
		rect.setFillColor(cFill);
		rect.setOutlineColor(cOutline);
		rect.setOutlineThickness(-2.f);
		this->pWindow->draw(rect);
	}
}



