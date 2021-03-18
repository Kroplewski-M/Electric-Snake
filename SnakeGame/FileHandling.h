#pragma once
#include <iostream>
#include <fstream>

class FileHandling
{
public:
	FileHandling(std::string filename);
	~FileHandling();
	void CreateFile();
	void OverRideScore(int score);
	int GetScore();
private:
	void SetScore();
	std::string fileName;
	std::ofstream file;
	std::ifstream readFile;
	int score = 0;
};

