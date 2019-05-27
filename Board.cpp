#include "Board.h"
using namespace std;

Board::Board()
{
	gameState = PLAY;
	numMines = 0;
	numCovered = 0;
	flagCount = 0;
	isDebug = false;
	Loader();

	grid.reserve(400);
	int counter = 0;
	for (int y = 0; y < 512; y += 32)
	{
		for (int x = 0; x < 800; x += 32)
		{
			Tile base;
			base.tileNum = counter;
			base.setTexture(tile_revealed);
			base.setPosition(x, y);
			grid.push_back(base);
			counter++;
		}
	}
	SetRandomMines();
}

vector<int> Board::validNeighbors(int pos)
{
	//calculates neighbors of given cell
	vector<int> neighbors;
	if (!(pos % 25 == 0))
	{
		if((pos - 26) >= 0 && (pos - 26) < 400)
			neighbors.push_back(pos - 26);
		if ((pos - 1) >= 0 && (pos - 1) < 400)
			neighbors.push_back(pos - 1);
		if ((pos + 24) >= 0 && (pos + 24) < 400)
			neighbors.push_back(pos + 24);
	}
	if (!((pos + 1) % 25 == 0))
	{
		if ((pos - 24) >= 0 && (pos - 24) < 400)
			neighbors.push_back(pos - 24);
		if ((pos + 1) >= 0 && (pos + 1) < 400)
			neighbors.push_back(pos + 1);
		if ((pos + 26) >= 0 && (pos + 26) < 400)
			neighbors.push_back(pos + 26);
	}
	if ((pos - 25) >= 0 && (pos - 25) < 400)
		neighbors.push_back(pos - 25);
	if ((pos + 25) >= 0 && (pos + 25) < 400)
		neighbors.push_back(pos + 25);
	return neighbors;
}

void Board::floodFill(int pos)
{
	if (grid.at(pos).mineCount > 0)
	{
		grid.at(pos).isRevealed = true;
		return;
	}
	grid.at(pos).isRevealed = true;
	visited.push_back(pos);
	vector<int> moves = validNeighbors(pos);
	for (unsigned int i = 0; i < moves.size(); i++)
	{
		if (!(find(visited.begin(), visited.end(), moves.at(i)) != visited.end()))
		{
			floodFill(moves.at(i));
		}
	}
}

void Board::SetTestMines(string boardName)
{
	gameState = PLAY;
	isDebug = false;
	numMines = 0;
	numCovered = 0;
	flagCount = 0;
	visited.clear();
	for (int i = 0; i < 400; i++)
	{
		grid.at(i).isMine = false;
		grid.at(i).isRevealed = false;
		grid.at(i).isFlagged = false;
	}

	ifstream in(boardName, std::ifstream::in);
	string tmp(static_cast<std::stringstream const&>(std::stringstream() << in.rdbuf()).str());
	tmp.erase(std::remove(tmp.begin(), tmp.end(), '\n'), tmp.end());

	for (int i = 0; i < 400; i++)
	{
		if (tmp[i] == '1')
		{
			grid.at(i).isMine = true;
			numMines += 1;
		}
	}
	SetNumbers();
}

void Board::SetRandomMines()
{
	gameState = PLAY;
	isDebug = false;
	numMines = 0;
	flagCount = 0;
	numCovered = 0;
	visited.clear();
	std::random_device rd;
	std::default_random_engine generator(rd());
	std::uniform_real_distribution<double> distribution(-1.0, 1.0);

	vector<int> mines;
	for (int i = 0; i < 400; i++)
	{
		grid.at(i).isMine = false;
		grid.at(i).isRevealed = false;
		grid.at(i).isFlagged = false;
		mines.push_back(i);
	}

	shuffle(begin(mines), end(mines), rd);
	mines.resize(50);

	for (int i = 0; i < 400; i++)
	{
		if (find(mines.begin(), mines.end(), i) != mines.end())
		{
			grid.at(i).isMine = true;
			numMines += 1;
		}
	}
	flagCount = numMines;
	SetNumbers();
}

void Board::SetNumbers()
{
	for (int i = 0; i < 400; i++)
	{
		grid.at(i).mineCount = 0;
	}

	for (int i = 0; i < 400; i++)
	{
		if (!grid.at(i).isMine)
		{
			if (!(i % 25 == 0))
			{
				//top left
				if ((i - 26) >= 0 && (i - 26) < 400)
					if (grid.at(i - 26).isMine)
						grid.at(i).mineCount += 1;
				//left
				if ((i - 1) >= 0 && (i - 1) < 400)
					if (grid.at(i - 1).isMine)
						grid.at(i).mineCount += 1;
				//bottom left
				if ((i + 24) >= 0 && (i + 24) < 400)
					if (grid.at(i + 24).isMine)
						grid.at(i).mineCount += 1;
			}
			if (!((i + 1) % 25 == 0))
			{
				//top right
				if ((i - 24) >= 0 && (i - 24) < 400)
					if (grid.at(i - 24).isMine)
						grid.at(i).mineCount += 1;
				//right
				if ((i + 1) >= 0 && (i + 1) < 400)
					if (grid.at(i + 1).isMine)
						grid.at(i).mineCount += 1;
				//bottom right
				if ((i + 26) >= 0 && (i + 26) < 400)
					if (grid.at(i + 26).isMine)
						grid.at(i).mineCount += 1;
			}
			//top middle
			if ((i - 25) >= 0 && (i - 25) < 400)
				if (grid.at(i - 25).isMine)
					grid.at(i).mineCount += 1;
			//bottom middle
			if ((i + 25) >= 0 && (i + 25) < 400)
				if (grid.at(i + 25).isMine)
					grid.at(i).mineCount += 1;
		}
	}
}

void Board::SetNumbersTexture(int i, Board &board, sf::Sprite &num)
{
	if (grid.at(i).mineCount == 1)
		num.setTexture(board.number_1);
	else if (grid.at(i).mineCount == 2)
		num.setTexture(board.number_2);
	else if (grid.at(i).mineCount == 3)
		num.setTexture(board.number_3);
	else if (grid.at(i).mineCount == 4)
		num.setTexture(board.number_4);
	else if (grid.at(i).mineCount == 5)
		num.setTexture(board.number_5);
	else if (grid.at(i).mineCount == 6)
		num.setTexture(board.number_6);
	else if (grid.at(i).mineCount == 7)
		num.setTexture(board.number_7);
	else if (grid.at(i).mineCount == 8)
		num.setTexture(board.number_8);
}

void Board::Loader()
{
	debug.loadFromFile("images/debug.png");
	digits.loadFromFile("images/digits.png");
	face_happy.loadFromFile("images/face_happy.png");
	face_lose.loadFromFile("images/face_lose.png");
	face_win.loadFromFile("images/face_win.png");
	flag.loadFromFile("images/flag.png");
	mine.loadFromFile("images/mine.png");
	number_1.loadFromFile("images/number_1.png");
	number_2.loadFromFile("images/number_2.png");
	number_3.loadFromFile("images/number_3.png");
	number_4.loadFromFile("images/number_4.png");
	number_5.loadFromFile("images/number_5.png");
	number_6.loadFromFile("images/number_6.png");
	number_7.loadFromFile("images/number_7.png");
	number_8.loadFromFile("images/number_8.png");
	test_1.loadFromFile("images/test_1.png");
	test_2.loadFromFile("images/test_2.png");
	test_3.loadFromFile("images/test_3.png");
	tile_hidden.loadFromFile("images/tile_hidden.png");
	tile_revealed.loadFromFile("images/tile_revealed.png");
}