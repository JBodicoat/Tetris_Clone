#pragma once
#include "Coordinate.h"

Coordinate::Coordinate(int x, int y)
	: m_x{x}, m_y{y}
{

}

Coordinate& Coordinate::operator=(const Coordinate& coordinate)
{
	m_x = coordinate.m_x;
	m_y = coordinate.m_y;

	return *this;
}

Coordinate& Coordinate::operator+=(const Coordinate& coordinate)
{
	m_x += coordinate.m_x;
	m_y += coordinate.m_y;

	return *this;
}

Coordinate& Coordinate::operator-=(const Coordinate& coordinate)
{
	m_x -= coordinate.m_x;
	m_y -= coordinate.m_y;

	return *this;
}

Coordinate Coordinate::operator+(const Coordinate& coordinate)
{
	Coordinate result{ m_x + coordinate.m_x, m_y + coordinate.m_y };

	return result;
}

Coordinate Coordinate::operator-(const Coordinate& coordinate)
{
	Coordinate result{ m_x - coordinate.m_x, m_y - coordinate.m_y };

	return result;
}

bool Coordinate::operator==(const Coordinate& coordinate)
{
	if (m_x == coordinate.m_x && m_y == coordinate.m_y)
	{
		return true;
	}

	return false;
}
