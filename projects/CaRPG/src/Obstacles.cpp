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
		break;
	case 1:
		printf("Hairpin turn get close to : ");
		printf("%i", Value);
		break;
	case 2:
		printf("Chicane turn");
		break;
	case 3:
		printf("Rocks");
		break;
	}
	Increment++;
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
			printf("Player wins");
			return 1;
		}
		else if (pGear < oGear && oGear >= Value)
		{
			printf("EnemyWins");
			return 0;
		}
	}
	else if (CurObs == 1)
	{
		if (abs(pGear - Value) <= abs(oGear - Value))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if (CurObs == 2)
	{
		if (pGear > oGear)
		{
			ChicaneTurns += 1;
			return 1;
		}
		else
		{
			ChicaneTurns += 1;
			return 0;
		}
	}
	else if (CurObs == 3)
	{
		if (pGear > oGear)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}
