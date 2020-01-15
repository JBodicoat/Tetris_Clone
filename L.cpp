#pragma once
#include "L.h"

L::L(std::string text, Coordinate pos, unsigned short colour)
	:Shape(text, pos, colour)
{
	Rotate(true);
}

void L::Rotate(bool rotate_clockwise)
{
	Shape::Rotate(rotate_clockwise);

	switch (orientation)
	{
	case 1:
		m_p_blocks[1]->Move({ 0, 1 });
		m_p_blocks[2]->Move({ 0, 2 });
		m_p_blocks[3]->Move({ -1, 0 });
		break;

	case 2:
		m_p_blocks[1]->Move({ -1, 0 });
		m_p_blocks[2]->Move({ -2, 0 });
		m_p_blocks[3]->Move({ 0, -1 });
		break;

	case 3:
		m_p_blocks[1]->Move({ 0, -1 });
		m_p_blocks[2]->Move({ 0, -2 });
		m_p_blocks[3]->Move({ 1, 0 });
		break;

	case 4:
		m_p_blocks[1]->Move({ 1, 0 });
		m_p_blocks[2]->Move({ 2, 0 });
		m_p_blocks[3]->Move({ 0, 1 });
		break;
	}
}
