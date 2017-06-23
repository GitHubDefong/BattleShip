#include "BattleShip.h"

BattleShip::BattleShip()
{
	BattleField obj1(new User("Player"));
	BattleField obj2(new User("COM"));
	battleFields.push_back(obj1);
	battleFields.push_back(obj2);
}

BattleShip::~BattleShip()
{
}

vector<BattleField> & BattleShip::GetBattleFields()
{
	return battleFields;
}

char BattleShip::Shot(int x, int y, int index)
{
	
	char temp = battleFields[index].Hit(x, y);
	if (temp == '+') // If you return + (Then hit)
	{
		if (index == 0) battleFields[1].AddScore();
		else if (index == 1) battleFields[0].AddScore();
	}
	else if (temp == '=') // If you return = (Then they already shot)
	{
		temp = '+';
	}	

	return temp;  // If you return - (Missed)
}


