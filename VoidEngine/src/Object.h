#pragma once
#include "entt/entity/registry.hpp"

class Object
{
public:
	// registry where the entities-components reside
	static entt::registry* registry;
};