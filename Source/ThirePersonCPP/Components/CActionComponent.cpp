#include "CActionComponent.h"
UCActionComponent::UCActionComponent()
{
}

void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCActionComponent::SetUnarmedMode()
{
	SetMode(EActionType::Unarmed);
}

void UCActionComponent::SetFistMode()
{
	SetMode(EActionType::Fist);
}

void UCActionComponent::SetOneHandMode()
{
	SetMode(EActionType::OneHand);
}

void UCActionComponent::SetTwoHandMode()
{
	SetMode(EActionType::TwoHand);
}

void UCActionComponent::SetMagicBallMode()
{
	SetMode(EActionType::MagicBall);
}

void UCActionComponent::SetWarpMode()
{
	SetMode(EActionType::Warp);
}

void UCActionComponent::SetWhirlWindMode()
{
	SetMode(EActionType::WhirlWind);
}

void UCActionComponent::SetMode(EActionType InNewType)
{
	if (Type == InNewType)
	{
		SetUnarmedMode();
		return;
	}

	EActionType PrevType = Type;
	Type = InNewType;

	ChangeType(PrevType, Type);
}

void UCActionComponent::ChangeType(EActionType InNewType)
{
	EActionType PrevType = Type;
	Type = InNewType;

	OnActionTypeChanged.BroadCast(PrevType, Type);
}
