#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/CCharacterInterface.h"
#include "Components/CStateComponent.h"
#include "Components/TimeLineComponent.h"
#include "CEnemy.generated.h"

class UCAttributeComponent;
class UCStateComponent;
class UCMontagesComponent;
class UCActionComponent;
class UWidgetComponent;
class UCurveFloat;

UCLASS()
class THIREPERSONCPP_API ACEnemy : public ACharacter, public ICCharacterInterface
{
	GENERATED_BODY()

public:
	ACEnemy();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	// Inherited via ICCharacterInterface
	virtual void SetBodyColor(FLinearColor InColor);
	
private:
	UFUNCTION()
	void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

	void Hitted() override;
	void Dead() override;

	UFUNCTION()
	void RestoreBodyColor();

	UFUNCTION()
	void OnProgressDissolve(float OutPut);

	UFUNCTION()
	void OnFinishDissolve();

protected:	
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
	UCAttributeComponent* AttributeComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCStateComponent* StateComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCMontagesComponent* MontagesComp;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
	UCActionComponent* ActionComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UWidgetComponent* NameWidgetComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UWidgetComponent* HealthWidgetComp;

	UPROPERTY(EditAnywhere, Category = "Debug")
	bool bVisibleNameWidget;

	UPROPERTY(EditAnywhere, Category = "Hitted")
	float LaunchValue;

	UPROPERTY(EditAnywhere, Category = "Dissolve")
	UCurveFloat* DissolveCurve;

private:
	AController* DamageInstigator;
	float DamageValue;

	UMaterialInstanceDynamic* BodyMaterial;
	UMaterialInstanceDynamic* LogoMaterial;

	UPROPERTY(VisibleAnywhere)
	UMaterialInstanceDynamic* DissolveMaterial;

	FTimeline DissolveTimeline;
};
