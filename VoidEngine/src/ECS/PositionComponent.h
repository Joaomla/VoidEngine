#pragma once
#include "Components.h"

class Transform : public Component
{
private:
	float xPos;
	float yPos;

public:
	Transform();
	Transform(float x, float y);

	float x() { return xPos; }
	float y() { return yPos; }

	void Init() override;

	void Update() override;

	void SetPos(float x, float y);
};