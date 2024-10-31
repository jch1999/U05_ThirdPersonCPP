#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance.generated.h"

UCLASS()
class THIREPERSONCPP_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeBeginPlay() override;

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Player")
	float Speed;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Player")
	float Direction;
};
