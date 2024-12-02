#include "CBehaviorComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/CPlayer.h"

UCBehaviorComponent::UCBehaviorComponent()
{
}

void UCBehaviorComponent::SetBlackboardComponent(UBlackboardComponent* InBlackboardComp)
{
	BlackboardComp = InBlackboardComp;
}

bool UCBehaviorComponent::IsWaitMode()
{
	return GetType() == EBehaviorType::Wait;
}

bool UCBehaviorComponent::IsApproachMode()
{
	return GetType() == EBehaviorType::Approach;
}

bool UCBehaviorComponent::IsActionMode()
{
	return GetType() == EBehaviorType::Action;
}

bool UCBehaviorComponent::IsPatrolMode()
{
	return GetType() == EBehaviorType::Patrol;
}

bool UCBehaviorComponent::IsHittedMode()
{
	return GetType() == EBehaviorType::Hitted;
}

bool UCBehaviorComponent::IsRunAwayMode()
{
	return GetType() == EBehaviorType::RunAway;
}

void UCBehaviorComponent::SetWiatMode()
{
	ChangeType(EBehaviorType::Wait);
}

void UCBehaviorComponent::SetApproachMode()
{
	ChangeType(EBehaviorType::Approach);
}

void UCBehaviorComponent::SetActionMode()
{
	ChangeType(EBehaviorType::Action);
}

void UCBehaviorComponent::SetPatrolMode()
{
	ChangeType(EBehaviorType::Patrol);
}

void UCBehaviorComponent::SetHittedMode()
{
	ChangeType(EBehaviorType::Hitted);
}

void UCBehaviorComponent::SetRunAwayMode()
{
	ChangeType(EBehaviorType::RunAway);
}

ACPlayer* UCBehaviorComponent::GetPlayerValue()
{
	return Cast<ACPlayer>(BlackboardComp->GetValueAsObject(PlayerKeyName));
}

FVector UCBehaviorComponent::GetLocationValue()
{
	return BlackboardComp->GetValueAsVector(LocationKeyName);
}

EBehaviorType UCBehaviorComponent::GetType()
{
	return (EBehaviorType)(BlackboardComp->GetValueAsEnum(BehaviorKeyName));
}

void UCBehaviorComponent::ChangeType(EBehaviorType InNewType)
{
	BlackboardComp->SetValueAsEnum(BehaviorKeyName, (uint8)InNewType);

	//OnBehaviorTypeChanged.Broadcast(Prev, InNewType);
}
