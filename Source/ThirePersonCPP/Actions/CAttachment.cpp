#include "CAttachment.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/ShapeComponent.h"

ACAttachment::ACAttachment()
{
	CHelpers::CreateSceneComponent(this, &RootComp, "RootComp");
}

void ACAttachment::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	
	GetComponents<UShapeComponent>(ShapeComponents);

	for (const auto& Comp : ShapeComponents)
	{
		Comp->OnComponentBeginOverlap.AddDynamic(this, &ACAttachment::OnComponentBeginOverlap);
		Comp->OnComponentEndOverlap.AddDynamic(this, &ACAttachment::OnComponentEndOverlap);
	}
	
	OffCollision();

	Super::BeginPlay();
}

void ACAttachment::ActorAttachTo(FName InSocketName)
{
	// AActor::AttachToComponent
	AttachToComponent
	(
		OwnerCharacter->GetMesh(), 
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), 
		InSocketName
	);
}

void ACAttachment::ComponentAttachTo(USceneComponent* InComp, FName InSocketName)
{
	// USceneComponent::AttachToComponent
	InComp->AttachToComponent
	(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		InSocketName
	);
}

void ACAttachment::OnCollision()
{
	for (const auto& Comp : ShapeComponents)
	{
		Comp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

void ACAttachment::OffCollision()
{
	for (const auto& Comp : ShapeComponents)
	{
		Comp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ACAttachment::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckTrue(OwnerCharacter == OtherActor);
	CheckTrue(OwnerCharacter->GetClass() == OtherActor->GetClass());
	// CEnemy, BP_CEnemy_Dummy, BP_CEnemy_Melee. these are not recognized in the same class.

	ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
	if (OwnerCharacter && OtherCharacter)
	{
		OnAttachmentBeginOverlap.Broadcast(OwnerCharacter, this, OtherCharacter);
	}
}

void ACAttachment::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
	if (OwnerCharacter && OtherCharacter)
	{
		OnAttachmentEndOverlap.Broadcast(OwnerCharacter, this, OtherCharacter);
	}
}
