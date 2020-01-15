#include "Tile.h"
#include <iostream>

Tile::Tile(Coordinate pos)
	:m_pos{ pos }, m_p_block{ nullptr }, m_has_block {false}
{
}


Tile::~Tile()
{
}

Coordinate Tile::Get_Pos(void)
{
	return m_pos;
}

bool Tile::Insert_Block(Block* p_block)
{
	if (nullptr == m_p_block)
	{
		m_p_block = p_block;
		m_has_block = true;

		return true;
	}
	
	return false;
}

bool Tile::Remove_Block(void)
{
	if (nullptr != m_p_block)
	{
		m_p_block = nullptr;
		m_has_block = false;

		return true;
	}
	else
	{
		std::cout << "Block not removed from tile";
	}

	return false;
}

bool Tile::Replace_Block(Block* block)
{
	bool block_replaced = false;

	if (nullptr != m_p_block)
	{
		block_replaced = true;
	}
	else
	{
		block_replaced = false;
	}

	m_p_block = block;
	m_has_block = true;

	return block_replaced;
}

bool Tile::Delete_Block(void)
{
	if (nullptr != m_p_block)
	{
		delete m_p_block;
		m_has_block = false;

		return true;
	}
	
	return false;
}

bool Tile::Get_Has_Block(void)
{
	return m_has_block;
}

Block* Tile::Get_Block(void)
{
	return m_p_block;
}