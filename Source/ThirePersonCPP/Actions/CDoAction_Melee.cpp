#include "CDoAction_Melee.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CAttributeComponent.h"

void ACDoAction_Melee::PrimaryAction()
{
	Super::PrimaryAction();

	CheckFalse(Datas.Num() > 0);
	
	// Combo Attack
	if (bCanCombo)
	{
		bCanCombo = false;
		bSuccessCombo = true;
		return;
	}

	// First Attack
	CheckFalse(StateComp->IsIdleMode());
	StateComp->SetActionMode();
	OwnerCharacter->PlayAnimMontage(Datas[0].Montage, Datas[0].PlayRate, Datas[0].StartSection);

	Datas[0].bCanMove ? AttributeComp->SetMove() : AttributeComp->SetStop();
}

void ACDoAction_Melee::Begin_PrimaryAction()
{
	Super::Begin_PrimaryAction();

	// Play NextCombo
	CheckFalse(bSuccessCombo);

	bSuccessCombo = false;

	OwnerCharacter->StopAnimMontage();
	++ComboCnt;
	ComboCnt = FMath::Clamp(ComboCnt, 0, Datas.Num() - 1);

	OwnerCharacter->PlayAnimMontage(Datas[ComboCnt].Montage, Datas[ComboCnt].PlayRate, Datas[ComboCnt].StartSection);
	Datas[ComboCnt].bCanMove ? AttributeComp->SetMove() : AttributeComp->SetStop();
}

void ACDoAction_Melee::End_PrimaryAction()
{
	Super::End_PrimaryAction();

	OwnerCharacter->StopAnimMontage(Datas[ComboCnt].Montage);
	ComboCnt = 0;

	StateComp->SetIdleMode();
	AttributeComp->SetMove();
}

void ACDoAction_Melee::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InCauser, InOtherCharacter);
	
	// Check Multiple Hit
	int32 PrevHittedCnt = HittedCharacters.Num();
	HittedCharacters.AddUnique(InOtherCharacter);
	CheckFalse(PrevHittedCnt < HittedCharacters.Num());

	// Hit Stop
	float HitStop = Datas[ComboCnt].HitStop;
	if (!FMath::IsNearlyZero(HitStop))
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 2e-2f);
		UKismetSystemLibrary::K2_SetTimer(this, "RestoreGlobalTimerDeilation", HitStop * 2e-2f, false);
	}

	// Spawn Impact Effect
	UParticleSystem* ImpactEffect = Datas[ComboCnt].Effect;
	if (ImpactEffect)
	{
		FTransform TM = Datas[ComboCnt].EffectTransform;
		TM.AddToTranslation(InOtherCharacter->GetActorLocation());
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, TM);
	}

	// Play CameraShake
	TSubclassOf<UCameraShake> ShakeClass = Datas[ComboCnt].CameraShakeClass;
	if (ShakeClass)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PC)
		{
			PC->PlayerCameraManager->PlayCameraShake(ShakeClass);
		}
	}
	FDamageEvent DamagedEvent;
	InOtherCharacter->TakeDamage(Datas[ComboCnt].Damage, DamagedEvent, InAttacker->GetController(), InCauser);
}

void ACDoAction_Melee::OnAttachmentEndOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentEndOverlap(InAttacker, InCauser, InOtherCharacter);
}

void ACDoAction_Melee::EnableCombo()
{
	bCanCombo = true;
}

void ACDoAction_Melee::DisableCombo()
{
	bCanCombo = false;
}

void ACDoAction_Melee::ClearHittedCharacters()
{
	HittedCharacters.Empty();
}

void ACDoAction_Melee::RestoreGlobalTimerDeilation()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
}
