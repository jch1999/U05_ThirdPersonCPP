#include "COptionComponent.h"

UCOptionComponent::UCOptionComponent()
{
	MouseXSpeed = 90.0f;
	MouseYSpeed = 90.0f;
}

void UCOptionComponent::SetMouseXSpeed(float InSpeed)
{
	MouseXSpeed = InSpeed;
}

void UCOptionComponent::SetMouseYSpeed(float InSpeed)
{
	MouseYSpeed = InSpeed;
}
