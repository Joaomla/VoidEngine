#include "SpriteComponent.h"

SpriteRenderer::SpriteRenderer(const char* path)
{
	texture = TextureManager::LoadTexture(path);
}

void SpriteRenderer::Init()
{
	position = &entity->getComponent<Transform>();
	srcRect.x = srcRect.y = 0;
	srcRect.w = srcRect.h = 32;
	destRect.w = destRect.h = 64;
}

void SpriteRenderer::Update()
{
	destRect.x = position->x();
	destRect.y = position->y();
}

void SpriteRenderer::Draw()
{
	TextureManager::Draw(texture, srcRect, destRect);
}