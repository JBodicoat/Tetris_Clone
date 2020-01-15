#pragma once
#include "Block.h"
#include "Coordinate.h"

Block::Block()
{
}

Block::Block(unsigned short id, char text, Coordinate pos, unsigned short colour)
	: m_id{ id }, m_pos{ pos }, m_text{ text }, m_colour{ colour }
{
}

void Block::Move(Coordinate vector)
{
	m_pos += vector;

}

void Block::MoveTo(Coordinate pos)
{
	m_pos = pos;
}

unsigned short Block::Get_Id(void)
{
	return m_id;
}

char Block::Get_Text(void)
{
	return m_text;
}

unsigned short Block::Get_Colour(void)
{
	return m_colour;
}

Coordinate Block::Get_Pos(void)
{
	return m_pos;
}