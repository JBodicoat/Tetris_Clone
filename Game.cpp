#pragma once
#include"Game.h"
#include"Bar.h"
#include"J.h"
#include"L.h"
#include"S.h"
#include"Square.h"
#include"T.h"
#include"Z.h"
#include<random>
#include<locale>
#include<ctype.h>
#include<ctime>
#include<vector>
#include<conio.h>
#include<Windows.h>

Game::Game()
{
}


Game::~Game()
{
	while(false == m_p_shape_queue.empty())
	{
		delete m_p_shape_queue.front();
		m_p_shape_queue.pop();
	}

	for (Tile* tile : m_p_changed_tiles)
	{
		delete tile;
	}
}

void Game::Setup_Game(void)
{
	system("CLS");

	//Set variables to defaults

	while (false == m_p_shape_queue.empty())
	{
		delete m_p_shape_queue.front();
		m_p_shape_queue.pop();
	}

	for (Tile* tile : m_p_changed_tiles)
	{
		delete tile;
	}

	m_is_game_running = true;

	m_has_score_changed = false;

	m_tile_columns.clear();
	for (unsigned short i{ 0 }; i < m_dropzone_width + 2; i++)
	{
		std::vector<Tile> current_column;
		for (unsigned short j{ 0 }; j < m_dropzone_height + 2; j++)
		{
			Tile tile{ { i, j } };
			current_column.push_back(tile);
		}
		m_tile_columns.push_back(current_column);
	}

	m_p_shapes_placed.clear();

	m_p_changed_tiles.clear();

	m_p_current_shape = nullptr;

	m_turn_start_time = std::clock();

	Generate_Shapes(10);
	m_p_shape_queue = Get_Shapes();

	if (false == Spawn_Shape())
	{
		Generate_Shapes(10);
		m_p_shape_queue = Get_Shapes();
		if (false == Spawn_Shape())
		{
			m_is_game_running = false;

			m_console_manager.Print("No more shapes in queue", { m_dropzone_width + 2, m_dropzone_height - 1 });

			m_console_manager.Print("Game over. Press any key to exit.", { m_dropzone_width + 2, m_dropzone_height });
			(void)_getch();
		}
	}

	// Print Drop zone & score & such
	for (unsigned short i{ 0 }; i <= m_dropzone_height; i++)
	{
		m_console_manager.Print('|', {0, i});
		m_console_manager.Print('|', { m_dropzone_width + 1, i });
	}

	for (unsigned short i{ 1 }; i <= m_dropzone_width; i++)
	{
		m_console_manager.Print('_', { i, m_dropzone_height });
	}

	m_console_manager.Print("Score:", { m_dropzone_width + 2, 0 });

	m_console_manager.Print("Z - Rotate anti-clockwise", { m_dropzone_width + 2, 3 });
	m_console_manager.Print("X - Rotate clockwise", { m_dropzone_width + 2, 4 });
	m_console_manager.Print("LEFT - Move left", { m_dropzone_width + 2, 5 });
	m_console_manager.Print("RIGHT - Move right", { m_dropzone_width + 2, 6 });
	m_console_manager.Print("DOWN - Move down", { m_dropzone_width + 2, 7 });
	m_console_manager.Print("SPACE - Drop shape", { m_dropzone_width + 2, 8 });

	m_userQuit = false;
}

void Game::Get_Input(void)
{
	while (m_console_manager.Get_Input()) {
		if (KEY_EVENT == m_console_manager.Get_Input_Record().EventType && m_console_manager.Get_Input_Record().Event.KeyEvent.bKeyDown)
		{
			switch (m_console_manager.Get_Input_Record().Event.KeyEvent.wVirtualKeyCode)
			{
			case VK_LEFT:
			{
				Coordinate left{ -1, 0 };

				if (true == Can_Move(m_p_current_shape, left))
				{
					Transform_Setup(m_p_current_shape);

					m_p_current_shape->Move(left);

					Transform(m_p_current_shape);
				}
				break;
			}

			case VK_RIGHT:
			{
				Coordinate right{ 1, 0 };

				if (true == Can_Move(m_p_current_shape, right))
				{
					Transform_Setup(m_p_current_shape);

					m_p_current_shape->Move({ 1, 0 });

					Transform(m_p_current_shape);
				}
				break;
			}

			case VK_DOWN:
				if (true == Can_Move(m_p_current_shape, { 0, 1 }))
				{
					Transform_Setup(m_p_current_shape);

					m_p_current_shape->Fall();

					Transform(m_p_current_shape);
				}
				break;

			// Z KEY
			case 0x5A:
			{
				bool rotate_clockwise{ false };

				if (true == Can_Rotate(m_p_current_shape, rotate_clockwise))
				{
					Transform_Setup(m_p_current_shape);

					m_p_current_shape->Rotate(rotate_clockwise);

					Transform(m_p_current_shape);
				}
				break;
			}
			// X KEY
			case 0x58:
			{
				bool rotate_clockwise{ true };

				if (true == Can_Rotate(m_p_current_shape, rotate_clockwise))
				{
					Transform_Setup(m_p_current_shape);

					m_p_current_shape->Rotate(rotate_clockwise);

					Transform(m_p_current_shape);
				}
				break;
			}
			case VK_SPACE:
				Drop_Shape(m_p_current_shape);
				break;

			case VK_ESCAPE:
				// Exit to menu
				m_userQuit = true;
				m_is_game_running = false;
				break;
			}
		}
		else if (MOUSE_EVENT == m_console_manager.Get_Input_Record().EventType)
		{

		}
	}
}

