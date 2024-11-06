#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CActionData.generated.h"

class UAnimMontage;
class ACEquipment;

USTRUCT(BlueprintType)
struct FEquipmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
	float PlayRate = 1.0f;

	UPROPERTY(EditAnywhere)
	bool bCanMove = true;

	UPROPERTY(EditAnywhere)
	bool bUseControlRotation = true;
};

UCLASS()
class THIREPERSONCPP_API UCActionData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	// Equipment
	UPROPERTY(EditAnywhere, Category = "Equipment")
	TSubclassOf<ACEquipment> EquipmentClass;

	UPROPERTY(EditAnywhere, Category = "Equipment")
	FEquipmentData EquipmentData;

private:
	ACEquipment* Equipment;
};
