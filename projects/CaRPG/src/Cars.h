#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "AudioEngine.h"

class Cars
{
public:
	// 0 is NO2
	// 1 is Drift
	// 2 is Slipstream
	// 3 is E Brake
	// 4 is Quick shift
	// 5 is Sabotage
	Cars();
	~Cars();
	void ChangeGears(int);
	void ChangeGears();
	int GetGear();
	void SetAcc();
	void SetBrk();
	bool GetAcc();
	bool GetBrake();
	bool GetSabo();
	void SetSabo();
	void PlayCard(int,int);
	int GetAction1();
	int GetAction2();
	void SetAction(int);
	void IncreaseScore();
	int GetScore();
	void ResetTurn();
	void ResetPed();

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
	bool Quick;
	bool Sabo;
	int Gear;
	int Increment = 0;
	int Action1 = -1;
	int Action2 = -1;
	int Turns = 0;
	int Turns2 = 0;
	int CompletedObs = 0;
	int Hand[5] = {0,1,2,0,2};
	std::vector <int> Deck = {1,2,2,0,0};
};