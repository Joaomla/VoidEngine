#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"

using namespace std;

Map* map;

SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto& player(manager.addEntity());

Game::Game()
{}
Game::~Game()
{}

// Init function when the game starts
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;

	// make the game fullscreen using a flag
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// If the SDL is able to initiallize
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "Subsystems Initialized!..." << endl;

		// creates a new window
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		// if the window is successfully created
		if (window)
		{
			cout << "Window created!" << endl;
		}

		// create a rendering context for the window
		renderer = SDL_CreateRenderer(window, -1, 0);

		// the renderer is successfully created
		if (renderer)
		{
			// sets the render colour to white
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			cout << "Renderer created!" << endl;
		}

		// the game is currently running
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	//---------------------

	map = new Map();

	player.addComponent<Transform>();
	player.addComponent<SpriteRenderer>("assets/player3.png");
}

// handles game events
void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

// Update the game
void Game::update(double deltaTime)
{
	manager.refresh();
	manager.update();
}

// Render the game;
void Game::render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout << "Game Cleaned!" << endl;
}