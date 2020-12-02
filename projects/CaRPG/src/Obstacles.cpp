#include "Obstacles.h"
Obstacles::Obstacles()
{
}
Obstacles::~Obstacles()
{
}
void Obstacles::Draw()
{
		CurObs = Deck.at(Increment);
		srand((unsigned)time(0));
		Value = (rand() % 6 + 1);
		switch (Deck.at(Increment))
		{
		case 0:
			printf("Apex turn Get higher than : ");
			printf("%i", Value);
			printf("\n");
			break;
		case 1:
			printf("Hairpin turn get close to : ");
			printf("%i", Value);
			printf("\n");
			break;
		case 2:
			printf("Chicane turn get close to : ");
			printf("%i", Value);
			printf("\n");
			break;
		case 3:
			printf("Rocks be the lowest");
			printf("\n");
			break;
		}
		if (Increment + 1 < Deck.size())
		{
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
			return 1;
		}
		else if (pGear < oGear && oGear >= Value)
		{
			printf("ENEMY WINS APEX\n");
			return 0;
		}
	}
	else if (CurObs == 1)
	{
		if (abs(pGear - Value) <= abs(oGear - Value))
		{
			printf("PLAYER WINS HAIRPIN\n");
			return 1;
		}
		else
		{
			printf("ENEMY WINS HAIRPIN\n");
			return 0;
		}
	}
	else if (CurObs == 2)
	{
		if (P1wins + P2wins != 2)
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
				printf("CHICANE PLATER WIN\n");
				return 1;
			}
			else
			{
				P1wins = 0;
				P2wins = 0;
				printf("CHICANE ENEMY WIN\n");
				return 0;
			}
		}
	}
	else if (CurObs == 3)
	{
		if (pGear < oGear)
		{
			printf("PLAYER WINS ROCKS\n");
			return 1;
		}
		else
		{
			printf("PLAYER WINS ROCKS\n");
			return 0;
		}
	}
}

bool Obstacles::GetEnd()
{
	return End;
}
