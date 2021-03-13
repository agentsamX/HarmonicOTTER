#include "Cars.h"


Cars::Cars()
{
	Accelerate = false;
	Brake = false;
	Quick = false;
	Sabo = false;
	Gear = 1;
}

Cars::~Cars()
{
}

void Cars::ChangeGears(int NewGear)
{
	Gear = NewGear;
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
			Action1 = -2;
		else
			Action2 = -2;
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
			Action1 = -3;
		else
			Action2 = -3;
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

bool Cars::GetSabo()
{
	return Sabo;
}

void Cars::SetSabo()
{
	if (Sabo == false)
		Sabo = true;
	else if (Sabo == true)
		Sabo = false;
}

void Cars::PlayCard(int Position, int NewGear)
{
	AudioEngine& audio = AudioEngine::Instance();

	if (Hand[Position] == 0)
	{
		if (Action1 == -1)
			Action1 = Hand[Position];
		else
			Action2 = Hand[Position];
		audio.GetEvent("MultiNitro").Restart();
	}
	if (Hand[Position] == 1)
	{
		if (Action1 == -1)
			Action1 = Hand[Position];
		else
			Action2 = Hand[Position];
		audio.GetEvent("Drift").Restart();

	}
	if (Hand[Position] == 2)
	{
		if (Action1 == -1)
			Action1 = Hand[Position];
		else
			Action2 = Hand[Position];
		audio.GetEvent("Slipstream").Restart();
	}
	if (Hand[Position] == 3)
	{
		if (Action1 == -1)
			Action1 = Hand[Position];
		else
			Action2 = Hand[Position];
	}
	if (Hand[Position] == 4)
	{
		if (Action1 == -1)
			Action1 = Hand[Position];
		else
			Action2 = Hand[Position];
	}
	if (Hand[Position] == 5)
	{
		if (Action1 == -1)
			Action1 = Hand[Position];
		else
			Action2 = Hand[Position];
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

void Cars::SetAction(int action)
{
	if (Action1 == -1)
		Action1 = action;
	else
		Action2 = action;
}

void Cars::IncreaseScore()
{
	CompletedObs += 1;
}

int Cars::GetScore()
{
	return CompletedObs;
}

void Cars::SetOppGear(int gear)
{
	Oppgear = gear;
}

void Cars::ResetTurn()
{
	Draw();
	Action1 = -1;
	Action2 = -1;
	PEnd = false;
	if (Turns == 2 && Quick == true)
	{
		Turns = 0;
		Quick = false;
	}
	if (Quick == true)
	{
		Turns += 1;
	}
	if (Turns2 == 1 && Sabo == true)
	{
		Turns2 = 0;
		Sabo = false;
	}
	else if (Sabo == true)
	{
		Turns2 += 1;
	}
}

void Cars::ResetPed()
{
	Accelerate = false;
	Brake = false;
}

void Cars::ResolveCards()
{
	if (Action1 == 0)
	{
		if (Gear + 3 > 6)
		{
			Gear = 6;
		}
		else
		{
			Gear += 3;
		}
	}
	else if (Action1 == 2)
	{
		Gear = Oppgear;
	}
	else if (Action1 == 3)
	{
		Gear = 1;
	}
	else if (Action1 == 4)
	{
		Quick = true;
		if (Turns != 0)
		{
			Turns = 0;
		}
	}
	else if (Action1 == -2 && Gear + 1 != 7)
	{
		if (Quick == false)
		{
			Gear += 1;
		}
		else if (Gear + 2 > 6)
		{
			Gear = 6;
		}
		else
		{
			Gear += 2;
		}
	}
	else if (Action1 == -3 && Gear - 1 != 0)
	{
		if (Quick == false)
		{
			Gear -= 1;
		}
		else if (Gear - 2 < 0)
		{
			Gear = 0;
		}
		else
		{
			Gear -= 2;
		}
	}


	if (Action2 == 0)
	{
		if (Gear + 3 > 6)
		{
			Gear = 6;
		}
		else
		{
			Gear += 3;
		}
	}
	else if (Action2 == 3)
	{
		Gear = 1;
	}
	else if (Action2 == 4)
	{
		Quick = true;
		if (Turns != 0)
		{
			Turns = 0;
		}
	}
	else if (Action1 == -2 && Gear + 1 != 7)
	{
		if (Quick == false)
		{
			Gear += 1;
		}
		else if (Gear + 2 > 6)
		{
			Gear = 6;
		}
		else
		{
			Gear += 2;
		}
	}
	else if (Action1 == -3 && Gear - 1 != 0)
	{
		if (Quick == false)
		{
			Gear -= 1;
		}
		else if (Gear - 2 < 0)
		{
			Gear = 0;
		}
		else
		{
			Gear -= 2;
		}
	}
}

void Cars::SetEnded()
{
	PEnd = true;
}

bool Cars::GetEnded()
{
	return PEnd;
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
	for (int i = 0; i < Deck.size(); i++)
	{
		if (Hand[i] == -1 && Increment < Deck.size())
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
}

