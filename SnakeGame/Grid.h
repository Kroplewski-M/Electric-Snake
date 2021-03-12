#pragma once
#include <SFML\Graphics.hpp>



class Grid
{
public:
	Grid(sf::Vector2f TopLeftPoint, sf::Vector2f BottomRightPoint, sf::Vector2f GridSegmentSize);
	~Grid();
	void SetGrid();
	std::vector<sf::RectangleShape> GetGrid();
private:
	sf::Vector2f TopLeftGridPoint;
	sf::Vector2f BottomRightGridPoint;
	sf::Vector2f GridSegmentSize;
	sf::RectangleShape GridSegment;
	std::vector<sf::RectangleShape>Grids;

};

