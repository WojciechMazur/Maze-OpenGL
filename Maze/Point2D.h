#pragma once
#ifndef POINT2D_H
#define POINT2D_H

#include "MazeGenerator.h"

template <typename Datatype>
class Point2D
{
public:
	Point2D(Datatype xx, Datatype yy) : x(xx), y(yy) {};
	Point2D(const Point2D& source)
	{
		this->x = source.x;
		this->y = source.y;
	}

	Point2D& operator=(const Point2D& source)
	{
		this->x = source.x;
		this->y = source.y;
		return *this;
	}

	Point2D<Datatype> operator+(int direction)
	{
		Point2D<Datatype> sum(*this);
		switch (direction)
		{
		case Maze::UP:
			sum.x--;
			break;
		case Maze::DOWN:
			sum.x++;
			break;
		case Maze::RIGHT:
			sum.y++;
			break;
		case Maze::LEFT:
			sum.y--;
			break;
		}
		return sum;
	}

	bool Point2D::operator==(const Point2D& source)
	{
		return (this->x == source.x && this->y == source.y) ? true : false;
	}
	~Point2D() {};

	Point2D<Datatype>& Point2D::operator+=(int direction)
	{
		switch (direction)
		{
		case Maze::UP:
			x--;
			break;
		case Maze::DOWN:
			x++;
			break;
		case Maze::RIGHT:
			y++;
			break;
		case Maze::LEFT:
			y--;
			break;
		}
		return *this;
	}

public:
	Datatype x, y;

};

#endif // !POINT2D_H
