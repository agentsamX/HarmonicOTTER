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
		Gear += 4;
		RemoveCard(Position, true);
	}
	if (Hand[Position] == 2)
	{
		printf("Slipstream played");
		RemoveCard(Position, true);
	}
	if (Hand[Position] == 3)
	{
		printf("Drift");
		RemoveCard(Position, true);
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
	srand((unsigned)time(0));
	int randomNumber1;
	int randomNumber2;
	int temp;
	for (int index = 0; index < 5; index++) {
		randomNumber1 = (rand() % Deck.size());
		randomNumber2 = (rand() % Deck.size());
		temp = Deck.at(randomNumber1);
		Deck.at(randomNumber1) = Deck.at(randomNumber2);
		Deck.at(randomNumber2) = temp;
	}
	for (int index = 0; index < Deck.size() - 1; index++)
	{
		printf("%i", Deck.at(index));
	}
}

