#include "Grid.h"

Grid::Grid(sf::Vector2f TopLeftPoint, sf::Vector2f BottomRightPoint, sf::Vector2f GridSegmentsize)
	:TopLeftGridPoint(TopLeftPoint), BottomRightGridPoint(BottomRightPoint), GridSegmentSize(GridSegmentsize)
{
	//SETS THE GRID SEGMENT SIZES, COLOR AND MORE
	GridSegment.setSize(GridSegmentSize);
	GridSegment.setFillColor(sf::Color(0,0,0,200));
	GridSegment.setOutlineThickness(1);
	GridSegment.setOutlineColor(sf::Color(255, 255, 255, 50));
	SetGrid();
}

Grid::~Grid()
{

}

void Grid::SetGrid()
{
	//SETS THE LOCATION OFF ALL GRID SEGMENTS
	for (int i = TopLeftGridPoint.y; i < BottomRightGridPoint.y; i += GridSegmentSize.y)
	{
		for (int j = TopLeftGridPoint.x; j < BottomRightGridPoint.x; j += GridSegmentSize.x)
		{
			GridSegment.setPosition({ float(j),float(i) });
			Grids.push_back(GridSegment);
		}
	}
}

std::vector<sf::RectangleShape> Grid::GetGrid()
{
	return Grids;
}
