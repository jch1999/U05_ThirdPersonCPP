#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/CInteractableInterface.h"
#include "CDoor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UMaterialInstanceDynamic;

UCLASS()
class THIREPERSONCPP_API ACDoor : public AActor, public ICInteractableInterface
{
	GENERATED_BODY()
	
public:	
	ACDoor();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;

public:
	virtual EInteractType OnInteract() override;
	virtual void FailInteract() override;
	virtual EInteractType GetType() override;
	virtual void SetInteracted() override;
	FORCEINLINE virtual bool IsInteracted() override { return bInteracted; }

private:
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UFUNCTION(BlueprintNativeEvent)
	void Open();
	void OpenLerp();

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USceneComponent* RootSceneComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* FrameMeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* DoorMeshComp;

	UPROPERTY(EditAnywhere, Category = "Color")
	FLinearColor Color;

	UPROPERTY(EditAnywhere, Category = "Interact")
	EInteractType Type;

private:
	UMaterialInstanceDynamic* FrameMaterial, * DoorMaterial;
	bool bInteracted;
	FTimerHandle OpenTimer;
	FRotator NowRot, TargetRot;
};
