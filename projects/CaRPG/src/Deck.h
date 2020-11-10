#pragma once
#include <iostream>
#include <vector>

class Deck
{
	// 1 is NO2
	// 2 is Drift
	// 3 is Slipstream
public:
	Deck();
	~Deck();
	int Draw();
	void AddCard(int);
	void RemoveCard(int);
	void Shuffle();
	int GetCard(int);
private:
	std::vector <int> EqDeck;
	int DeckPos;
};