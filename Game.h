#pragma once
#include<iostream>
#include"Snake.h"
#include"Food.h"
#include"point.h"
#include"conio.h"
#include"windows.h"
#include"time.h"
using namespace std;
class Snake;
class CGame 
{
private:
	bool exit;
	int speed;
	bool gameOver;
	Snake snake;
	Food food;
	int length, width, score;
public:

	CGame()
	{
		length = 80;
		width = 24;
		score = 0;
		exit = false;
	}
	bool Exit()
	{
		return exit;
	}
	void NewGame()
	{
		system("cls");
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD position = { 17,6 };
		SetConsoleCursorPosition(hOut, position);

		cout << " ―――   ―     ―  ―――  ―    ― ――――";
		Point::SetOutputPosition(17, 7, hOut);
		cout << "―    ―  ――   ― ―    ― ―   ―  ―";
		Point::SetOutputPosition(17, 8, hOut);
		cout << "―        ― ―  ― ―    ― ―  ―   ―";
		Point::SetOutputPosition(17, 9, hOut);
		cout << " ―――   ―  ― ― ―――― ――     ―――";
		Point::SetOutputPosition(17, 10, hOut);
		cout << "      ―  ―   ―― ―    ― ―  ―   ―";
		Point::SetOutputPosition(17, 11, hOut);
		cout << "―    ―  ―     ― ―    ― ―   ―  ―";
		Point::SetOutputPosition(17, 12, hOut);
		cout << " ―――   ―     ― ―    ― ―    ― ――――";

		while (true)
		{
			Point::SetOutputPosition(27, 20, hOut);
			cout << "Start";

			Sleep(70);
			for (int i = 0; i < 25; i++)
				cout << "\b \b";
			Sleep(70);
			if (_kbhit())
				break;
		}
		cin.get();
	}
	
	void PaintEdge()
	{
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		for (int x = 0;x<=78;x+=2)
		{
			for (int y = 0; y < 25; y++)
			{
				if ((x == 0) || (y == 0) || (x == 78) || (y == 24))
				{
					Point::SetOutputPosition(x, y, hOut);
					cout << "―";
				}
			}
		}
		for (int x = 2; x <= 78; x += 2)
		{
			Point::SetOutputPosition(x, 2, hOut);
			cout << "―";
		}
	}
	void UpdateScore(bool eaten)
	{
		if (eaten)
		{
			HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
			score += 10;
			Point::SetOutputPosition(58, 1, hOut);
			cout << "Score: " << score;
			int spaceUsed = 0;

			for (int s = score; s != 0; s /= 10)
				spaceUsed++;
			for (int i = 0; i < 10 - spaceUsed; i++)
				cout << ' ';
		}
	}
	bool DirectionChanged()
	{
		char ch;
		if (_kbhit())
		{
			ch = _getch();
			switch (ch)
			{
			case 'w':case 'W':
				return snake.ChangeDirection(snake.UP);
			case 'a':case'A':
				return snake.ChangeDirection(snake.LEFT);
			case 's':case 'S':
				return snake.ChangeDirection(snake.DOWN);
			case 'd':case 'D':
				return snake.ChangeDirection(snake.RIGHT);
			}
		}
		return false;
	}
	void RandomFood(Food& food)
	{
		srand(static_cast<unsigned>(time(NULL)));
		int x, y;
		while (true)
		{
			x = rand() % (length / 2) * 2;
			y = rand() % (width / 2) * 2;
			if ((x <= 2) || (y <= 6) || (x >= 70) || (y >= 20))
				continue;
			if (!snake.Hit(Point(x, y)))
				break;
			else
				continue;
		}
		food.PlaceFood(x, y);
	}
	void PlayGame()
	{
		system("cls");
		PaintEdge();
		food.PlaceFood(20, 20);
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		snake.PaintSnake(hOut);
		while (true)
		{
			snake.Tail().Clear(hOut);
			DirectionChanged();
			bool eaten = snake.Eat(food);
			if (!eaten)
				snake.move();
			else
				RandomFood(food);
			UpdateScore(eaten);
			snake.Head().Plot(hOut);
			if (snake.HitEdge() || snake.HitItself())
			{
				Sleep(1000);
				snake.Head().Plot(hOut);
				Sleep(3000);
				break;
			}
			Sleep(speed);
		}
	}
	void GameOver()
	{
		int x = 28, y = 3;
		system("cls");
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		Point::SetOutputPosition(x + 7, y + 13, hOut);
		cout << "GAME OVER";
		Point::SetOutputPosition(x + 7, y + 15, hOut);
		cout << "Score: " << score;
		Point::SetOutputPosition(x + 4, y + 17, hOut);
		cout << "play Again?(Y/N)";
		char ch;
		while (true)
		{
			ch = _getch();
			if (ch == 'n' || ch == 'N')
			{
				exit = true;
				break;
			}
			else if (ch == 'y' || ch == 'Y')
				break;
		}
		Point::SetOutputPosition(x - 1, y + 19, hOut);
	}



};