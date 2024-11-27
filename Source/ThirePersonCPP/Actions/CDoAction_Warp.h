#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "CDoAction_Warp.generated.h"

class USkeletalMeshComponent;

UCLASS()
class THIREPERSONCPP_API ACDoAction_Warp : public ACDoAction
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DelatTime) override;

public:
	virtual void PrimaryAction() override;
	virtual void Begin_PrimaryAction() override;
	virtual void End_PrimaryAction() override;

private:
	bool GetCursorLocation(FVector& OutLocation);
	void SetPreviewMeshColor(FLinearColor InColor);

private:
	USkeletalMeshComponent* PreviewMeshComp;
	FVector LocationToWarp;
};
