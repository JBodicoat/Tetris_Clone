#pragma once
#include "Shape.h"

class S :
	public Shape
{
public:
	S(std::string text, Coordinate pos, unsigned short colour);
	void Rotate(bool rotate_clockwise);
};

