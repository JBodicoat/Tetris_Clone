#pragma once
#include "Shape.h"

class Square :
	public Shape
{
public:
	Square(std::string text, Coordinate pos, unsigned short colour); 
	void Rotate(bool rotate_clockwise);
};

