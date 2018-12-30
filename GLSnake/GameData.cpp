#include "GameData.h"
#include<iostream>
#include<fstream>


int GameData::difficulty = 0;
int GameData::currentLevel = 1;
int GameData::levelUpper = 1;

void GameData::Load()
{
	std::ifstream fin("GameData.data");
	fin >> difficulty >> currentLevel >> levelUpper;
	fin.close();
}

void GameData::Save()
{
	std::ofstream fout("GameData.data");
	fout << difficulty << std::endl;
	fout << currentLevel << std::endl;
	fout << levelUpper << std::endl;
	fout.close();
}
