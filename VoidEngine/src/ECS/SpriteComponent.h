#pragma once
#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"

class Transform;

class SpriteRenderer : public Component
{
private:
	Transform* position;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

public:
	SpriteRenderer() = default;
	SpriteRenderer(const char* path);
	void Init();
	void Update();
	void Draw();
};