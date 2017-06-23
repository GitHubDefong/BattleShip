#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

class Ship
{
private:
	bool direction;
	int length;
	vector<COORD> pos;

public:
	Ship(int len, bool dir);
	~Ship();

	const int & GetLength();
	const bool & GetDirection();
	void ChangeDirection();
	void SavePosition(int x, int y);
	vector<COORD> GetPosition();
};

