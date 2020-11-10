#pragma once
#include <iostream>
#include <vector>

class Cars
{
public:
	Cars();
	~Cars();
	void ChangeGears(int);
	void ChangeGears();
	int GetGear();
	void SetAcc();
	void SetBrk();
	void PlayCard(int);
private:
	bool Accelerate;
	bool Brake;
	int Gear;
};