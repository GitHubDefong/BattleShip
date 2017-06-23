#include "Ship.h"

Ship::Ship(int len, bool dir)
{
	length = len;
	direction = dir;
}

Ship::~Ship()
{
}

const int & Ship::GetLength()
{
	return length;
}

const bool & Ship::GetDirection()
{
	return direction;
}

void Ship::ChangeDirection()
{
	direction = rand() % 2;
}

void Ship::SavePosition(int x, int y)
{
	COORD temp = { x, y };
	pos.push_back(temp);
}

vector<COORD> Ship::GetPosition()
{
	return pos;
}
