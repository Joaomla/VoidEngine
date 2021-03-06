#pragma once
#include "Game.h"
#include <vector>

class Map
{
private:
	SDL_Rect src, dest;
	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;
	std::vector<SDL_Texture*> textures;

	int map[20][25];

public:
	Map();
	~Map();

	void LoadMap(int arr[20][25]);
	void DrawMap();
	void AddTexture(const char* filename);

};