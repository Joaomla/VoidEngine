#include "GameObject.h"

// Create new GameObject
GameObject::GameObject()
{
	if (registry == nullptr) return;
	// create an entity for this gameObject
	entity = registry->create();

	// Add a transform component;
	transform = AddComponent<Transform>();
}