#pragma once
#include "Object.h"
#include "ECS/Transform.h"


class GameObject : Object
{
private:
	// transform of this gameObject
	Transform transform;

	// entity that corresponds to this gameObject
	entt::entity entity;

public:
	GameObject();

	template<typename T1>
	T1* AddComponent()
	{
		if (registry == nullptr) return nullptr;

		// it's added a component to the entity corresponding to this GameObject
		// and it is returned a pointer to that component
		return &(registry->emplace<T1>(entity));
	}

	template<typename T1>
	T1* GetComponent()
	{
		if (registry == nullptr) return nullptr;

		// returns the pointer to the component, if it exists.
		// else, returns null
		return &(registry->get<T1>(entity));
	}
};