// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPatrolComponent.generated.h"

class ACPatrolPath;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIREPERSONCPP_API UCPatrolComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FORCEINLINE bool IsPathValid() { return PatrolPath != nullptr; }

	bool GetMoveTo(FVector& OutLocation);
	void UpdateNextIndex();

private:
	UPROPERTY(EditInstanceOnly, Category = "Path")
	ACPatrolPath* PatrolPath;

	UPROPERTY(EditInstanceOnly, Category = "Path")
	int32 Index;

	UPROPERTY(EditInstanceOnly, Category = "Path")
	bool bReverse;
};
