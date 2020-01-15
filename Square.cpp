#pragma once
#include "Square.h"

Square::Square(std::string text, Coordinate pos, unsigned short colour)
	:Shape(text, pos, colour)
{
	m_p_blocks[1]->Move({ 1, 0 });
	m_p_blocks[2]->Move({ 0, 1 });
	m_p_blocks[3]->Move({ 1, 1 });
}

void Square::Rotate(bool rotate_clockwise)
{
}
