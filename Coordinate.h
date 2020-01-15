#pragma once

class Coordinate
{
public:
	Coordinate(int x, int y);

	Coordinate& operator=(const Coordinate& coordinate);
	Coordinate& operator+=(const Coordinate& coordinate);
	Coordinate& operator-=(const Coordinate& coordinate);
	Coordinate operator+(const Coordinate& coordinate);
	Coordinate operator-(const Coordinate& coordinate);
	bool operator==(const Coordinate& coordinate);

	int m_x{ 0 };
	int m_y{ 0 };
};

