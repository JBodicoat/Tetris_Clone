#pragma once
#include "Shape.h"

class L :
	public Shape
{
public:
	L(std::string text, Coordinate pos, unsigned short colour);
	void Rotate(bool rotate_clockwise);
};

