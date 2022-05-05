#include "Object.h"

// initialize with null pointer or else a linker error happens
entt::registry* Object::registry = nullptr;