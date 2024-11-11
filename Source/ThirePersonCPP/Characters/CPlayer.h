#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Interfaces/CCharacterInterface.h"
#include "Interfaces/CInteractableInterface.h"
#include "CPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UCAttributeComponent;
class UCOptionComponent;
class UCStateComponent;
class UCMontagesComponent;
class UCActionComponent;
class CKeyWidget;

UCLASS()
class THIREPERSONCPP_API ACPlayer : public ACharacter, public ICCharacterInterface, public ICInteractableInterface
{
	GENERATED_BODY()

public:
	ACPlayer();
	// Inherited via ICCharacterInterface
	virtual void SetBodyColor(FLinearColor InColor) override;

	// Inherited via ICCharacterInterface
	virtual EInteractType OnInteract() override;
	virtual EInteractType GetType() override;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

private:
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);
	void OnTurn(float Axis);
	void OnLookUp(float Axis);
	void OnZoom(float Axis);
	
	void OnEvade();
	void OnWalk();
	void OffWalk();

	void OnFist();
	void OnOneHand();
	void OnTwoHand();
	void OnMagicBall();
	void OnWarp();
	void OnWhirlWind();

	void OnInteracting();

private:
	void Begin_Roll();
	void Begin_Backstep();

	void RollingRotation();

public:
	void End_Roll();
	void End_Backstep();

	FORCEINLINE bool IsInteractable(EInteractType InType) { return Keys[(int32)InType]; }
private:
	UFUNCTION()
	void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCAttributeComponent* AttributeComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCOptionComponent* OptionComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCStateComponent* StateComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCMontagesComponent* MontagesComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCActionComponent* ActionComp;

	UPROPERTY(VisibleInstanceOnly,Category="Key")
	TArray<bool> Keys;

	UPROPERTY(EditDefaultsOnly, Category = "Key")
	TSubclassOf<CKeyWidget> KeyWidget;
private:
	UMaterialInstanceDynamic* BodyMaterial;
	UMaterialInstanceDynamic* LogoMaterial;
};
