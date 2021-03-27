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
	bool GetEnd();
	int GetSize();
	int GetP1wins();
	int GetP2wins();
private:
	int Increment = 0;
	int CurObs = -1;
	int Value = 1;
	int P1wins = 0;
	int P2wins = 0;
	bool End = false;
	std::vector <int> Deck = { 0,0,2,2,3,1,0,0,2,2,2,2,3,1,1,0,1,3,2,2,0,1 };
};