void Game::Update(void)
{
	if (true == m_is_game_running)
	{
		if (nullptr == m_p_current_shape && false == Spawn_Shape())
		{
			Generate_Shapes(10);
			m_p_shape_queue = Get_Shapes();
			if (false == Spawn_Shape())
			{
				m_is_game_running = false;

				m_console_manager.Print("No more shapes in queue", { m_dropzone_width + 2, m_dropzone_height - 1 });

				m_console_manager.Print("Game over. Press any key to exit.", { m_dropzone_width + 2, m_dropzone_height });
				(void)_getch();
			}
		}

		m_elapsed_time = static_cast<double>((std::clock() - m_turn_start_time) / CLOCKS_PER_SEC);
		m_has_score_changed = false;

		if (m_elapsed_time >= m_turn_duration)
		{
			m_turn_start_time = std::clock();

			if (true == Can_Move(m_p_current_shape, { 0, 1 }))
			{
				Transform_Setup(m_p_current_shape);

				m_p_current_shape->Fall();

				Transform(m_p_current_shape);
			}
			else
			{
				Place_Shape();
				Check_Rows();	
			}
		}
	}
}

void Game::Display(void)
{
	// Update score if changed

	for (Tile* tile : m_p_changed_tiles)
	{
		if (true == tile->Get_Has_Block())
		{
			m_console_manager.Print(tile->Get_Block()->Get_Text(), tile->Get_Pos(), tile->Get_Block()->Get_Colour());
		}
		else
		{
			//Print background block
			m_console_manager.Print(' ', tile->Get_Pos());
		}
	}

	m_p_changed_tiles.clear();

	if (true == m_has_score_changed)
	{
		m_console_manager.Print(m_score_manager.Get_Score(), { m_dropzone_width + 9, 0 });
	}

	if (false == m_is_game_running)
	{
		if (!m_userQuit)
		{
			m_console_manager.Print("You stacked your shapes too high!", { m_dropzone_width + 2, m_dropzone_height - 1 });
		}
		m_console_manager.Print("Game over. Press any key to exit.", { m_dropzone_width + 2, m_dropzone_height });
		(void)_getch();
	}
}

bool Game::Can_Move(Shape* shape, Coordinate vector)
{
	bool can_move{ true };

	for (Block* block : shape->m_p_blocks)
	{
		if (true == can_move)
		{
			int new_x{ block->Get_Pos().m_x + vector.m_x };
			int new_y{ block->Get_Pos().m_y + vector.m_y };

			if (new_x > m_dropzone_width || new_x <= 0 || new_y >= m_dropzone_height || new_y <= 0)
			{
				can_move = false;
			}
			else if (true == m_tile_columns[new_x][new_y].Get_Has_Block())
			{
				if (m_tile_columns[new_x][new_y].Get_Block()->Get_Id() != shape->Get_Id())
				{
					can_move = false;
				}
			}
		}
	}

	return can_move;
}

bool Game::Can_Rotate(Shape* shape, bool rotate_clockwise)
{
	bool can_rotate{ true };

	shape->Rotate(rotate_clockwise);

	for (Block* block : shape->m_p_blocks)
	{
		int x = block->Get_Pos().m_x;
		int y = block->Get_Pos().m_y;
		if (x <= 0 || x > m_dropzone_width || y >= m_dropzone_height)
		{
			can_rotate = false;
		}
		else if (true == m_tile_columns[x][y].Get_Has_Block())
		{
			if (m_tile_columns[x][y].Get_Block()->Get_Id() != shape->Get_Id())
			{
				can_rotate = false;
			}
		}
	}

	shape->Rotate(!rotate_clockwise);

	return can_rotate;
}

