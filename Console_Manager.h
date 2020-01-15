#pragma once
#include"Coordinate.h"
#include<Windows.h>
#include<string>
#include<iostream>

class Console_Manager
{
public:
	Console_Manager();
	Console_Manager(HANDLE input, HANDLE output, unsigned short colour);
	unsigned short Get_Input(void);
	void Print(std::string output, Coordinate pos);
	void Print(std::string output, Coordinate pos, unsigned short colour);
	void Print(char output, Coordinate pos);
	void Print(char output, Coordinate pos, unsigned short colour);
	void Print(int output, Coordinate pos);
	void Print(int output, Coordinate pos, unsigned short colour);
	std::string Get_String(std::string message);
	void Set_Cursor_Pos(Coordinate pos);
	void Revert_Cursor(void);
	INPUT_RECORD Get_Input_Record(void);

protected:
	Coordinate m_last_cursor_pos{ 0, 0 };
	Coordinate m_cursor_pos{ 0, 0 };
	HANDLE m_output_handle{ GetStdHandle(STD_OUTPUT_HANDLE) };
	HANDLE m_input_handle{ GetStdHandle(STD_INPUT_HANDLE) };
	INPUT_RECORD m_input_record{ 0 };
	DWORD m_events_read{ 0 };
	DWORD m_events{ 0 };
	CONSOLE_SCREEN_BUFFER_INFO m_buffer;
	unsigned short m_colour{ 7 };
};

