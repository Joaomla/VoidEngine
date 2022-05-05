#pragma once
#include "../Math/Vector2.h"
#include "Component.h"

struct Transform : Component
{
	Vector2 position = Vector2();
	Vector2 rotation = Vector2();
	Vector2 scale = Vector2();

	// rb stuff

	Vector2 velocity = Vector2();
	int speed = 3;
};