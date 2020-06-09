#pragma once
#include<iostream>
#include"point.h"
using namespace std;

class Food
{
private:
	Point position;
public:
	Food()
	{
		position.SetPosition(20, 20);
	}
	Food(int x, int y)
	{
		position.SetPosition(x, y);
	}
	void PlaceFood(int x, int y)
	{
		position.SetPosition(x, y);
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		//SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		Point::SetOutputPosition(x, y, hOut);
		cout << "%%";
	}
	Point& GetPosition()
	{
		return position;
	}
	void Show()
	{
		cout << '(' << position.GetX() << "," << position.GetY() << ')';
	}
};
