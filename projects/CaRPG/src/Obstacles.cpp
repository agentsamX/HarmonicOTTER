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
	Increment++;
	srand((unsigned)time(0));
	Value = (rand() % 6);
}

int Obstacles::GetObs()
{
	return CurObs;
}

int Obstacles::GetValue()
{
	return Value;
}

bool Obstacles::Resolve()
{
	if (CurObs == 0)
	{
		return 1;
	}
	else if (CurObs == 1)
	{
		return 1;
	}
	else if (CurObs == 2)
	{
		return 1;
	}
}
