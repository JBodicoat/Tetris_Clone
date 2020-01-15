#pragma once
#include "Console_Manager.h"
#include<iostream>

Console_Manager::Console_Manager()
{
	SetConsoleMode(m_input_handle, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
}

Console_Manager::Console_Manager(HANDLE input, HANDLE output, unsigned short colour)
	:m_input_handle{ input }, m_output_handle{ output }, m_colour{ colour }
{
	SetConsoleMode(m_input_handle, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
}

unsigned short Console_Manager::Get_Input(void)
{
	m_events_read = 0;
	m_events = 0;

	GetNumberOfConsoleInputEvents(m_input_handle, &m_events);

	if (m_events < 1)
	{
		return 0;
	}

	ReadConsoleInput(m_input_handle, &m_input_record, 1, &m_events_read);

	return static_cast<unsigned short>(m_events);
}

void Console_Manager::Print(std::string output, Coordinate pos)
{
	SetConsoleCursorPosition(m_output_handle, { static_cast<short>(pos.m_x), static_cast<short>(pos.m_y) });
	std::cout << output;
}

void Console_Manager::Print(std::string output, Coordinate pos, unsigned short colour)
{
	if (colour < 255)
	{
		SetConsoleTextAttribute(m_output_handle, colour);
	}
	SetConsoleCursorPosition(m_output_handle, { static_cast<short>(pos.m_x), static_cast<short>(pos.m_y) });
	std::cout << output;

	SetConsoleTextAttribute(m_output_handle, m_colour);
}

void Console_Manager::Print(char output, Coordinate pos)
{
	SetConsoleTextAttribute(m_output_handle, m_colour);
	SetConsoleCursorPosition(m_output_handle, { static_cast<short>(pos.m_x), static_cast<short>(pos.m_y) });
	std::cout << output;
}

void Console_Manager::Print(char output, Coordinate pos, unsigned short colour)
{
	if (colour < 255)
	{
		SetConsoleTextAttribute(m_output_handle, colour);
	}
	SetConsoleCursorPosition(m_output_handle, { static_cast<short>(pos.m_x), static_cast<short>(pos.m_y) });
	std::cout << output;

	SetConsoleTextAttribute(m_output_handle, m_colour);
}

void Console_Manager::Print(int output, Coordinate pos)
{
	SetConsoleTextAttribute(m_output_handle, m_colour);
	SetConsoleCursorPosition(m_output_handle, { static_cast<short>(pos.m_x), static_cast<short>(pos.m_y) });
	std::cout << output;
}

void Console_Manager::Print(int output, Coordinate pos, unsigned short colour)
{
	if (colour < 255)
	{
		SetConsoleTextAttribute(m_output_handle, colour);
	}
	SetConsoleCursorPosition(m_output_handle, { static_cast<short>(pos.m_x), static_cast<short>(pos.m_y) });
	std::cout << output;

	SetConsoleTextAttribute(m_output_handle, m_colour);
}

std::string Console_Manager::Get_String(std::string message)
{
	std::cout << message;
	std::string input{ "" };
	std::getline(std::cin, input);

	return input;
}

void Console_Manager::Set_Cursor_Pos(Coordinate pos)
{
	if (GetConsoleScreenBufferInfo(m_output_handle, &m_buffer))
	{
		m_last_cursor_pos = { m_buffer.dwCursorPosition.X, m_buffer.dwCursorPosition.Y };
	}

	SetConsoleCursorPosition(m_output_handle, { static_cast<short>(pos.m_x), static_cast<short>(pos.m_y) });
}

void Console_Manager::Revert_Cursor(void)
{
	SetConsoleCursorPosition(m_output_handle, { static_cast<short>(m_last_cursor_pos.m_x), static_cast<short>(m_last_cursor_pos.m_y) });
}

INPUT_RECORD Console_Manager::Get_Input_Record(void)
{
	return m_input_record;
}
