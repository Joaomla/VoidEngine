#include "Game.h"
#include "GameObject.h"
#include "Input.h"

using namespace std;

Map* map;

// Game renderer
SDL_Renderer* Game::renderer = nullptr;

// Game events
SDL_Event Game::event;

// entity component registry initialize
entt::registry Game::registry;

//GameObjects
GameObject player;

// Input
Input* input = new Input();
// keyboard state
const Uint8* keystate;

char playerSpriteFilename[] = "assets/player3.png";

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

	Object::registry = &registry;
	player = GameObject();

	map = new Map();

	player.AddComponent<SpriteRenderer>();

	player.GetComponent<SpriteRenderer>()->LoadSprite(playerSpriteFilename);
	player.GetComponent<SpriteRenderer>()->Init();
	//player.AddComponent<KeyboardController>();
}

// handles game events
void Game::handleEvents()
{
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
		}
	}
	
	// Get array of key states
	keystate = SDL_GetKeyboardState(NULL);
}

// Update the game
void Game::update(double deltaTime)
{
	//Vector2 playerPosition = player.GetComponent<Transform>()->position += Vector2(0.1f, 0.1f);
	player.GetComponent<SpriteRenderer>()->Update();
	Vector2 pposition = player.GetComponent<SpriteRenderer>()->transform->position;


	

	if (keystate[SDL_SCANCODE_W])
		player.GetComponent<Transform>()->position += Vector2(0, -1);

	if (keystate[SDL_SCANCODE_A])
		player.GetComponent<Transform>()->position += Vector2(-1, -0);

	if (keystate[SDL_SCANCODE_S])
		player.GetComponent<Transform>()->position += Vector2(0, 1);

	if (keystate[SDL_SCANCODE_D])
		player.GetComponent<Transform>()->position += Vector2(1, -0);
}

// Render the game;
void Game::render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();
	player.GetComponent<SpriteRenderer>()->Draw();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout << "Game Cleaned!" << endl;
}