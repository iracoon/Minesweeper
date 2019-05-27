#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"

struct DrawBoard
{
	void DrawTiles(sf::RenderWindow &window, Board &board, sf::Sprite mine, sf::Sprite num, sf::Sprite cover, sf::Sprite &flag);
	void DrawMenu(sf::RenderWindow &window, Board &board, sf::Sprite &face, sf::Sprite &toggle, sf::Sprite &test1, 
		sf::Sprite&test2, sf::Sprite &test3, sf::Sprite &digits);
};