#pragma once
#include<iostream>
#include"point.h"
#include<deque>
#include"Food.h"
#include"point.h"
using namespace std;

class Snake
{
private:
	deque<Point>snake;
	moveDirection direction;
public:
	enum moveDirection {UP,LEFT,DOWN,RIGHT};
	Snake()
	{
		snake.push_back(Point(18, 16));
		snake.push_back(Point(16, 16));
		direction = moveDirection::RIGHT;
	}
	void move()
	{
		switch (direction)
		{
		case moveDirection::DOWN:
			snake.push_front(Point(snake.begin()->GetX(), snake.begin()->GetY() + 1)); break;
		case moveDirection::LEFT:
			snake.push_front(Point(snake.begin()->GetX() - 2, snake.begin()->GetY())); break;
		case moveDirection::RIGHT:
			snake.push_front(Point(snake.begin()->GetX() + 2, snake.begin()->GetY())); break;
		case moveDirection::UP:
			snake.push_front(Point(snake.begin()->GetX(), snake.begin()->GetY() - 1)); break;
		}
		snake.pop_back();
	}
	bool ChangeDirection(moveDirection direction)
	{
		if ((direction + 2) % 4 == this->direction)
			return false;
		else
			this->direction = direction;
		return true;
	}
	void PaintSnake(HANDLE hOut)
	{
		for (Point& point : snake)
		{
			Point::SetOutputPosition(point.GetX(), point.GetY(), hOut);
			point.Plot(hOut);
		}
	}
	//蛇頭蛇身重合的問題
	bool HitItself()
	{
		for (Point& point : snake)
		{
			if (point == *snake.begin())
			{
				if (&point == &(*snake.begin()))
					continue;
				else
					return true;
			}
		}
		return false;
	}
	bool Hit(Point& point)
	{
		for (Point& pointInSnake : snake)
		{
			if (point == pointInSnake)
				return true;
		}
		return false;
	}
	bool HitEdge()
	{
		int x = snake.begin()->GetX();
		int y = snake.begin()->GetY();
		if ((x == 0) || (y == 2) || (x == 78) || (y == 24))
			return true;
		else
			return false;
	}
	Point& Head()
	{
		return *snake.begin();
	}
	Point& Tail()
	{
		return *(snake.end()-1);
	}
	bool Eat(Food& food)
	{
		int foodx = food.GetPosition().GetX();
		int foody = food.GetPosition().GetY();
		int headx = Head().GetX();
		int heady = Head().GetY();
		bool toEat=((foodx==headx)&&(foody==heady+1)&&(direction==moveDirection::DOWN)) || ((foodx == headx) && (foody == (heady - 1)) && (direction == moveDirection::UP))
			|| (((foodx + 2) == headx) && (foody == heady) && (direction == moveDirection::LEFT))
			|| (((foodx - 2) == headx) && (foody == heady) && (direction == moveDirection::RIGHT));
		if (toEat)
		{
			snake.push_front(food.GetPosition());
			return true;
		}
		else
			return false;
	}

};
