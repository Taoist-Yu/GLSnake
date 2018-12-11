#pragma once
#include "Debug.h"

#include<fstream>
#include<iostream>
#include<string>

namespace Debug
{
	void Log(std::string str)
	{
		std::ofstream log("Log.log");
		log << str << std::endl;
		log.close();
	}

	void Warning(std::string str)
	{
		std::ofstream warning("Warning.log");
		warning << str << std::endl;
		warning.close();
	}

	void Error(std::string str)
	{
		std::ofstream error("Error.log");
		error << str << std::endl;
		error.close();
	}

}

