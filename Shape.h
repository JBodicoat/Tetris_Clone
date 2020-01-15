#pragma once
#include<vector>
#include"Block.h"
#include"Coordinate.h"

class Shape
{
public:
	Shape(std::string text, Coordinate pos, unsigned short colour);
	virtual ~Shape();
	virtual void Rotate(bool rotate_clockwise);
	void Fall(void);
	void Move(Coordinate velocity);
	unsigned short Get_Id(void);

	std::vector<Block*> m_p_blocks;
	

protected:
	static unsigned short ID;
	unsigned short m_id{ 0 };
	unsigned short orientation{ 1 };
	Coordinate m_pos{ 0,0 };
};
