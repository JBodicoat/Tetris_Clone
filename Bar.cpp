#pragma once
#include "Bar.h"

Bar::Bar(std::string text, Coordinate pos, unsigned short colour)
	:Shape(text, pos, colour)
{
	Rotate(true);
}

void Bar::Rotate(bool rotate_clockwise)
{
	Shape::Rotate(rotate_clockwise);

	if (orientation % 2 == 0)
	{
		m_p_blocks[1]->Move({ 1, 0 });
		m_p_blocks[2]->Move({ 2, 0 });
		m_p_blocks[3]->Move({ 3, 0 });
	}
	else
	{
		m_p_blocks[1]->Move({ 0, 1 });
		m_p_blocks[2]->Move({ 0, 2 });
		m_p_blocks[3]->Move({ 0, 3 });
	}
}