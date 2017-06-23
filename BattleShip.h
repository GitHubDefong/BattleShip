#pragma once
#include "BattleField.h"

class BattleShip
{
private:
	vector<BattleField> battleFields; // Collection of playing fields
	
public:
	BattleShip();
	~BattleShip();

	vector<BattleField> & GetBattleFields(); 
	char Shot(int x, int y, int index); // Shot method. Accepts the coordinates and the player's index for which you need to shoot
	
};

