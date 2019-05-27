#pragma once
#include <SFML/Graphics.hpp>

struct Tile: public sf::Sprite
{
	bool isRevealed;
	bool isMine;
	bool isFlagged;
	int mineCount;
	int tileNum;

	Tile()
	{
		isRevealed = false;
		isMine = false;
		isFlagged = false;
		mineCount = 0;
		tileNum = 0;
	}
};