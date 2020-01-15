#pragma once
#include"Coordinate.h"
#include<string>

class Block
{
public:
	Block();
	Block(unsigned short id, char text, Coordinate pos,  unsigned short colour);
	void Move(Coordinate vector);
	void MoveTo(Coordinate pos);
	unsigned short Get_Id(void);
	char Get_Text(void);
	unsigned short Get_Colour(void);
	Coordinate Get_Pos(void);

protected:
	unsigned short m_id{ 0 };
	char m_text{ ' ' };
	unsigned short m_colour{ 0 };
	Coordinate m_pos{ 0, 0 };
};

