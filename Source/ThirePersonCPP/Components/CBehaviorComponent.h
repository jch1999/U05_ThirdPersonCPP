// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CBehaviorComponent.generated.h"

class UBlackboardComponent;
class ACPlayer;

UENUM(BlueprintType)
enum class EBehaviorType : uint8
{
	Wait, Approach, Action, Patrol, Hitted, RunAway,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIREPERSONCPP_API UCBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCBehaviorComponent();

public:
	void SetBlackboardComponent(UBlackboardComponent* InBlackboardComp);

	UFUNCTION(BlueprintPure)
	bool IsWaitMode();

	UFUNCTION(BlueprintPure)
	bool IsApproachMode();

	UFUNCTION(BlueprintPure)
	bool IsActionMode();

	UFUNCTION(BlueprintPure)
	bool IsPatrolMode();

	UFUNCTION(BlueprintPure)
	bool IsHittedMode();

	UFUNCTION(BlueprintPure)
	bool IsRunAwayMode();

	void SetWaitMode();

	void SetApproachMode();

	void SetActionMode();

	void SetPatrolMode();

	void SetHittedMode();

	void SetRunAwayMode();

	ACPlayer* GetPlayerValue();
	
	FVector GetLocationValue();

private:
	EBehaviorType GetType();

	void ChangeType(EBehaviorType InNewType);

private:
	UPROPERTY(EditDefaultsOnly, Category = "BlackboardKeyName")
	FName PlayerKeyName = "PlayerKey";
	
	UPROPERTY(EditDefaultsOnly, Category = "BlackboardKeyName")
	FName LocationKeyName = "LocationKey";

	UPROPERTY(EditDefaultsOnly, Category = "BlackboardKeyName")
	FName BehaviorKeyName = "BehaviorKey";

private:	
	UBlackboardComponent* BlackboardComp;
};