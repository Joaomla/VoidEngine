#pragma once
#include "../Math/Vector2.h"
#include "SDL.h"
#include "../TextureManager.h"
#include "Component.h"

struct SpriteRenderer : public Component
{
private:
	SDL_Texture* texture;
	SDL_Point textureSize = { 32,32 };
	SDL_Rect srcRect, destRect;

	/*
	Get the size of the loaded texture.

	texture - a pointer to the loaded texture
	*/
	SDL_Point GetTextureSize(SDL_Texture* texture);

public:
	/*
	Awake function
	*/
	void Init();

	/*
	Update function
	*/
	void Update();

	/*
	Draw function
	*/
	void Draw();

	/*
	Load a sprite from assets

	path - path to the sprite
	*/
	void LoadSprite(const char* path);
};