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

Map::Map(sf::RenderWindow* pWindow)
{
	this->pWindow = pWindow;
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

void Map::Render(sf::RenderTarget* target, int idPlayer)
{
	for (unsigned int i = 0; i < this->vGrids.size(); i++) {
		for (unsigned int j = 0; j < this->vGrids[i].size(); j++) {
			if (vGrids[i][j].GetPlayerVision(idPlayer)) {
				vGrids[i][j].Render(target);
			}
		}
	}
}

void Map::UpdatePlayerVision(Grid* pGrid, int radius, int idPlayer)
{
	for (int q = pGrid->GetRC().y - radius; q <= pGrid->GetRC().y + radius; q++) {
		for (int r = pGrid->GetRC().x - radius; r <= pGrid->GetRC().x + radius; r++) {
			if (abs(-(q - pGrid->GetRC().y) - (r - pGrid->GetRC().x)) <= radius) {
				int col = q + (r - (r & 1)) / 2;
				int row = r;
				if (row >= 0 && row < 11 && col >= 0 && col < 15) {
					this->vGrids[row + 1][col + 1].UpdatePlayerVision(idPlayer);
				}
			}
		}
	}
}

void Map::ShowGridHighlight(Grid* pGridPointed, std::string gMode)
{
	if (gMode == "Move") {
		this->HighlightGridPointed(pGridPointed, sf::Color(0, 255, 0, 100), sf::Color::Green);
		this->HighlightGridArea(sf::Color(0, 255, 0, 80), sf::Color(0, 0, 0, 0));
	}
	else {
		this->HighlightGridPointed(pGridPointed, sf::Color(0, 0, 0, 0), sf::Color::White);
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

void Map::CreateGridArea(Grid* pGridCenter, int radius)
{
	this->SetGridAllEnable(false);
	for (int q = pGridCenter->GetRC().y - radius; q <= pGridCenter->GetRC().y + radius; q++) {
		for (int r = pGridCenter->GetRC().x - radius; r <= pGridCenter->GetRC().x + radius; r++) {
			if (abs(-(q - pGridCenter->GetRC().y) - (r - pGridCenter->GetRC().x)) <= radius) {
				int col = q + (r - (r & 1)) / 2;
				int row = r;
				if (row >= 0 && row < 11 && col >= 0 && col < 15) {
					Grid* pGrid = &this->vGrids[row + 1][col + 1];
					if (pGrid != pGridCenter && !pGrid->isBuilding && !pGrid->isUnit) {
						pGrid->SetEnabled(true);
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

void Map::HighlightGridPointed(Grid* pGridPointed,sf::Color cFill, sf::Color cOutline)
{
	if (pGridPointed != 0) {
		sf::CircleShape rect(35, 6);
		rect.setPosition(pGridPointed->GetPosition().x - 5, pGridPointed->GetPosition().y);
		rect.setFillColor(cFill);
		rect.setOutlineColor(cOutline);
		rect.setOutlineThickness(-1.5f);
		this->pWindow->draw(rect);
	}
}



