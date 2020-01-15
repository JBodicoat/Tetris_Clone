#pragma once
#include "Shape.h"

class T :
	public Shape
{
public:
	T(std::string text, Coordinate pos, unsigned short colour);
	void Rotate(bool rotate_clockwise);
};

