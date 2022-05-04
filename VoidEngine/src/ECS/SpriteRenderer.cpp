#include "SpriteRenderer.h"

void SpriteRenderer::LoadSprite(const char* path)
{
	texture = TextureManager::LoadTexture(path);
	textureSize = GetTextureSize(texture);
}

SDL_Point SpriteRenderer::GetTextureSize(SDL_Texture* texture) {
	SDL_Point size;
	SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
	return size;
}

void SpriteRenderer::Init(Transform *transform)
{
	this->transform = transform;

	srcRect.x = srcRect.y = 0;

	// source rect is the same size as the sprite
	srcRect.w = textureSize.x;
	srcRect.h = textureSize.y;

	// destination rect is what is the area in the screen
	destRect.w = destRect.h = 128;
}

void SpriteRenderer::Update()
{
	destRect.x = transform->position.x;
	destRect.y = transform->position.y;
}

void SpriteRenderer::Draw()
{
	TextureManager::Draw(texture, srcRect, destRect);
}