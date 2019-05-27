#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Board.h"
#include "DrawBoard.h"
using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");
	Board board;
	DrawBoard drawBoard;
	sf::Sprite mine;
	sf::Sprite num;
	sf::Sprite cover;
	sf::Sprite face;
	sf::Sprite toggle;
	sf::Sprite test1;
	sf::Sprite test2;
	sf::Sprite test3;
	sf::Sprite flag;
	sf::Sprite digits;

	//game loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			
			//set mines and numbers
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (face.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
				{
					board.SetRandomMines();
					board.flagCount = board.numMines;
				}				
				else if (test1.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
				{
					board.SetTestMines("boards/testboard1.brd");
					board.flagCount = board.numMines;
				}
				else if (test2.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
				{
					board.SetTestMines("boards/testboard2.brd");
					board.flagCount = board.numMines;
				}
				else if (test3.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
				{
					board.SetTestMines("boards/testboard3.brd");
					board.flagCount = board.numMines;
				}
					
				if (toggle.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
					board.isDebug = !board.isDebug;


				for (int i = 0; i < 400; i++)
				{
					if(board.gameState != board.LOSE)
					{
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
						{
							if (board.grid.at(i).getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
							{
								if (!(board.grid.at(i).isFlagged))
								{
									board.grid.at(i).isRevealed = true;
									if (board.grid.at(i).isMine)
									{
										board.gameState = board.LOSE;
										board.isDebug = true;
									}
									else if (board.grid.at(i).mineCount == 0)
										board.floodFill(i);
								}
							}
						}
						if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
						{
							if (board.grid.at(i).getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
								if (!board.grid.at(i).isRevealed)
								{
									if (board.grid.at(i).isFlagged)
									{
										board.flagCount++;
									}
									else
									{
										board.flagCount--;
									}
									board.grid.at(i).isFlagged = !(board.grid.at(i).isFlagged);
								}
						}
					}
				}
			}
		}
		window.clear(sf::Color::White);
		drawBoard.DrawMenu(window, board, face, toggle, test1, test2, test3, digits);
		drawBoard.DrawTiles(window, board, mine, num, cover, flag);
		window.display();
	}
	return 0;
}