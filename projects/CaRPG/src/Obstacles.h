#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class Obstacles
{
	// 0 is Apex
	// 1 is Hairpin
	// 2 is Chicane
	// 3 is Rocks
public:
	Obstacles();
	~Obstacles();
	void Draw();
	int GetObs();
	int GetValue();
	bool Resolve(int,int);
private:
	int Increment = 0;
	int CurObs = -1;
	int Value = 1;
	int ChicaneTurns = 0;
	std::vector <int> Deck = { 0,1,2,3 };
};