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
	int GetGear();
	void SetAcc();
	void SetBrk();
	bool GetAcc();
	bool GetBrk();
	bool GetSabo();
	void SetSabo();
	void PlayCard(int,int);
	/*
	int GetAction1();
	int GetAction2();
	void SetAction(int);
	*/
	void IncreaseScore();
	int GetScore();
	void SetOppGear(int);
	void ResetTurn();
	void ResolveCards();
	void SetEnded();
	bool GetEnded();
	int GetPosition1();
	int GetPosition2();
	void SetPosition(int);

	//Hand interactions
	void AddCard(int, bool);
	void RemoveCard(int,bool);
	int GetCard(int, bool);

	// Deck interactions
	void Draw();
	void Shuffle();
private:
	bool Quick;
	bool Sabo;
	bool PEnd = false;
	bool Acce = false;
	bool Brake = false;
	int Gear;
	int Increment = 0;
	/*
	int Action1 = -1;
	int Action2 = -1;
	*/
	int Turns = 0;
	int Turns2 = 0;
	int Position1 = -1;
	int Position2 = -1;
	int CompletedObs = 0;
	int Oppgear;
	int Hand[5] = {0,1,2,3,4};
	std::vector <int> Deck = {0,0,1,1,2,2,3,3,4,4,5,5};
};