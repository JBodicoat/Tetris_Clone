#pragma once
#include"Highscore.h"
#include<string>
#include<vector>
#include<fstream>
#include<iostream>

class Score_Manager
{
public:
	Score_Manager(std::string file_name);
	~Score_Manager();

	int Get_Score(void);
	void Increment_Score(unsigned int increment);
	std::vector<Highscore> Get_Highscores(void);
	std::vector<Highscore> Get_Highscores(unsigned short num_of_scores);
	void Insert_Score(std::string player_name);
	void Delete_Scores(void);

protected:
	int m_score{ 0 };
	std::string m_file_name{ "" };
	std::fstream m_file;
};

