#include "GameObject.h"

// Create new GameObject
GameObject::GameObject()
{
	if (registry == nullptr) return;
	// set a transform;
	transform = Transform();

	// create an entity for this gameObject
	entity = registry->create();
}