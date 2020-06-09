#pragma once
#include<iostream>
#include<windows.h>
using namespace std;

class Point
{
private:
	int x, y;
public:
	Point() {}
	Point(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	void Plot(HANDLE hOut)
	{
		SetOutputPosition(x, y, hOut);
		cout << "@";
	}
	void Clear(HANDLE hOut)
	{
		SetOutputPosition(x, y, hOut);
		cout << " ";
	}
	void Clear()
	{
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		cout << " ";
	}
	static void SetOutputPosition(int x, int y, HANDLE hOut)
	{
		COORD position;
		position.X = x;
		position.Y = y;
		SetConsoleCursorPosition(hOut, position);
	}
	bool operator == (Point& point)
	{
		return(point.x == this->x) && (point.y == this->y);
	}
	void SetPosition(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	int GetX()
	{
		return x;
	}
	int GetY()
	{
		return y;
	}
};