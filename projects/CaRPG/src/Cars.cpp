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
	{
		Accelerate = true;
		Brake = false;
		if (Action1 == -1)
			Action1 = 6;
		else
			Action2 = 6;
	}
	else
	{
		Accelerate = false;
		Brake = false;
	}
}

void Cars::SetBrk()
{
	if (!Brake)
	{
		Brake = true;
		Accelerate = false;
		if (Action1 == -1)
			Action1 = 5;
		else
			Action2 = 5;
	}
	else
	{
		Brake = false;
		Accelerate = false;
	}
}

bool Cars::GetAcc()
{
	if (Accelerate == true)
		return true;
	else
		return false;
}

bool Cars::GetBrake()
{
	if (Brake == true)
		return true;
	else
		return false;
}

void Cars::PlayCard(int Position, int NewGear)
{
	if (Hand[Position] == 0)
	{
		printf("NO2 played");
		if (Gear + 3 > 6)
		{
			Gear = 6;
		}
		else
		{
			Gear += 3;
		}
		if (Action1 == -1)
			Action1 = Hand[Position];
		else
			Action2 = Hand[Position];
		RemoveCard(Position, true);
	}
	if (Hand[Position] == 1)
	{
		printf("Drift");
		Gear = NewGear;
		if (Action1 == -1)
			Action1 = Hand[Position];
		else
			Action2 = Hand[Position];
		RemoveCard(Position, true);
	}
	if (Hand[Position] == 2)
	{
		printf("Slipstream played");
		Gear = NewGear;
		if (Action1 == -1)
			Action1 = Hand[Position];
		else
			Action2 = Hand[Position];
		RemoveCard(Position, true);
	}
}

int Cars::GetAction1()
{
	return Action1;
}

int Cars::GetAction2()
{
	return Action2;
}

void Cars::IncreaseScore()
{
	CompletedObs += 1;
}

int Cars::GetScore()
{
	return CompletedObs;
}

void Cars::ResetTurn()
{
	Draw();
	Action1 = -1;
	Action2 = -1;
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
		Hand[Position] = -1;
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

void Cars::Draw()
{
	for (int i = 0; i < 5; i++)
	{
		if (Hand[i] == -1)
		{
			Hand[i] = Deck.at(Increment);
			Increment += 1;
			break;
		}
	}
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

