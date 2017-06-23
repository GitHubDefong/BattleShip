#include "BattleField.h"

BattleField::BattleField(User * user)
{
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t y = 0; y < 10; y++)
		{
			CharBuffer[i][y] = '.';
		}	
	}
		
	score = 0;
	owner = user;

	ships.push_back(*new Ship(4, 0));
	ships.push_back(*new Ship(3, 0));
	ships.push_back(*new Ship(3, 0));
	ships.push_back(*new Ship(2, 0));
	ships.push_back(*new Ship(2, 0));
	ships.push_back(*new Ship(2, 0));
	ships.push_back(*new Ship(1, 0));
	ships.push_back(*new Ship(1, 0));
	ships.push_back(*new Ship(1, 0));
	ships.push_back(*new Ship(1, 0));

	for (size_t i = 0; i < ships.size(); i++)
	{
		RandomFilling(ships[i]);
	}
}

BattleField::~BattleField()
{

}

void BattleField::RandomFilling(Ship & obj)
{
	
	COORD tempPos;
	tempPos.X = rand() % 10;
	tempPos.Y = rand() % 10;
	obj.ChangeDirection();
	if (obj.GetDirection())
	{
		bool check = false;
		for (size_t i = 0; i < obj.GetLength(); i++)
		{
			if (tempPos.Y + i < 10 && tempPos.X < 10 &&
				GetChar(tempPos.X, tempPos.Y + 1 + i) != '#' &&
				GetChar(tempPos.X, tempPos.Y - 1 + i) != '#' &&
				GetChar(tempPos.X + 1, tempPos.Y + i) != '#' &&
				GetChar(tempPos.X - 1, tempPos.Y + i) != '#' &&
				GetChar(tempPos.X + 1, tempPos.Y + 1 + i) != '#' &&
				GetChar(tempPos.X + 1, tempPos.Y - 1 + i) != '#' &&
				GetChar(tempPos.X - 1, tempPos.Y + 1 + i) != '#' &&
				GetChar(tempPos.X - 1, tempPos.Y - 1 + i) != '#' &&
				GetChar(tempPos.X, tempPos.Y) != '#'
				)
			{
				check = true;
			}
			else
			{
				check = false;
				break;
			}
		}

		if (check == true)
		{
			for (size_t i = 0; i < obj.GetLength(); i++)
			{
				SetChar(tempPos.X, tempPos.Y + i, '#');
				obj.SavePosition(tempPos.X, tempPos.Y + i);
			}
		}
		else RandomFilling(obj);
	}
	else
	{
		bool check = false;
		for (size_t i = 0; i < obj.GetLength(); i++)
		{
			if (tempPos.Y < 10 && tempPos.X + i < 10 &&
				GetChar(tempPos.X + i, tempPos.Y + 1) != '#' &&
				GetChar(tempPos.X + i, tempPos.Y - 1) != '#' &&
				GetChar(tempPos.X + i + 1, tempPos.Y) != '#' &&
				GetChar(tempPos.X + i - 1, tempPos.Y) != '#' &&
				GetChar(tempPos.X + i + 1, tempPos.Y + 1) != '#' &&
				GetChar(tempPos.X + i + 1, tempPos.Y - 1) != '#' &&
				GetChar(tempPos.X + i - 1, tempPos.Y + 1) != '#' &&
				GetChar(tempPos.X + i - 1, tempPos.Y - 1) != '#' &&
				GetChar(tempPos.X, tempPos.Y) != '#'
				)
			{
				check = true;
			}
			else
			{
				check = false;
				break;
			}
		}

		if (check == true)
		{
			for (size_t i = 0; i < obj.GetLength(); i++)
			{
				SetChar(tempPos.X + i, tempPos.Y, '#');
				obj.SavePosition(tempPos.X + i, tempPos.Y);
			}
		}
		else RandomFilling(obj);
	}

}

void BattleField::SetChar(int x, int y, char c)
{
	CharBuffer[x][y] = c;
}

void BattleField::AddScore()
{
	score++;
}

const char & BattleField::GetChar(int x, int y)
{
	return CharBuffer[x][y];
}

User & BattleField::GetOwner()
{
	return *owner;
}

const int & BattleField::GetScore()
{
	return score;
}

char BattleField::Hit(int x, int y)
{
	if (CharBuffer[x][y] == '#') // Hit
	{
		CharBuffer[x][y] = '+';
		return '+';
	}
	else if (CharBuffer[x][y] == '+') // Hit the old coordinates
	{
		return '=';
	}
	else // Missed
	{
		CharBuffer[x][y] = '-';
		return '-';
	}
}

int BattleField::GetLiveShips() 
{
	int result = 10;
	for (size_t i = 0; i < ships.size(); i++)
	{
		int count = 0;
		for (size_t y = 0; y < ships[i].GetPosition().size(); y++)
		{
			COORD temp;
			temp.X = ships[i].GetPosition()[y].X;
			temp.Y = ships[i].GetPosition()[y].Y;

			if (CharBuffer[temp.X][temp.Y] == '+')
			{
				count++;
			}
		}
		
		if (count == ships[i].GetLength())
		{
			result--;
		}
	}
	return result;
}