#include "CDoor.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

ACDoor::ACDoor()
{
	// Root
	CHelpers::CreateSceneComponent(this, &RootSceneComp, "RootSceneComp");
	CheckNull(RootSceneComp);

	RootComponent = RootSceneComp;

	// Collsion
	CHelpers::CreateSceneComponent(this, &BoxComp, "BoxComp", RootComponent);
	CheckNull(BoxComp);

	BoxComp->SetRelativeScale3D(FVector(3));
	BoxComp->bHiddenInGame = false;

	// Mesh
	CHelpers::CreateSceneComponent(this, &FrameMeshComp, "FrameMeshComp", RootComponent);
	CheckNull(FrameMeshComp);
	CHelpers::CreateSceneComponent(this, &DoorMeshComp, "DoorMeshComp", FrameMeshComp);
	CheckNull(DoorMeshComp);

	UStaticMesh* FrameMeshAsset;
	UStaticMesh* DoorMeshAsset;

	CHelpers::GetAsset(&FrameMeshAsset, "/Game/Assignment/Door/Props/SM_DoorFrame");
	CHelpers::GetAsset(&DoorMeshAsset, "/Game/Assignment/Door/Props/SM_Door");
	CheckNull(FrameMeshAsset);
	FrameMeshComp->SetStaticMesh(FrameMeshAsset);
	FrameMeshComp->SetRelativeLocation(FVector(0, 0, -100));

	CheckNull(DoorMeshAsset);
	DoorMeshComp->SetStaticMesh(DoorMeshAsset);
	DoorMeshComp->SetRelativeLocation(FVector(0, 45, 0));

	Type = EInteractType::Red;
}

void ACDoor::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ACDoor::BeginOverlap);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &ACDoor::EndOverlap);

	UMaterialInstanceDynamic* FrameMaterial = UMaterialInstanceDynamic::Create(FrameMeshComp->GetMaterial(0), nullptr);
	UMaterialInstanceDynamic* DoorMaterial = UMaterialInstanceDynamic::Create(DoorMeshComp->GetMaterial(0), nullptr);
	CheckNull(FrameMaterial);
	CheckNull(DoorMaterial);

	FrameMeshComp->SetMaterial(0, FrameMaterial);
	DoorMeshComp->SetMaterial(0, DoorMaterial);
	FrameMaterial->SetVectorParameterValue("Color", Color);
	DoorMaterial->SetVectorParameterValue("ColorDoor", Color);
}

EInteractType ACDoor::OnInteract()
{
	Open();

	return EInteractType::None;
}

EInteractType ACDoor::GetType()
{
	return Type;
}

void ACDoor::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FString msg = "Press F to Open. You must have a ";
	switch (Type)
	{
	case EInteractType::Red:
		msg.Append("Red Key.");
		break;
	case EInteractType::Blue:
		msg.Append("Blue Key.");
		break;
	case EInteractType::Green:
		msg.Append("Green Key.");
		break;
	}

	DrawDebugString(GetWorld(), GetActorLocation(), msg, 0, FColor::White, 2.0f);
}

void ACDoor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void ACDoor::Open()
{
	DoorMeshComp->AddRelativeRotation(FRotator(0, -90, 0));
}
