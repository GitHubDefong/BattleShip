#pragma once
#include "BattleShip.h"
#include <thread>

class App
{
private:
	HANDLE hConsole;
	BattleShip * GameApp;
	int shift[2]; // Distance between player fields
public:
	App();
	~App();

	void Draw(bool mode); // Output of game fields and their contents (mode - Hide enemy field or not)
	void Update(); // Initialize and run all game mechanics
};

