#include "Troll.h"



Troll::Troll()
{
	ID = 0;
	strength = 0;
	team = -1;
}


Troll::~Troll()
{
}


int Troll::getID()
{
	return ID;
}

int Troll::getGroup()
{
	return team;
}

void Troll::setGroup(int n)
{
	team = n;
}

int Troll::getStrength()
{
	return strength;
}

void Troll::setStrength(int newStrength) {
	strength = newStrength;
}
