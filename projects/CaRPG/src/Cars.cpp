#include "Cars.h"

Cars::Cars()
{
	Accelerate = false;
	Brake = false;
	Gear = 1;
}

Cars::~Cars()
{
}

void Cars::ChangeGears(int NewGear)
{
	Gear = NewGear;
}

void Cars::ChangeGears()
{
	if (Accelerate)
		Gear += 1;
	if (Brake)
		Gear -= 1;
}

int Cars::GetGear()
{
	return Gear;
}

void Cars::SetAcc()
{
	if (!Accelerate)
		Accelerate = true;
	else
		Accelerate = false;
}

void Cars::SetBrk()
{
	if (!Brake)
		Brake = true;
	else
		Brake = false;
}

void Cars::PlayCard(int Position)
{
	if (Hand[Position] == 1)
	{
		printf("NO2 played");
		RemoveCard(Position, true);
	}
	if (Hand[Position] == 2)
	{
		printf("Slipstream played");
	}
	if (Hand[Position] == 3)
	{
		printf("Drift");
	}
}

void Cars::AddCard(int NewCard, bool object)
{
	if (object == true)
	{
		for (int i = 0; i <= 4; i++)
		{
			if (Hand[i] == 0)
			{
				Hand[i] = NewCard;
				break;
			}
		}
	}
	if (object == false)
	{
		Deck.emplace_back(NewCard);
	}
}

void Cars::RemoveCard(int Position, bool object)
{
	if (object == true)
	{
		Hand[Position] = 0;
	}
	if (object == false)
	{
		Deck.erase(Deck.begin() + Position);
	}
}

int Cars::GetCard(int Position, bool object)
{
	if (object == true)
	{
		return Hand[Position];
	}
	if (object == false)
	{
		return Deck.at(Position);
	}
}

int Cars::Draw()
{
	
	return 0;
}

void Cars::Shuffle()
{
}

