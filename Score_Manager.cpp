#pragma once
#include "Score_Manager.h"
#include"Highscore.h"
#include<fstream>
#include<iostream>

Score_Manager::Score_Manager(std::string file_name)
	:m_file_name{file_name}
{
}


Score_Manager::~Score_Manager()
{
	m_file.close();
}

int Score_Manager::Get_Score(void)
{
	return m_score;
}

void Score_Manager::Increment_Score(unsigned int increment)
{
	m_score += increment;
}

std::vector<Highscore> Score_Manager::Get_Highscores(void)
  {
	m_file.open(m_file_name, std::ios::in);

	std::vector<Highscore> highscores;

	if (true == m_file.good())
	{
		std::string name = "";
		int score = 0;

		do
		{
			m_file >> name;

			if (false == m_file.eof() && false == m_file.fail())
			{
				m_file.clear();
				m_file >> score;

				if (false == m_file.eof() && false == m_file.fail())
				{
					Highscore current_highscore{ name, score };

					highscores.push_back(current_highscore);
				}

				m_file.clear();
			}
		} while ((false == m_file.eof()) && (true == m_file.good()));
		m_file.clear();
	}

	m_file.close();

	return highscores;
}

std::vector<Highscore> Score_Manager::Get_Highscores(unsigned short num_of_scores)
{
	m_file.open(m_file_name, std::ios::in);

	std::vector<Highscore> highscores;

	if (true == m_file.good())
	{
		std::string name = "";
		int score = 0;

		for (unsigned short i = 0; (i < num_of_scores) && (!m_file.eof()); i++)
		{
			m_file >> name;

			if (false == m_file.eof() && false == m_file.fail())
			{
				m_file >> score;

				if (false == m_file.fail())
				{
					Highscore current_highscore{ name, score };

					highscores.push_back(current_highscore);
				}

				m_file.clear();
			}
		}
	}

	m_file.close();

	return highscores;
}

void Score_Manager::Insert_Score(std::string name)
{
	m_file.open(m_file_name, std::ios::out | std::ios::app);

	if (true == m_file.good())
	{
		m_file << name << " " << m_score << std::endl;
	}

	m_file.close();
}

void Score_Manager::Delete_Scores(void)
{
	remove(m_file_name.c_str());
}
