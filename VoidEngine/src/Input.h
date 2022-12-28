#pragma once

#include "SDL.h"
#include "Game.h"

class Input
{
public:
	static bool GetKeyDown(SDL_Keycode keyEvent)
	{
		return Game::event.key.keysym.sym == keyEvent;
	}
};