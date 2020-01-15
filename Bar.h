#pragma once
#include "Shape.h"

class Bar :
	public Shape
{
public:
	Bar(std::string text, Coordinate pos, unsigned short colour);
	void Rotate(bool rotate_clockwise);
};

