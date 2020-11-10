#include "Deck.h"

Deck::Deck()
{
}

Deck::~Deck()
{
}

int Deck::Draw()
{
	return 0;
}

void Deck::AddCard(int NewCard)
{
	EqDeck.emplace_back(NewCard);
}

void Deck::RemoveCard(int position)
{
	EqDeck.erase(EqDeck.begin()+position-1);
}

void Deck::Shuffle()
{
}

int Deck::GetCard(int position)
{
	return EqDeck.at(position);
}