bool Game::Spawn_Shape(void)
{
	if (m_p_shape_queue.size() > 0)
	{
		m_p_current_shape = m_p_shape_queue.front();
		m_p_shape_queue.pop();

		for (Block* block : m_p_current_shape->m_p_blocks)
		{
			Tile* current_tile{ &m_tile_columns[block->Get_Pos().m_x][block->Get_Pos().m_y] };
			current_tile->Insert_Block(block);
			m_p_changed_tiles.push_back(current_tile);
		}

		return true;
	}

	return false;
}

void Game::Check_Rows(void)
{
	// Check for completed rows
	std::vector<unsigned short> completed_rows;

	for (unsigned short row{ 0 }; row < m_dropzone_height; row++)
	{
		bool row_complete{ true };

		for (unsigned short column{ 1 }; (column <= m_dropzone_width) && (true == row_complete); column++)
		{
			if (false == m_tile_columns[column][row].Get_Has_Block())
			{
				row_complete = false;
			}
		}

		if (true == row_complete)
		{
			completed_rows.push_back(row);
		}
	}

	// Delete any completed rows
	for (unsigned short i{ 0 }; i < completed_rows.size(); i++)
	{
		for (unsigned short column{ 1 }; column <= m_dropzone_width; column++)
		{
			Delete_Block(&m_tile_columns[column][completed_rows[i]]);
			m_p_changed_tiles.push_back(&m_tile_columns[column][completed_rows[i]]);
		}

		m_score_manager.Increment_Score(100 * (i + 1) * (i + 1));
	}

	if (completed_rows.size() > 0)
	{
		m_has_score_changed = true;

		// Drop the blocks above the completed row
		for (unsigned short column{ 1 }; column < m_tile_columns.size() - 1; column++)
		{
			for (int row{ completed_rows.front() - 1 }; row > 0; row--)
			{
				if (m_tile_columns[column][row].Get_Has_Block())
				{
					Block* block = m_tile_columns[column][row].Get_Block();
					block->Move({ 0, static_cast<int>(completed_rows.size()) });

					m_tile_columns[column][row].Remove_Block();
					m_p_changed_tiles.push_back(&m_tile_columns[column][row]);

					m_tile_columns[column][row + completed_rows.size()].Insert_Block(block);
					m_p_changed_tiles.push_back(&m_tile_columns[column][row + completed_rows.size()]);
				}
			}
		}
	}
}

bool Game::Delete_Block(Tile* passed_tile)
{
	if (true == passed_tile->Get_Has_Block())
	{
		Block* p_block_in_tile = passed_tile->Get_Block();
		Shape* p_shape = nullptr;

		if (nullptr != m_p_current_shape && p_block_in_tile->Get_Id() == m_p_current_shape->Get_Id())
		{
			p_shape = m_p_current_shape;
		}
		else
		{
			for (Shape* shape_placed : m_p_shapes_placed)
			{
				if (p_block_in_tile->Get_Id() == shape_placed->Get_Id())
				{
					p_shape = shape_placed;
					break;
				}
			}
		}

		if (p_shape != nullptr)
		{
			bool block_deleted{ false };
			for (unsigned short i{ 0 }; i < p_shape->m_p_blocks.size() && false == block_deleted; i++)
			{
				if (p_shape->m_p_blocks[i]->Get_Pos() == p_block_in_tile->Get_Pos())
				{
					p_shape->m_p_blocks.erase(p_shape->m_p_blocks.begin() + i);
					m_tile_columns[p_block_in_tile->Get_Pos().m_x][p_block_in_tile->Get_Pos().m_y].Remove_Block();
					delete p_block_in_tile; 
					block_deleted = true;

					// Delete shape if it contains no blocks
					if (p_shape->m_p_blocks.empty())
					{
						for (unsigned short j{ 0 }; j < m_p_shapes_placed.size(); j++)
						{
							if (m_p_shapes_placed[j]->Get_Id() == p_shape->Get_Id())
							{
								m_p_shapes_placed.erase(m_p_shapes_placed.begin() + j);
								delete p_shape;
							}
						}
					}
				}
			}
		}

		return true;
	}

	return false;
}

void Game::Place_Shape(void)
{
	for (Block* block : m_p_current_shape->m_p_blocks)
	{
		if (block->Get_Pos().m_y <= m_drop_point.m_y)
		{
			m_is_game_running = false;
		}
	}

	m_p_shapes_placed.push_back(m_p_current_shape);
	m_p_current_shape = nullptr;
}

bool Game::Drop_Shape(Shape* shape)
{
	Transform_Setup(shape);

	bool hasMoved = false;

	bool can_fall{ true };

	do
	{
		can_fall = Can_Move(shape, { 0, 1 });
		if (true == can_fall)
		{
			shape->Fall();
			hasMoved = true;
		}
	} while (true == can_fall);

	Transform(shape);

	return hasMoved;
}

