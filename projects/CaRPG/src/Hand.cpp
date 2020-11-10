#include "Hand.h"

Hand::Hand()
{
}

Hand::~Hand()
{
}

void Hand::AddCard(int NewCard)
{
	for (int i = 0; i <= 4; i++)
	{
		if (EqHand[i] = 0)
		{
			EqHand[i] = NewCard;
			break;
		}
	}

}

void Hand::RemoveCard(int position)
{
	EqHand[position-1] = 0;
}

int Hand::GetCard(int position)
{
	return EqHand[position-1];
}
