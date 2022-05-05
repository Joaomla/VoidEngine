#pragma once
#include "../Object.h"

// forward declaration of Transform to break a circular dependency
struct Transform;

class Component : Object
{
public:
	Transform *transform;
};