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

void Cars::PlayCard(int type)
{
}
