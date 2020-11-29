#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class Obstacles
{
public:
	Obstacles();
	~Obstacles();
	void Draw();
	int GetObs();
	int GetValue();
	bool Resolve();
private:
	int Increment = 0;
	int CurObs = -1;
	int  Value = 1;
	std::vector <int> Deck = { 0,0,0,0,0 };
};