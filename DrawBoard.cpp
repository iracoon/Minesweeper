#include "DrawBoard.h"

void DrawBoard::DrawTiles(sf::RenderWindow &window, Board &board,
	sf::Sprite mine, sf::Sprite num, sf::Sprite cover, sf::Sprite &flag)
{
	//draw bottom layer, mines and numbers, cover
	for (int i = 0; i < 400; i++)
	{
		window.draw(board.grid.at(i));

		//draw mines
		if (board.grid.at(i).isMine)
		{
			mine.setPosition(board.grid.at(i).getPosition().x, board.grid.at(i).getPosition().y);
			mine.setTexture(board.mine);
			window.draw(mine);
		}
		//draw numbers
		if (board.grid.at(i).mineCount != 0)
		{
			num.setPosition(board.grid.at(i).getPosition().x, board.grid.at(i).getPosition().y);
			board.SetNumbersTexture(i, board, num);
			window.draw(num);
		}

		if (board.gameState == board.LOSE) 	//on lose, show all mines
		{
			if (!board.grid.at(i).isRevealed && !board.grid.at(i).isMine)
			{
				cover.setPosition(board.grid.at(i).getPosition().x, board.grid.at(i).getPosition().y);
				cover.setTexture(board.tile_hidden);
				window.draw(cover);
				if (board.grid.at(i).isFlagged)
				{
					flag.setPosition(board.grid.at(i).getPosition().x, board.grid.at(i).getPosition().y);
					flag.setTexture(board.flag);
					window.draw(flag);
				}
			}
		}
		else 
		{
			if (!board.grid.at(i).isRevealed)
			{
				cover.setPosition(board.grid.at(i).getPosition().x, board.grid.at(i).getPosition().y);
				cover.setTexture(board.tile_hidden);
				window.draw(cover);
				board.numCovered += 1;
				if (board.isDebug)
				{
					window.draw(mine);
				}
				if (board.grid.at(i).isFlagged || (board.gameState == board.WIN && board.grid.at(i).isMine))
				{
					flag.setPosition(board.grid.at(i).getPosition().x, board.grid.at(i).getPosition().y);
					flag.setTexture(board.flag);
					window.draw(flag);
				}
			}
		}
	}

	if (board.numMines == board.numCovered) //check for win
	{
		board.gameState = board.WIN;
	}
	board.numCovered = 0;
}

void DrawBoard::DrawMenu(sf::RenderWindow &window, Board &board,
	sf::Sprite &face, sf::Sprite &toggle, sf::Sprite &test1, sf::Sprite&test2, sf::Sprite &test3, sf::Sprite &digits)
{
	face.setPosition(368, 512);
	if (board.gameState == board.PLAY)
		face.setTexture(board.face_happy);
	else if (board.gameState == board.LOSE)
		face.setTexture(board.face_lose);
	else if (board.gameState == board.WIN)
		face.setTexture(board.face_win);
	window.draw(face);

	toggle.setPosition(496, 512);
	toggle.setTexture(board.debug);
	window.draw(toggle);

	test1.setPosition(560, 512);
	test1.setTexture(board.test_1);
	window.draw(test1);

	test2.setPosition(624, 512);
	test2.setTexture(board.test_2);
	window.draw(test2);

	test3.setPosition(688, 512);
	test3.setTexture(board.test_3);
	window.draw(test3);

	//flag counter display
	digits.setTexture(board.digits);
	string tmp = to_string(board.flagCount);
	int xPos = 0;
	for (int i = 0; i < tmp.length(); i++)
	{
		digits.setPosition(xPos, 512);
		xPos += 21;
		if (tmp[i] == '0')
			digits.setTextureRect(sf::IntRect(0, 0, 21, 32));
		if (tmp[i] == '1')
			digits.setTextureRect(sf::IntRect(21, 0, 21, 32));
		if (tmp[i] == '2')
			digits.setTextureRect(sf::IntRect(42, 0, 21, 32));
		if (tmp[i] == '3')
			digits.setTextureRect(sf::IntRect(63, 0, 21, 32));
		if (tmp[i] == '4')
			digits.setTextureRect(sf::IntRect(84, 0, 21, 32));
		if (tmp[i] == '5')
			digits.setTextureRect(sf::IntRect(105, 0, 21, 32));
		if (tmp[i] == '6')
			digits.setTextureRect(sf::IntRect(126, 0, 21, 32));
		if (tmp[i] == '7')
			digits.setTextureRect(sf::IntRect(147, 0, 21, 32));
		if (tmp[i] == '8')
			digits.setTextureRect(sf::IntRect(168, 0, 21, 32));
		if (tmp[i] == '9')
			digits.setTextureRect(sf::IntRect(189, 0, 21, 32));
		if (tmp[i] == '-')
			digits.setTextureRect(sf::IntRect(210, 0, 21, 32));
		window.draw(digits);
	}
}
