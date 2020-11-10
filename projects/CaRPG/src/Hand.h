#pragma once
#include <iostream>
#include <vector>

class Hand
{
	// 1 is NO2
	// 2 is Drift
	// 3 is Slipstream
public:
	Hand();
	~Hand();
	void AddCard(int);
	void RemoveCard(int);
	int GetCard(int);
private:
	int EqHand[4] = { 0,0,0,0 }
};