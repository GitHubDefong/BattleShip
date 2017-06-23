#define _CRT_SECURE_NO_WARNINGS
#include "App.h"

App::App()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GameApp = new BattleShip();
	shift[0] = 3;
	shift[1] = 33;
	pause = false;
}

App::~App()
{
}

void App::Draw(bool mode)
{	
	COORD tempPos;
	for (size_t j = 0; j < 2; j++)
	{
		tempPos.X = shift[j];
		tempPos.Y = 1;
		for (size_t i = 0; i < 10; i++)
		{
			SetConsoleCursorPosition(hConsole, tempPos);
			for (size_t y = 0; y < 10; y++)
			{
				if (mode == false)
				{
					if (j == 0) cout << GameApp->GetBattleFields()[j].GetChar(i, y);
					else cout << ".";
				}
				else cout << GameApp->GetBattleFields()[j].GetChar(i, y);
			}
			tempPos.Y++;
		}
	}
}

void App::Update()
{
	int range = 20;
	COORD tempPos;
	tempPos.X = 3;
	tempPos.Y = 0;
	for (size_t i = 0; i < 2; i++)
	{
		SetConsoleCursorPosition(hConsole, tempPos);
		cout << "ABCDEFGHIJ";

		tempPos.X = shift[i] - shift[0];
		tempPos.Y = 0;
		for (size_t i = 0; i < 10; i++)
		{
			tempPos.Y++;
			SetConsoleCursorPosition(hConsole, tempPos);
			cout << " " << i << endl;
		}
		tempPos.X += shift[1];
		tempPos.Y = 0;
	}

	Draw(false);

	// A set of logic forAI
	COORD AIShotPos;
	bool AIhitting = false; // Got or not (If so, then look for "the rest of the ship")
	COORD AIhittingPos = { 0 , 0 }; // Coordinates of the hit
	// bool AIchangeShotDirection = true; // Missing after hitting == changing direction from the previous point
	vector<COORD> AIpreviousРits; // Collection of previous shots
	// int AIshipsAnalysis[4] = { 4, 3, 2, 1 }; //	Analysis of the remaining ships from the enemy is necessary to prevent the search for the remaining parts of the ship, which can no longer be (for example, if a ship of 4 cells has already been destroyed)

	bool GameOver = false;
	
	while (true)
	{
		tempPos.X = shift[1] + range;
		tempPos.Y = 9;
		SetConsoleCursorPosition(hConsole, tempPos);
		cout << "Enter the coordinates for the attack:";
		
		while (true)
		{
			char c[2];
			tempPos.X = shift[1] + range;
			tempPos.Y = 12;
			SetConsoleCursorPosition(hConsole, tempPos);
			cout << "                                                                           ";
			SetConsoleCursorPosition(hConsole, tempPos);
			cout << "Enter number from <0 to 9>: ";

			while (true)
			{				
				c[0] = getch();
				if (c[0] == VK_SPACE) Pause();
				else if (kbhit)
				{
					break;
				}
			}
			if (pause)
			{
				pause = false;
				continue;
			}
			 
			if (atoi(&c[0]) > 0 && atoi(&c[0]) < 10 || c[0] == '0')
			{				
				tempPos.Y = 12;
				SetConsoleCursorPosition(hConsole, tempPos);
				cout << "Enter symbol from <ABCDEFGHIJ>: ";

				while (true)
				{
					c[1] = getch();
					if (c[1] == VK_SPACE) Pause();
					else if (kbhit)
					{
						break;
					}
				}
				if (pause)
				{
					pause = false;
					continue;
				}
				
				if (c[1] == 'A' || c[1] == 'a') c[1] = 0;
				else if (c[1] == 'B' || c[1] == 'b') c[1] = 1;
				else if (c[1] == 'C' || c[1] == 'c') c[1] = 2;
				else if (c[1] == 'D' || c[1] == 'd') c[1] = 3;
				else if (c[1] == 'E' || c[1] == 'e') c[1] = 4;
				else if (c[1] == 'F' || c[1] == 'f') c[1] = 5;
				else if (c[1] == 'G' || c[1] == 'g') c[1] = 6;
				else if (c[1] == 'H' || c[1] == 'h') c[1] = 7;
				else if (c[1] == 'I' || c[1] == 'i') c[1] = 8;
				else if (c[1] == 'J' || c[1] == 'j') c[1] = 9;
				else
				{
					cout << "Error! Invalid character!";
					Sleep(1000);
					continue;
				}
				
				int num = atoi(&c[0]);
				if (num >= 0 && num < 10)
				{
					// Implementing the player's attack

					tempPos.X = shift[1] + c[1];
					tempPos.Y = num + 1;
					SetConsoleCursorPosition(hConsole, tempPos);

					cout << GameApp->Shot(atoi(&c[0]), c[1], 1);

					// Check for victory or defeat for player 1
					if (GameApp->GetBattleFields()[0].GetScore() == 20)
					{
						GameOver = true;
						break;
					}

					//////////////////////////////////////////////////////////////////////////////////////

					// Logic AI
					
					AIhitting = false; // Temporary variable

					if (AIhitting == false)
					{
						// Random shot
						bool tempCheck;
						while (true)
						{
							tempCheck = true;
							AIShotPos.X = rand() % 10;
							AIShotPos.Y = (rand() % 10) + 1;
							
							for (size_t i = 0; i < AIpreviousРits.size(); i++) // Check if the position matches the previous shots
								if (AIpreviousРits[i].X == AIShotPos.X && AIpreviousРits[i].Y == AIShotPos.Y)
								{
									tempCheck = false;
									break;
								}

							if (tempCheck)
								break;
						}
					}
					else if (AIhitting == true)
					{
						// Logic for finding the remaining parts of the ship
						// ...
					}

					AIpreviousРits.push_back(AIShotPos);
					tempPos.X = shift[0] + AIShotPos.X;
					tempPos.Y = AIShotPos.Y;
					SetConsoleCursorPosition(hConsole, tempPos);
					char tempAnalysisHit = GameApp->Shot(AIShotPos.Y - 1, AIShotPos.X, 0);
					
					// Shot analysis
					if (tempAnalysisHit == '+')
					{
						AIhitting = true;
						AIhittingPos = AIShotPos;
					}

					Sleep(500);
					cout << tempAnalysisHit;
					
					// Check for victory or defeat for player 2
					if (GameApp->GetBattleFields()[1].GetScore() == 20)
					{
						GameOver = true;
						break;
					}
				}
				else
				{
					cout << "Error! Invalid character!";
					Sleep(1000);
				}
			}
			else
			{
				cout << "Error! Invalid character!";
				Sleep(1000);
			}
			if (GameOver) break;
		}

		if (GameOver == true)
		{
			tempPos.Y = 9;
			SetConsoleCursorPosition(hConsole, tempPos);
			for (size_t i = 0; i < 10; i++)
			{
				tempPos.X = shift[1] + range;
				SetConsoleCursorPosition(hConsole, tempPos);
				for (size_t y = 0; y < 50; y++)
				{
					cout << " ";
				}
				tempPos.Y++;
			}

			// Open output of game fields and player statistics...

			Draw(true); 

			tempPos.X = shift[1] + range;
			tempPos.Y = 0;
			SetConsoleCursorPosition(hConsole, tempPos);
			cout << "Win! = ";
			if (GameApp->GetBattleFields()[0].GetScore() == 20)
				cout << GameApp->GetBattleFields()[0].GetOwner().GetName();
			else cout << GameApp->GetBattleFields()[1].GetOwner().GetName();
			tempPos.X = shift[1] + range;
			tempPos.Y = 2;
			SetConsoleCursorPosition(hConsole, tempPos);
			cout << "Stats:" << endl;

			tempPos.Y += 2;
			SetConsoleCursorPosition(hConsole, tempPos);
			cout << GameApp->GetBattleFields()[0].GetOwner().GetName() << ": " << "Living ships: " << GameApp->GetBattleFields()[0].GetLiveShips();
			tempPos.Y++;
			SetConsoleCursorPosition(hConsole, tempPos);
			cout << GameApp->GetBattleFields()[0].GetOwner().GetName() << ": " << "Killed ships: " << 10 - GameApp->GetBattleFields()[1].GetLiveShips();
			tempPos.Y += 2;
			SetConsoleCursorPosition(hConsole, tempPos);
			cout << GameApp->GetBattleFields()[1].GetOwner().GetName() << ": " << "Living ships: " << GameApp->GetBattleFields()[1].GetLiveShips();
			tempPos.Y++;
			SetConsoleCursorPosition(hConsole, tempPos);
			cout << GameApp->GetBattleFields()[1].GetOwner().GetName() << ": " << "Killed ships: " << 10 - GameApp->GetBattleFields()[0].GetLiveShips();

			tempPos.X = 0;
			tempPos.Y = 15;
			SetConsoleCursorPosition(hConsole, tempPos);
			break;
		}
	}
}

void App::Pause()
{
	pause = true;

	COORD tempPos;
	tempPos.X = shift[1] + 20;
	tempPos.Y = 12;
	SetConsoleCursorPosition(hConsole, tempPos);
	cout << "                  Press ESC to resume                                   ";
	SetConsoleCursorPosition(hConsole, tempPos);
	cout << "Pause: ";

	unsigned short h = 0;
	unsigned short m = 0;
	unsigned short s = 0;

	tempPos.X += 6;
	while (true)
	{
		if (kbhit && s != 0)
		{
			if (GetAsyncKeyState(VK_ESCAPE))
			{
				SetConsoleCursorPosition(hConsole, tempPos);
				cout << "                                                    ";
				break;
			}
		}
	
		if (s == 60)
		{
			s = 0;
			m++;
			if (m == 60)
			{
				m = 0;
				h++;
			}
		}
		
		SetConsoleCursorPosition(hConsole, tempPos);
		cout << "           ";
		SetConsoleCursorPosition(hConsole, tempPos);
		cout << h << ":" << m << ":" << s;
		
		Sleep(1000);
		s++;
	}
}
