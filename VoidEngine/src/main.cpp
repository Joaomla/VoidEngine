#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[])
{
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0;

	game = new Game();

	game->init("BitchEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

	while (game->running())
	{
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();
		deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());

		game->handleEvents();
		game->update(deltaTime);
		game->render();
	}
	game->clean();
	return 0;
}