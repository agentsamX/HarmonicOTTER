#include "Cars.h"


Cars::Cars()
{
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
	if (Position2 != -6)
	{
		if (Position1 == -3)
		{
			Position1 = -1;
			Acce = false;
		}
		else if (Position2 == -3)
		{
			Position2 = -1;
			Acce = false;
		}
		else if (Position1 == -1 || Position1 == -2)
		{
			Position1 = -3;
			Brake = false;
			Acce = true;
		}
		else if (Position2 == -1 || Position2 == -2)
		{
			Position2 = -3;
			Brake = false;
			Acce = true;
		}
		else
		{
			Position1 = Position2;
			Position2 = -3;
			Brake = false;
			Acce = true;
		}
	}
	else
	{
		if (Position1 == -3)
		{
			Position1 = -1;
			Acce = false;
		}
		else if (Position1 == -1)
		{
			Position1 = -3;
			Brake = false;
			Acce = true;
		}
		else
		{
			Position1 = -3;
			Brake = false;
			Acce = true;
		}
	}
}

void Cars::SetBrk()
{
	if (Position2 != -6)
	{
		if (Position1 == -2)
		{
			Position1 = -1;
			Brake = false;
		}
		else if (Position2 == -2)
		{
			Position2 = -1;
			Brake = false;
		}
		else if (Position1 == -1 || Position1 == -3)
		{
			Position1 = -2;
			Brake = true;
			Acce = false;
		}
		else if (Position2 == -1 || Position2 == -3)
		{
			Position2 = -2;
			Brake = true;
			Acce = false;
		}
		else
		{
			Position1 = Position2;
			Position2 = -2;
			Brake = true;
			Acce = false;
		}
	}
	else
	{
		if (Position1 == -3)
		{
			Position1 = -1;
			Brake = false;
		}
		else if (Position1 == -1)
		{
			Position1 = -2;
			Brake = true;
			Acce = false;
		}
		else
		{
			Position1 = -2;
			Brake = true;
			Acce = false;
		}
	}
}

bool Cars::GetAcc()
{
	return Acce;
}

bool Cars::GetBrk()
{
	return Brake;
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


	if (Position2 != -6)
	{
		if (Position1 == Position)
			Position1 = -1;
		else if (Position2 == Position)
			Position2 = -1;
		else if (Position1 == -1)
			Position1 = Position;
		else if (Position2 == -1)
			Position2 = Position;
		else
		{
			Position1 = Position2;
			Position2 = Position;
		}
	}
	else
	{
		if (Position1 == Position)
			Position1 = -1;
		else if (Position1 == -1)
			Position1 = Position;
		else
			Position1 = Position;
	}

	if (Position2 != 6)
	{
		if (Position1 != -3 && Position2 != -3 && Acce == true)
		{
			Acce = false;
			Brake = false;
		}

		if (Position1 != -2 && Position2 != -2 && Brake == true)
		{
			Acce = false;
			Brake = false;
		}
	}
	else
	{
		if (Position1 != -1 && Acce == true)
		{
			Acce = false;
			Brake = false;
		}

		if (Position1 != -1 && Brake == true)
		{
			Acce = false;
			Brake = false;
		}
	}

	if (Hand[Position] == 0)
	{
		audio.GetEvent("MultiNitro").Restart();
	}
	if (Hand[Position] == 1)
	{
		audio.GetEvent("Drift").Restart();
	}
	if (Hand[Position] == 2)
	{
		audio.GetEvent("Slipstream").Restart();
	}
	if (Hand[Position] == 3)
	{
		// Put audio cues here 
	}
	if (Hand[Position] == 4)
	{
		// Put audio cues here 
	}
	if (Hand[Position] == 5)
	{
		// Put audio cues here 
	}
}
/*
int Cars::GetAction1()
{
}

int Cars::GetAction2()
{
}

void Cars::SetAction(int action)
{
}
*/

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
	if (Position1 != -1 && Position1 != -3 && Position1 != -2)
	{
		RemoveCard(Position1, true);
	}
	else if (Position2 != -1 && Position2 != -3 && Position2 != -2)
	{
		RemoveCard(Position2, true);
	}

	Draw();
	Position1 = -1;
	Position2 = -1;
	Acce = false;
	Brake = false;
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


void Cars::ResolveCards()
{
	if (Position1 != -1 && Position1 != -2 && Position1 != -3)
	{
		if (Hand[Position1] == 0)
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
		else if (Hand[Position1] == 2)
		{
			Gear = Oppgear;
		}
		else if (Hand[Position1] == 3)
		{
			Gear = 1;
		}
		else if (Hand[Position1] == 4)
		{
			Quick = true;
			if (Turns != 0)
			{
				Turns = 0;
			}
		}
	}
	if (Position2 != -6)
	{
		if (Position2 != -1 && Position2 != -2 && Position2 != -3)
		{
			if (Hand[Position2] == 0)
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
			else if (Hand[Position2] == 2)
			{
				Gear = Oppgear;
			}
			else if (Hand[Position2] == 3)
			{
				Gear = 1;
			}
			else if (Hand[Position2] == 4)
			{
				Quick = true;
				if (Turns != 0)
				{
					Turns = 0;
				}
			}
		}
	}

	if (Position1 == -3 || Position2 == -3)
	{
		if (Gear + 1 != 7)
		{
			if (Quick == false)
			{
				Gear += 1;
			}
			else if (Gear + 2 > 6 || Gear > 6)
			{
				Gear = 6;
			}
			else
			{
				Gear += 2;
			}
		}
	}

	if (Position1 == -2 || Position2 == -2)
	{
		if (Gear - 1 != 0)
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

	PEnd = true;
}

void Cars::SetEnded()
{
	PEnd = true;
}

bool Cars::GetEnded()
{
	return PEnd;
}

int Cars::GetPosition1()
{
	return Position1;
}

int Cars::GetPosition2()
{
	return Position2;
}

void Cars::SetPosition(int Position)
{
	Position2 = Position;
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

