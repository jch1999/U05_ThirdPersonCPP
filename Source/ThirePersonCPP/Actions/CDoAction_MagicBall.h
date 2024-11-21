#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "CDoAction_MagicBall.generated.h"

class UCAim;

UCLASS()
class THIREPERSONCPP_API ACDoAction_MagicBall : public ACDoAction
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

public:
	virtual void PrimaryAction() override;
	virtual void Begin_PrimaryAction() override;
	virtual void End_PrimaryAction() override;

private:
	UPROPERTY()
	UCAim* Aim;
};
