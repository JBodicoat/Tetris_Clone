#include"Bar.h"
#include"Block.h"
#include"Console_Manager.h"
#include"Coordinate.h"
#include"Game.h"
#include"Highscore.h"
#include"J.h"
#include"L.h"
#include"S.h"
#include"Score_Manager.h"
#include"Shape.h"
#include"Square.h"
#include"T.h"
#include"Tile.h"
#include"Z.h"

#include<conio.h>

unsigned short Shape::ID{ 0 };

int main()
{
	Game game;
	bool quit_game{ false };
	do
	{
		system("CLS");
		std::cout << "Do you wish to\n1 - Play\n2 - Read How To Play\n3 - Quit\n\nPlease enter either 1, 2 or 3." << std::endl;
		bool choice_valid{ true };

		do
		{
			char menu_choice = getchar();
			choice_valid = true;

			switch (menu_choice)
			{
				// 1
			case 0x31:
				game.Setup_Game();

				do
				{
					game.Get_Input();
					game.Update();
					game.Display();
				} while (game.Get_Is_Game_Running());
				break;
				// 2
			case 0x32:
				system("CLS");
				std::cout << "~~~~~ HOW TO PLAY ~~~~~\nShapes will spawn and fall down the screen until they hit the bottom or another shape.\nFill an entire row to remove that row and earn points.\nThe more rows removed with a single shape the greater the points earned.\nDon't let the shapes stack too high or you will lose\n\nEnjoy!" << std::endl;
				std::cout << "\nPress any key to go back to the menu...";
				(void)_getch();
				break;
				// 3
			case 0x33:
				quit_game = true;
				break;
			}
		} while (false == choice_valid);
	} while (false == quit_game);
}
