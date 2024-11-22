#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CHUD.generated.h"

class UTexture2D;

UCLASS()
class THIREPERSONCPP_API ACHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ACHUD();

	virtual void DrawHUD() override;

public:
	void EnableAimTexture();
	void DisableAimTexture();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Aim")
	UTexture2D* AimTexture;

private:
	bool bDrawAimTexture;
};
