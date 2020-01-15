#pragma once
#include"Block.h"
#include"Shape.h"
#include"Bar.h"
#include"J.h"
#include"L.h"
#include"S.h"
#include"Square.h"
#include"T.h"
#include"Z.h"
#include"Console_Manager.h"
#include"Score_Manager.h"
#include"Tile.h"
#include<vector>
#include<queue>
#include<random>
#include<locale>
#include<ctype.h>
#include<ctime>

class Game
{
public:
	Game();
	~Game();

	void Setup_Game(void);
	void Get_Input(void);
	void Update(void);
	void Display(void);
	bool Can_Move(Shape* shape, Coordinate vector);
	bool Can_Rotate(Shape* shape, bool rotate_clockwise);
	bool Spawn_Shape(void);
	void Check_Rows(void);
	bool Delete_Block(Tile* tile);
	void Place_Shape(void);
	bool Drop_Shape(Shape* shape);
	void Generate_Shapes(unsigned short num_of_shapes);
	unsigned short Generate_Randn(unsigned short lower, unsigned short higher);
	std::queue<Shape*> Get_Shapes(void);
	bool Get_Is_Game_Running(void);
	void Transform_Setup(Shape* shape);
	void Transform(Shape* shape);

protected:
	std::queue<Shape*> m_p_shape_queue;
	std::vector<Shape*> m_p_shapes_placed;
	std::vector<Tile*> m_p_changed_tiles;
	Shape* m_p_current_shape{ nullptr };
	bool m_is_game_running{ false };
	bool m_has_score_changed{ false };
	std::vector<std::vector<Tile>> m_tile_columns;
	Console_Manager m_console_manager;
	Score_Manager m_score_manager{"Highscores.txt"};
	unsigned short m_dropzone_width{ 10 };
	unsigned short m_dropzone_height{ 20 };
	Coordinate m_drop_point{ (m_dropzone_width / 2), 3 };
	std::fstream m_f_shapes;
	std::string m_file_name{ "Shapes.txt" };
	std::clock_t m_turn_start_time;
	double m_elapsed_time{ 0 };
	double m_turn_duration{ 0.8 };
};
