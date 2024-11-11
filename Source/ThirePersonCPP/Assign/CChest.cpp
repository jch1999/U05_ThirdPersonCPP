#include "CChest.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Materials/MaterialInstanceDynamic.h"

ACChest::ACChest()
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
	CHelpers::CreateSceneComponent(this, &DownMeshComp, "DownMeshComp", RootComponent);
	CheckNull(DownMeshComp);
	CHelpers::CreateSceneComponent(this, &UpMeshComp, "UpMeshComp", DownMeshComp);
	CheckNull(UpMeshComp);

	UStaticMesh* UpMeshAsset;
	UStaticMesh* DownMeshAsset;

	CHelpers::GetAsset(&UpMeshAsset, "/Game/Assignment/Chest/SM_ChestTop");
	CHelpers::GetAsset(&DownMeshAsset, "/Game/Assignment/Chest/SM_ChestBottom");
	CheckNull(UpMeshAsset);
	UpMeshComp->SetStaticMesh(UpMeshAsset);

	CheckNull(DownMeshAsset);
	DownMeshComp->SetStaticMesh(DownMeshAsset);
	DownMeshComp->SetRelativeLocation(FVector(-40, 0, -30));

	// Particle
	CHelpers::CreateSceneComponent(this, &ParticleComp, "ParticleComp",RootComponent);
	CheckNull(ParticleComp);

	UParticleSystem* Particle;
	CHelpers::GetAsset<UParticleSystem>(&Particle, "/Game/InfinityBladeEffects/Effects/FX_Skill_Aura/P_Aura_Default_Upheaval_01");
	CheckNull(Particle)
	ParticleComp->SetTemplate(Particle);
	ParticleComp->bAutoActivate = false;

	bInteracted = false;
	Type = EInteractType::Red;
}

void ACChest::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (!DownMaterial || !UpMaterial)
	{
		DownMaterial = UMaterialInstanceDynamic::Create(DownMeshComp->GetMaterial(0), nullptr);
		UpMaterial = UMaterialInstanceDynamic::Create(UpMeshComp->GetMaterial(0), nullptr);
		CheckNull(DownMaterial);
		CheckNull(UpMaterial);

		DownMeshComp->SetMaterial(0, DownMaterial);
		UpMeshComp->SetMaterial(0, UpMaterial);
	}
	/*CHelpers::GetAssetDynamic(&Material, "/Game/Assignment/Chest/MI_Chest");
	CHelpers::GetAssetDynamic(&DownMaterial, "/Game/Assignment/Chest/MI_Chest");
	CHelpers::GetAssetDynamic(&UpMaterial, "/Game/Assignment/Chest/MI_Chest");*/

	DownMaterial->SetVectorParameterValue("Emissive", Emissive);
	UpMaterial->SetVectorParameterValue("Emissive", Emissive);
}
void ACChest::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ACChest::BeginOverlap);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &ACChest::EndOverlap);
}

EInteractType ACChest::OnInteract()
{
	if (bInteracted) return EInteractType::None;

	Open();
	SetInteracted();

	return Type;
}

void ACChest::FailInteract()
{
	return;
}

EInteractType ACChest::GetType()
{
	return EInteractType::None;
}

void ACChest::SetInteracted()
{
	bInteracted = true;
}

void ACChest::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FString msg = "Prees F to Interact!";
	DrawDebugString(GetWorld(), GetActorLocation(), msg, 0, FColor::White, 2.0f);
}

void ACChest::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void ACChest::Open()
{
	UpMeshComp->AddRelativeRotation(FRotator(110, 0, 0));
	UpMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ParticleComp->Activate();
}
