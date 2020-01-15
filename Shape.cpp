#pragma once
#include "Shape.h"

Shape::Shape(std::string text, Coordinate pos, unsigned short colour)
	:m_pos{ pos }
{
	m_id = ID;
	ID++;

	for (unsigned short i{ 0 }; text.length() < 4; i++)
	{
		text.push_back(text[i]);
	}

	for (unsigned short i{ 0 }; i < 4; i++)
	{
		Block* block = new Block{ m_id, text[i], pos,  colour };
		m_p_blocks.push_back(block);
	}
}

Shape::~Shape()
{
	for(Block* block : m_p_blocks)
	{
		delete block;
	}
}

void Shape::Fall()
{
	Coordinate velocity{ 0, 1 };
	Move(velocity);
}

void Shape::Move(Coordinate velocity)
{
	m_pos += velocity;
	for (Block* block : m_p_blocks)
	{
		block->Move(velocity);
	}
}

void Shape::Rotate(bool rotate_clockwise)
{
	if (true == rotate_clockwise)
	{
		orientation++;
	}
	else
	{
		orientation--;
	}

	if (orientation > 4)
	{
		orientation = 1;
	}
	else if (orientation < 1)
	{
		orientation = 4;
	}

	for (Block* block : m_p_blocks)
	{
		block->MoveTo(m_pos);
	}
}

unsigned short Shape::Get_Id(void)
{
	return m_id;
}