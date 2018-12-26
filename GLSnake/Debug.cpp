#pragma once
#include "Debug.h"

#include<fstream>
#include<iostream>
#include<string>

std::ofstream Debug::log("Log.log");
std::ofstream Debug::warning("Warning.log");
std::ofstream Debug::error("Error.log");

void Debug::Log(std::string str)
{
	std::ofstream log("Log.log");
	log << str << std::endl;
	log.close();
}

void Debug::Warning(std::string str)
{
	std::ofstream warning("Warning.log");
	warning << str << std::endl;
	warning.close();
}

void Debug::Error(std::string str)
{
	std::ofstream error("Error.log");
	error << str << std::endl;
	error.close();
}

