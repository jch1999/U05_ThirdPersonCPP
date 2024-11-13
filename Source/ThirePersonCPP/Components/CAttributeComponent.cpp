#include "CAttributeComponent.h"

UCAttributeComponent::UCAttributeComponent()
{
	SneakSpeed = 200.0f;
	WalkSpeed = 400.0f;
	SprintSpeed = 600.0f;

	MaxHealth = 100.0f;

	bCanMove = true;
}

void UCAttributeComponent::BeginPlay()
{
	// Maybe this will be using in BP.
	CurrentHealth = MaxHealth;

	Super::BeginPlay();
}

void UCAttributeComponent::SetMove()
{
	bCanMove = true;
}

void UCAttributeComponent::SetStop()
{
	bCanMove = false;
}
