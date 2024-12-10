#include "CAttributeComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UCAttributeComponent::UCAttributeComponent()
{
	WalkSpeeds[(int32)EWalkSpeedType::Sneak] = 200.0f;
	WalkSpeeds[(int32)EWalkSpeedType::Walk] = 400.0f;
	WalkSpeeds[(int32)EWalkSpeedType::Sprint] = 600.0f;

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

void UCAttributeComponent::SetSpeed(EWalkSpeedType InType)
{
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	CheckNull(OwnerCharacter);

	OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = WalkSpeeds[(int32)InType];
}

void UCAttributeComponent::IncreaseHealth(float InAmount)
{
	CurrentHealth += InAmount;
	CurrentHealth=FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);

	OnHealthChanged.Broadcast();
}

void UCAttributeComponent::DecreaseHealth(float InAmount)
{
	CurrentHealth -= InAmount;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);

	OnHealthChanged.Broadcast();
}
