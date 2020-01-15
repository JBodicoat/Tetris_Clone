#pragma once
#include "Shape.h"

class Z :
	public Shape
{
public:
	Z(std::string text, Coordinate pos, unsigned short colour);
	void Rotate(bool rotate_clockwise);
};

