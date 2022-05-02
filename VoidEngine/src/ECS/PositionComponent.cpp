#include "PositionComponent.h"

Transform::Transform()
{
	xPos = 0;
	yPos = 0;
}
Transform::Transform(float x, float y)
{
	xPos = x;
	yPos = y;
}

void Transform::Init()
{
	xPos = 0;
	yPos = 0;
}

void Transform::Update()
{
	xPos++;
	yPos++;
}

void Transform::SetPos(float x, float y)
{
	xPos = x;
	yPos = y;
}