#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CProjectile.generated.h"

class USphereComponent;
class UParticleSystemComponent;
class UProjectileMovementComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FProjectileBeginOverlap, const FHitResult&, InHitResult);

UCLASS()
class THIREPERSONCPP_API ACProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ACProjectile();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void ProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USphereComponent* SphereComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UParticleSystemComponent* ParticleComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UProjectileMovementComponent* MovementComp;

public:
	UPROPERTY(BlueprintAssignable)
	FProjectileBeginOverlap OnProjectileBeginOverlap;
};
