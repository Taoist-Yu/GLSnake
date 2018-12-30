#pragma once

//全局关卡信息
class GameData
{
public:
	static int difficulty;
	static int currentLevel;
	static int levelUpper;

public:
	static void Load();
	static void Save();


};

