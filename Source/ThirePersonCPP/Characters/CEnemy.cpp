#include "CEnemy.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/CAttributeComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CMontagesComponent.h"
#include "Components/CActionComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UI/CNameWidget.h"
#include "UI/CHealthWidget.h"

ACEnemy::ACEnemy()
{
	//MeshComp
	USkeletalMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Character/Mesh/SK_Mannequin");
	GetMesh()->SetSkeletalMesh(MeshAsset);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	// Animation
	TSubclassOf<UAnimInstance> AnimClass;
	CHelpers::GetClass(&AnimClass, "/Game/Enemies/ABP_CEnemy");
	GetMesh()->SetAnimInstanceClass(AnimClass);

	// Action Comp
	CHelpers::CreateActorComponent(this, &ActionComp, "ActionComp");

	// Montage Comp
	CHelpers::CreateActorComponent(this, &MontagesComp, "MontagesComp");

	// Attribute Comp
	CHelpers::CreateActorComponent(this, &AttributeComp, "AttributeComp");

	// State Comp
	CHelpers::CreateActorComponent(this, &StateComp, "StateComp");

	// Widget Comp
	CHelpers::CreateSceneComponent(this, &NameWidgetComp, "NameWidgetComp", GetMesh());
	CHelpers::CreateSceneComponent(this, &HealthWidgetComp, "HealthWidgetComp", GetMesh());
	
	// -> Name Widget
	TSubclassOf<UCNameWidget> NameWidgetClass;
	CHelpers::GetClass(&NameWidgetClass, "/Game/UI/WB_Name");
	if (NameWidgetClass)
	{
		NameWidgetComp->SetWidgetClass(NameWidgetClass);
		NameWidgetComp->SetRelativeLocation(FVector(0, 0, 240));
		NameWidgetComp->SetDrawSize(FVector2D(240, 30));
		NameWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
	}

	// -> Health Widget
	TSubclassOf<UCHealthWidget> HealthWidgetClass;
	CHelpers::GetClass(&HealthWidgetClass, "/Game/UI/WB_Health");
	if (HealthWidgetClass)
	{
		HealthWidgetComp->SetWidgetClass(HealthWidgetClass);
		HealthWidgetComp->SetRelativeLocation(FVector(0, 0, 190));
		HealthWidgetComp->SetDrawSize(FVector2D(120, 20));
		HealthWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
	}

	// Movement Comp
	GetCharacterMovement()->MaxWalkSpeed = AttributeComp->GetSprintSpeed();
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
}

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();

	//Set Dynamic Material
	BodyMaterial = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(0), nullptr);
	LogoMaterial = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(1), nullptr);

	GetMesh()->SetMaterial(0, BodyMaterial);
	GetMesh()->SetMaterial(1, LogoMaterial);


	// On StateType Changed
	ActionComp->SetUnarmedMode();

	// Widget Settings
	NameWidgetComp->InitWidget();
	UCNameWidget* NameWidget = Cast<UCNameWidget>(NameWidgetComp->GetUserWidgetObject());
	if (NameWidget)
	{
		NameWidget->SetNameText(GetController()->GetName(), GetName());
	}

	HealthWidgetComp->InitWidget();
	UCHealthWidget* HealthWidget = Cast<UCHealthWidget>(HealthWidgetComp->GetUserWidgetObject());
	if (NameWidget)
	{
		HealthWidget->Update(AttributeComp->GetCurrentHealth(),AttributeComp->GetMaxHealth());
	}
}

void ACEnemy::SetBodyColor(FLinearColor InColor)
{
	BodyMaterial->SetVectorParameterValue("BodyColor", InColor);
	LogoMaterial->SetVectorParameterValue("BodyColor", InColor);
}

