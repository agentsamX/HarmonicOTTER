#include "Obstacles.h"
Obstacles::Obstacles()
{
}
Obstacles::~Obstacles()
{
}
void Obstacles::Adddeck(int obs)
{
	Deck.push_back(obs);
}

void Obstacles::Draw()
{
	if (Increment <= Deck.size()-1)
	{
		CurObs = Deck.at(Increment);
		srand((unsigned)time(0));
		Value = (rand() % 6 + 1);
		/*
		switch (Deck.at(Increment))
		{
		case 0:
			printf("Apex turn Get higher than : ");
			printf("%i", Value);
			printf("\n");
			printf("\n");
			break;
		case 1:
			printf("Hairpin turn get close to : ");
			printf("%i", Value);
			printf("\n");
			printf("\n");
			break;
		case 2:
			printf("Chicane turn get close to : ");
			printf("%i", Value);
			printf("\n");
			printf("\n");
			break;
		case 3:
			printf("Rocks be the lowest");
			printf("\n");
			printf("\n");
			break;
		}
		*/
		Increment++;
	}
	else
	{
		End = true;
	}
}

int Obstacles::GetObs()
{
	return CurObs;
}

int Obstacles::GetValue()
{
	return Value;
}

bool Obstacles::Resolve(int pGear, int oGear)
{
	if (CurObs == 0)
	{
		if (pGear >= oGear && pGear >= Value)
		{
			printf("PLAYER WINS APEX\n");
			printf("\n");
			return 1;
		}
		else if (pGear < oGear && oGear >= Value)
		{
			printf("ENEMY WINS APEX\n");
			printf("\n");
			return 0;
		}
	}
	else if (CurObs == 1)
	{
		if (abs(pGear - Value) <= abs(oGear - Value))
		{
			printf("PLAYER WINS HAIRPIN\n");
			printf("\n");
			return 1;
		}
		else
		{
			printf("ENEMY WINS HAIRPIN\n");
			printf("\n");
			return 0;
		}
	}
	else if (CurObs == 2)
	{
		if (P1wins + P2wins != 1)
		{
			if (abs(pGear - Value) <= abs(oGear - Value))
			{
				P1wins += 1;
			}
			else
			{
				P2wins += 1;
			}
		}
		else
		{
			if (P1wins >= P2wins)
			{
				P1wins = 0;
				P2wins = 0;
				printf("CHICANE PLAYER WIN\n");
				printf("\n");
				return 1;
			}
			else
			{
				P1wins = 0;
				P2wins = 0;
				printf("CHICANE ENEMY WIN\n");
				printf("\n");
				return 0;
			}
		}
	}
	else if (CurObs == 3)
	{
		if (pGear < oGear)
		{
			printf("PLAYER WINS ROCKS\n");
			printf("\n");
			return 1;
		}
		else
		{
			printf("PLAYER WINS ROCKS\n");
			printf("\n");
			return 0;
		}
	}
}

bool Obstacles::GetEnd()
{
	return End;
}

int Obstacles::GetSize()
{
	return Deck.size();
}

int Obstacles::GetP1wins()
{
	return P1wins;
}

int Obstacles::GetP2wins()
{
	return P2wins;
}
