#pragma once
#include"Coordinate.h"
#include"Block.h"

class Tile
{
public:
	Tile(Coordinate pos);
	~Tile();

	Coordinate Get_Pos(void);
	bool Insert_Block(Block* p_block);
	bool Remove_Block(void);
	bool Replace_Block(Block* block);
	bool Delete_Block(void);
	bool Get_Has_Block(void);
	Block* Get_Block(void);

protected:
	Coordinate m_pos{ 0, 0 };
	Block* m_p_block{ nullptr };
	bool m_has_block{ false };
};

