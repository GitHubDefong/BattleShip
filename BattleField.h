#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include <string>
#include <time.h>
#include "User.h"
#include "Ship.h"

using namespace std;

class BattleField
{
private:
	int CharBuffer[10][10]; // Buffer of the playing field
	int score;
	User * owner; // Player-Owner
	void RandomFilling(Ship & obj); // Random placement of ships on the playing field
	void SetChar(int x, int y, char c);

public:
	vector<Ship> ships;

	BattleField(User * user);
	~BattleField();
	
	void AddScore();
	const char & GetChar(int x, int y);
	User & GetOwner();
	const int & GetScore();
	char Hit(int x, int y); // Check for hit
	int GetLiveShips(); // Counting surviving ships
};