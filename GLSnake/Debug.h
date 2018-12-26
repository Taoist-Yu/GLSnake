#pragma once

#include<fstream>
#include<iostream>
#include<string>

class Debug
{
	static std::ofstream log;
	static std::ofstream warning;
	static std::ofstream error;

public:
	static void Log(std::string str);
	static void Warning(std::string str);
	static void Error(std::string str);
};

