#include"Game.h"
#include<windows.h>
#include<iostream>
#include<conio.h>
#include<cstdlib>
using namespace std;

int main()
{
	SetConsoleTitle("³g­¹³D");
	CGame* Game = new CGame();
	Game->NewGame();
	do
	{
		delete Game;
		Game = new CGame();
		
		Game->PlayGame();
		Game->GameOver();
	} while (!Game->Exit());
	Sleep(2000);
	system("pause");
	return 0;
}