#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class Cars
{
public:
	// 0 is NO2
	// 1 is Drift
	// 2 is Slipstream
	// 3 is Muffler
	Cars();
	~Cars();
	void ChangeGears(int);
	void ChangeGears();
	int GetGear();
	void SetAcc();
	void SetBrk();
	bool GetAcc();
	bool GetBrake();
	void PlayCard(int,int);
	int GetAction1();
	int GetAction2();
	void IncreaseScore();
	int GetScore();
	void ResetTurn();

	//Hand interactions
	void AddCard(int, bool);
	void RemoveCard(int,bool);
	int GetCard(int, bool);

	// Deck interactions
	void Draw();
	void Shuffle();
private:
	bool Accelerate;
	bool Brake;
	int Gear;
	int Increment = 0;
	int Action1 = -1;
	int Action2 = -1;
	int CompletedObs = 0;
	int Hand[5] = {0,1,0,2,2};
	std::vector <int> Deck = {1,2,2,0,0};
};