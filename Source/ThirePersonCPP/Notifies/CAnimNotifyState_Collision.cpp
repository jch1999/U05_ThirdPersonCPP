#include "CAnimNotifyState_Collision.h"
#include "global.h"
#include "Actions/CAttachment.h"
#include "Actions/CDoAction.h"
#include "Actions/CDoAction_Melee.h"
#include "Actions/CActionObject.h"
#include "Components/CActionComponent.h"

FString UCAnimNotifyState_Collision::GetNotifyName_Implementation() const
{
	return "Collision";
}

void UCAnimNotifyState_Collision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(ActionComp);
	
	UCActionObject* ActionObject = ActionComp->GetCurrentDataObject();
	CheckNull(ActionObject);

	ACAttachment* Attachment = ActionObject->GetAttachment();
	CheckNull(Attachment);

	Attachment->OnCollision();
}

void UCAnimNotifyState_Collision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(ActionComp);

	UCActionObject* ActionObject = ActionComp->GetCurrentDataObject();
	CheckNull(ActionObject);

	ACAttachment* Attachment = ActionObject->GetAttachment();
	CheckNull(Attachment);

	Attachment->OffCollision();

	ACDoAction_Melee* Melee = Cast<ACDoAction_Melee>(ActionObject->GetDoAction());
	CheckNull(Melee);

	Melee->ClearHittedCharacters();
}
