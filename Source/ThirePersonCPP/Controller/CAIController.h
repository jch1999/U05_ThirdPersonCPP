#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIController.generated.h"

class ACEnemy_AI;

UCLASS()
class THIREPERSONCPP_API ACAIController : public AAIController
{
	GENERATED_BODY()
public:
	ACAIController();

public:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	ACEnemy_AI* PossessedEnemy;
};
