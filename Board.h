#pragma once
#include "Tile.h" 
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <random>
#include <functional>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>   
using namespace std;

class Board
{
	void Loader();
public:
	enum GameState {PLAY, WIN, LOSE};
	bool isDebug;
	int numMines;
	int numCovered;
	int flagCount;
	GameState gameState;
	vector<Tile> grid;
	vector<int> validNeighbors(int pos);
	vector<int> visited;

	Board();
	void SetRandomMines();
	void SetTestMines(string boardName);
	void SetNumbers();
	void SetNumbersTexture(int i, Board &board, sf::Sprite &num);
	void floodFill(int pos);

	//textures
	sf::Texture debug;
	sf::Texture digits;
	sf::Texture face_happy;
	sf::Texture face_lose;
	sf::Texture face_win;
	sf::Texture flag;
	sf::Texture mine;
	sf::Texture number_1;
	sf::Texture number_2;
	sf::Texture number_3;
	sf::Texture number_4;
	sf::Texture number_5;
	sf::Texture number_6;
	sf::Texture number_7;
	sf::Texture number_8;
	sf::Texture test_1;
	sf::Texture test_2;
	sf::Texture test_3;
	sf::Texture tile_hidden;
	sf::Texture tile_revealed;
};