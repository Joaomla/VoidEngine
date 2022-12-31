#pragma once
#include <string>
#include <SDL.h>
#include "Component.h"

class Collider : public Component
{
public:
	SDL_Rect collider;
	std::string tag;

	void init()
	{

	}
};