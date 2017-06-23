#include "App.h"

void timer_clock();
unsigned short h = 0;
unsigned short m = 0;
unsigned short s = 0;

int main()
{
	srand(time(0));

	thread a(timer_clock); // Open a new thread with a game timer

	App app;
	app.Update(); // Initialize and run all game mechanics

	a.detach(); // 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), *new COORD{ 53, 10 });
	cout << "The game lasted " << h << ":" << m << ":" << s << endl; // Duration output of the game

	return 0;
}

void timer_clock()
{
	while (true)
	{
		s++;
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
		Sleep(1000);
	}
}