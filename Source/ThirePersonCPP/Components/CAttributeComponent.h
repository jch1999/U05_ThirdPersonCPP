#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CAttributeComponent.generated.h"

UENUM(BlueprintType)
enum class EWalkSpeedType: uint8
{
	Sneak, Walk, Sprint, Max
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIREPERSONCPP_API UCAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCAttributeComponent();
	
protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetCurrentHealth() { return CurrentHealth; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetMaxHealth() { return MaxHealth; }

	FORCEINLINE float GetSneakSpeed() { return WalkSpeeds[(int32)EWalkSpeedType::Sneak]; }
	FORCEINLINE float GetWalkSpeed() { return WalkSpeeds[(int32)EWalkSpeedType::Walk]; }
	FORCEINLINE float GetSprintSpeed() { return WalkSpeeds[(int32)EWalkSpeedType::Sprint]; }
	FORCEINLINE bool IsCanMove() { return bCanMove; }

	void SetMove();
	void SetStop();
	void SetSpeed(EWalkSpeedType InType);

	void IncreaseHealth(float InAmount);
	void DecreaseHealth(float InAmount);

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Health")
	float MaxHealth;

	UPROPERTY(EditDefaultsOnly, Category = "Speed")
	float WalkSpeeds[(int32)EWalkSpeedType::Max];

private:
	float CurrentHealth;
	bool bCanMove;
};
