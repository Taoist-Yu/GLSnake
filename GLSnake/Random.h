#pragma once


class Random
{
public:
	static int Next();
	static float Range(float l, float r);

private:
	static void InitSeed();
	static bool isinited;
	
};

