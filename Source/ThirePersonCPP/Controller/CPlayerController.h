#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Components/CStateComponent.h"
#include "CPlayerController.generated.h"

class UUserWidget;

UCLASS()
class THIREPERSONCPP_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ACPlayerController();

public:
	virtual void OnPossess(APawn* InPawn) override;

protected:
	virtual void SetupInputComponent();

public:
	UFUNCTION(BlueprintCallable, Exec)
	void ToggleOptionMenu();

private:
	void EnableSelectActionWidget();
	void DisableSelectActionWidget();

	UFUNCTION()
	void DisableAtDead(EStateType InPrevType, EStateType InNewType);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> OptionMenuClass;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	UUserWidget* OptionMenu;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> SelectActionWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	UUserWidget* SelectActionWidget;

	UPROPERTY()
	UCStateComponent* StateComp;
};
