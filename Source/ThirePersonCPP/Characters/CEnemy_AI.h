#pragma once

#include "CoreMinimal.h"
#include "Characters/CEnemy.h"
#include "CEnemy_AI.generated.h"

class UBehaviorTree;
class UCPatrolComponent;

UCLASS()
class THIREPERSONCPP_API ACEnemy_AI : public ACEnemy
{
	GENERATED_BODY()
	
public:
	ACEnemy_AI();

public:
	FORCEINLINE UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCPatrolComponent* PatrolComp;

private:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;


};
