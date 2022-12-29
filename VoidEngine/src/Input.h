#pragma once

#include "SDL.h"
#include "Game.h"

class Input
{
private:
	// 322 - number of SDLK_DOWN events
	bool KEYS[322];
public:
	Input()
	{
		for (int x = 0; x < 322; x++)
		{
			KEYS[x] = false;
		}
	}

	/// <summary>
	/// Returns true in the frame the user presses the key
	/// </summary>
	/// <param name="keyEvent"></param>
	/// <returns></returns>
	static bool GetKeyDown(SDL_Keycode keyCode)
	{
		SDL_KeyboardEvent keyEvent = Game::event.key;
		return keyEvent.keysym.sym == keyCode && keyEvent.state == SDL_PRESSED;
	}
};