#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/CCharacterInterface.h"
#include "CEnemy.generated.h"

class UCAttributeComponent;
class UCStateComponent;
class UCMontagesComponent;
class UCActionComponent;
class UWidgetComponent;

UCLASS()
class THIREPERSONCPP_API ACEnemy : public ACharacter, public ICCharacterInterface
{
	GENERATED_BODY()

public:
	ACEnemy();

protected:
	virtual void BeginPlay() override;

public:
	// Inherited via ICCharacterInterface
	virtual void SetBodyColor(FLinearColor InColor);

protected:	
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCAttributeComponent* AttributeComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCStateComponent* StateComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCMontagesComponent* MontagesComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCActionComponent* ActionComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UWidgetComponent* NameWidgetComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UWidgetComponent* HealthWidgetComp;

private:
	UMaterialInstanceDynamic* BodyMaterial;
	UMaterialInstanceDynamic* LogoMaterial;
};