void Game::Generate_Shapes(unsigned short num_of_shapes)
{
	m_f_shapes.open(m_file_name, std::ios::out | std::ios::trunc);

	if (true == m_f_shapes.good())
	{
		for (unsigned short i{ 0 }; i < num_of_shapes; i++)
		{
			Shape* p_current_shape{ nullptr };
			std::string text = { static_cast<char>(Generate_Randn(34, 126)),
				static_cast<char>(Generate_Randn(34, 126)),
				static_cast<char>(Generate_Randn(34, 126)),
				static_cast<char>(Generate_Randn(34, 126)) };

			unsigned int row{ Generate_Randn(0,24) };
			unsigned int column{ Generate_Randn(0, 79) };

			unsigned short colour{ Generate_Randn(1, 254) };

			switch (Generate_Randn(1, 7))
			{
			case 1:
				m_f_shapes << "BAR";
				break;

			case 2:
				m_f_shapes << "J";
				break;

			case 3:
				m_f_shapes << "L";
				break;

			case 4:
				m_f_shapes << "S";
				break;

			case 5:
				m_f_shapes << "SQUARE";
				break;

			case 6:
				m_f_shapes << "T";
				break;

			default:
				m_f_shapes << "Z";
				break;
			}

			m_f_shapes << " " << row << " " << column << " " << colour << " " << text << std::endl;
		}

		m_f_shapes.close();
	}
}

unsigned short Game::Generate_Randn(unsigned short lower, unsigned short higher)
{
	std::random_device rd;
	std::mt19937 mt_rand{ rd() };
	std::uniform_int_distribution<int> uid{ lower, higher };
	return uid(mt_rand);
}

std::queue<Shape*> Game::Get_Shapes(void)
{
	m_f_shapes.open(m_file_name, std::ios::in);
	
	std::queue<Shape*> shapes;

	if (m_f_shapes.good())
	{
		do
		{
			std::string name{ "" };
			unsigned int column{ 0 };
			unsigned int row{ 0 };
			unsigned short colour{ 0 };
			std::string text{ "" };
			m_f_shapes >> name >> row >> column >> colour >> text;

			row = m_drop_point.m_y;
			column = m_drop_point.m_x;

			if ((!m_f_shapes.fail()) && (row >= 0) && (row <= 24) && (column >= 0) && (column <= 79))
			{
				m_f_shapes.clear();

				bool is_printable{ true };
				for (unsigned short i{ 0 }; (i < name.length()) && (true == is_printable); i++)
				{
					if (false == isprint(name[i]))
					{
						is_printable = false;
					}
				}

				if (true == is_printable)
				{
					std::transform(name.begin(), name.end(), name.begin(), ::toupper);

					if ("SQUARE" == name)
					{
						shapes.push(new Square{ text, { static_cast<int>(column), static_cast<int>(row) }, colour });
					}
					else if ("BAR" == name)
					{
						shapes.push(new Bar{ text, { static_cast<int>(column), static_cast<int>(row) }, colour });
					}
					else if ("L" == name)
					{
						shapes.push(new L{ text,{ static_cast<int>(column), static_cast<int>(row) }, colour });
					}
					else if ("J" == name)
					{
						shapes.push(new J{ text,{ static_cast<int>(column), static_cast<int>(row) }, colour });
					}
					else if ("S" == name)
					{
						shapes.push(new S{ text,{ static_cast<int>(column), static_cast<int>(row) }, colour });
					}
					else if ("Z" == name)
					{
						shapes.push(new Z{ text,{ static_cast<int>(column), static_cast<int>(row) }, colour });
					}
					else if ("T" == name)
					{
						shapes.push(new T{ text,{ static_cast<int>(column), static_cast<int>(row) }, colour });
					}
				}
			}
		} while (false == m_f_shapes.fail() && false == m_f_shapes.eof());
	}

	m_f_shapes.close();
	return shapes;
}

bool Game::Get_Is_Game_Running(void)
{
	return m_is_game_running;
}

void Game::Transform_Setup(Shape* shape)
{
	for (Block* block : shape->m_p_blocks)
	{
		m_tile_columns[block->Get_Pos().m_x][block->Get_Pos().m_y].Remove_Block();
		m_p_changed_tiles.push_back(&m_tile_columns[block->Get_Pos().m_x][block->Get_Pos().m_y]);
	}
}

void Game::Transform(Shape* shape)
{
	for (Block* block : shape->m_p_blocks)
	{
		Tile* current_tile{ &m_tile_columns[block->Get_Pos().m_x][block->Get_Pos().m_y] };
		current_tile->Insert_Block(block);

		m_p_changed_tiles.push_back(current_tile);
	}
}
