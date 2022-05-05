#pragma once
#include "../Object.h"
#include "Transform.h"

class Component : Object
{
public:
	Transform *transform;
};