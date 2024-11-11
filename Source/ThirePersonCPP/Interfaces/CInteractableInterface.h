#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CInteractableInterface.generated.h"

UENUM(BlueprintType)
enum class EInteractType :uint8
{
	None, Red, Green, Blue, MAX
};

UINTERFACE(MinimalAPI)
class UCInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

class THIREPERSONCPP_API ICInteractableInterface
{
	GENERATED_BODY()

public:
	virtual EInteractType OnInteract() = 0;
	virtual void FailInteract() = 0;
	virtual EInteractType GetType() = 0;
	virtual void SetInteracted() = 0;
	virtual bool IsInteracted() = 0;
};
