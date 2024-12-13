#include "CPlayerController.h"
#include "Global.h"
#include "Blueprint/UserWidget.h"

ACPlayerController::ACPlayerController()
{
	
}

void ACPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	StateComp = CHelpers::GetComponent<UCStateComponent>(InPawn);
	StateComp->OnStateTypeChanged.AddDynamic(this, &ACPlayerController::DisableAtDead);
}

void ACPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("OptionMenu", IE_Pressed, this, &ACPlayerController::ToggleOptionMenu);

	InputComponent->BindAction("SelectAction", IE_Pressed, this, &ACPlayerController::EnableSelectActionWidget);
	InputComponent->BindAction("SelectAction", IE_Released, this, &ACPlayerController::DisableSelectActionWidget);
}

void ACPlayerController::ToggleOptionMenu()
{
	CheckNull(OptionMenuClass);

	if (OptionMenu && OptionMenu->IsInViewport())
	{
		OptionMenu->RemoveFromParent();
		OptionMenu = nullptr;

		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());
		return;
	}

	OptionMenu = CreateWidget<UUserWidget>(this, OptionMenuClass);
	CheckNull(OptionMenu);

	OptionMenu->AddToViewport(100);

	bShowMouseCursor = true;
	SetInputMode(FInputModeGameAndUI());

	// 1. 실제 WB 메뉴가 없음
	// 2. GM에 PC를 등록해야 한다
}

void ACPlayerController::EnableSelectActionWidget()
{
	if (StateComp)
	{
		CheckTrue(StateComp->IsDeadMode() || !(StateComp->IsIdleMode()));
	}

	if (!SelectActionWidget)
	{
		SelectActionWidget = CreateWidget(this, SelectActionWidgetClass);
	}

	if (SelectActionWidget)
	{
		SelectActionWidget->AddToViewport();

		bShowMouseCursor = true;
		SetInputMode(FInputModeGameAndUI());
	}
}

void ACPlayerController::DisableSelectActionWidget()
{
	if (SelectActionWidget && SelectActionWidget->IsInViewport())
	{
		SelectActionWidget->RemoveFromParent();
		SelectActionWidget = nullptr;

		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());
	}
}

void ACPlayerController::DisableAtDead(EStateType InPrevType, EStateType InNewType)
{
	CheckFalse(InNewType==EStateType::Dead)
	DisableSelectActionWidget();
}
