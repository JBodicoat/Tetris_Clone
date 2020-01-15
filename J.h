#pragma once
#include "Shape.h"

class J :
	public Shape
{
public:
	J(std::string text, Coordinate pos, unsigned short colour);
	void Rotate(bool rotate_clockwise);
};

