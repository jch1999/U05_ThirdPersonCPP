#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIController.generated.h"

class ACEnemy_AI;
class UCBehaviorComponent;
class UAIPerceptionComponent;
class UAISenseConfig_Sight;

UCLASS()
class THIREPERSONCPP_API ACAIController : public AAIController
{
	GENERATED_BODY()
public:
	ACAIController();

	float GetSightRadius();
	FORCEINLINE float GetBehaviorRange() { return BehaviorRange; }

public:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
		void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);
protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	UCBehaviorComponent* BehaviorComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	UAIPerceptionComponent* PerceptionComp;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Team")
	uint8 TeamID;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	bool bDrawRange;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float AdjustHeight;

	// diffent usage by Enemy Type 
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float BehaviorRange;

private:
	ACEnemy_AI* PossessedEnemy;
	UAISenseConfig_Sight* Sight;
};
