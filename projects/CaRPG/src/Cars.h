#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class Cars
{
public:
	// 1 is NO2
	// 2 is Drift
	// 3 is Slipstream
	Cars();
	~Cars();
	void ChangeGears(int);
	void ChangeGears();
	int GetGear();
	void SetAcc();
	void SetBrk();
	void PlayCard(int);

	//Hand interactions
	void AddCard(int, bool);
	void RemoveCard(int,bool);
	int GetCard(int, bool);

	// Deck interactions
	int Draw();
	void Shuffle();
private:
	bool Accelerate;
	bool Brake;
	int Gear;
	int Hand[4] = {1,0,0,0};
	std::vector <int> Deck = {1,2,3,4,5};
};