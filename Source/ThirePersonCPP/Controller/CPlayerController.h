#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

class UUserWidget;

UCLASS()
class THIREPERSONCPP_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ACPlayerController();

protected:
	virtual void SetupInputComponent();

public:
	UFUNCTION(BlueprintCallable, Exec)
	void ToggleOptionMenu();

private:
	void EnableSelectActionWidget();
	void DisableSelectActionWidget();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> OptionMenuClass;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	UUserWidget* OptionMenu;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> SelectActionWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	UUserWidget* SelectActionWidget;
};
