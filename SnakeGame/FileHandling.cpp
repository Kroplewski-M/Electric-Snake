#include "FileHandling.h"

FileHandling::FileHandling(std::string filename)
	:fileName(filename)
{
	CreateFile();
	SetScore();
}

FileHandling::~FileHandling()
{

}

void FileHandling::CreateFile()
{
	fileName = fileName + ".txt";

	//CREATE FILE
	file.open(fileName, std::ofstream::in | std::ofstream::out);
	if (file.is_open())
	{
		printf("\nFile Open\n");
	}
	else
	{
		printf("\nFile not created");
	}
	file.close();
}

void FileHandling::SetScore()
{
	readFile.open(fileName);
	if (readFile.is_open())
	{
		readFile >> score;
	}
	else
		printf( "file cant open 1");
	readFile.close();
}

void FileHandling::OverRideScore(int score)
{
	file.open(fileName, std::ofstream::in | std::ofstream::out | std::ofstream::trunc);
	if (file.is_open())
	{
		file << score;
	}
	else
	{
		printf("file cant open 2");
	}
	file.close();
}

int FileHandling::GetScore()
{
	return score;
}
