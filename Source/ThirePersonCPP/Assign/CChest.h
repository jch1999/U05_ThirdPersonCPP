#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/CInteractableInterface.h"
#include "CChest.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UParticleSystemComponent;

UCLASS()
class THIREPERSONCPP_API ACChest : public AActor, public ICInteractableInterface
{
	GENERATED_BODY()
	
public:	
	ACChest();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;

public:
	virtual EInteractType OnInteract() override;
	virtual void FailInteract() override;
	virtual EInteractType GetType() override;
	virtual void SetInteracted();
	FORCEINLINE virtual bool IsInteracted() override { return bInteracted; }

private:
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UFUNCTION(BlueprintNativeEvent)
	void Open();

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USceneComponent* RootSceneComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* UpMeshComp;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* DownMeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* ParticleComp;

	UPROPERTY(EditAnywhere, Category = "Color")
	FLinearColor Emissive;

	UPROPERTY(EditAnywhere, Category = "Interact")
	EInteractType Type;

private:
	UMaterialInstanceDynamic* DownMaterial, * UpMaterial;
	bool bInteracted;
};
