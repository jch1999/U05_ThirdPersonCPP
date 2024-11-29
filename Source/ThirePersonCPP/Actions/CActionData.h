#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CActionData.generated.h"

class UAnimMontage;
class ACharacter;
class ACEquipment;
class ACAttachment;
class ACDoAction;
class UParticleSystem;
class UCameraShake;
class ACProjectile;
class UCActionObject;

// ----------------------------------------------------------------------------
// struct FEquipmentData
// ----------------------------------------------------------------------------
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
	FName StartSection;

	UPROPERTY(EditAnywhere)
	bool bCanMove = true;

	UPROPERTY(EditAnywhere)
	bool bUseControlRotation = true;
};

// ----------------------------------------------------------------------------
// struct FActionData
// ----------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FActionData : public FEquipmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float Damage = 5.0f;

	UPROPERTY(EditAnywhere)
	float HitStop;
	
	UPROPERTY(EditAnywhere)
	UParticleSystem* Effect;

	UPROPERTY(EditAnywhere)
	FTransform EffectTransform;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraShake> CameraShakeClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ACProjectile> ProjectileClass;
};

// ----------------------------------------------------------------------------
// class UCActionData
// ----------------------------------------------------------------------------
UCLASS()
class THIREPERSONCPP_API UCActionData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	void BeginPlay(ACharacter* InOwnerCharacter, UCActionObject** OutActionObject);

private:
	FString MakeLabel(ACharacter* InOwnerCharacter,FString InMiddleName);

public:
	// Equipment
	UPROPERTY(EditAnywhere, Category = "Equipment")
	TSubclassOf<ACEquipment> EquipmentClass;

	UPROPERTY(EditAnywhere, Category = "Equipment")
	FLinearColor EquipmentColor;

	UPROPERTY(EditAnywhere, Category = "Equipment")
	FEquipmentData EquipmentData;

	// Attachment
	UPROPERTY(EditAnywhere, Category = "Attachment")
	TSubclassOf<ACAttachment> AttachmentClass;

	// DoAction
	UPROPERTY(EditAnywhere, Category = "DoAction")
	TSubclassOf<ACDoAction> DoActionClass;
	
	UPROPERTY(EditAnywhere, Category = "DoAction")
	TArray<FActionData> DoActionDatas;
};
