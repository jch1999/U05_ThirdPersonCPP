#include "CActionData.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "CEquipment.h"
#include "CAttachment.h"
#include "CDoAction.h"
#include "CActionObject.h"

void UCActionData::BeginPlay(ACharacter* InOwnerCharacter, UCActionObject** OutActionObject)
{
	CheckNull(InOwnerCharacter);

	ACAttachment* Attachment = nullptr;
	if (AttachmentClass)
	{
		FTransform TM;

		Attachment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACAttachment>(AttachmentClass, TM, InOwnerCharacter, nullptr);
		Attachment->SetActorLabel(MakeLabel(InOwnerCharacter, "Attachment"));
		Attachment->FinishSpawning(TM);
	}

	ACEquipment* Equipment = nullptr;
	if (EquipmentClass)
	{
		FTransform TM;

		Equipment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACEquipment>(EquipmentClass, TM, InOwnerCharacter, nullptr);
		Equipment->SetData(EquipmentData);
		Equipment->SetColor(EquipmentColor);
		Equipment->SetActorLabel(MakeLabel(InOwnerCharacter, "Equipment"));
		Equipment->FinishSpawning(TM);

		if (Attachment)
		{
			Equipment->OnEquipmentDelegate.AddDynamic(Attachment, &ACAttachment::OnEquip);
			Equipment->OnUnequipmentDelegate.AddDynamic(Attachment, &ACAttachment::OnUnequip);
		}
	}

	ACDoAction* DoAction = nullptr;
	if (DoActionClass)
	{
		FTransform TM;

		DoAction = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACDoAction>(DoActionClass, TM, InOwnerCharacter, nullptr);
		DoAction->SetDatas(DoActionDatas);
		DoAction->SetActorLabel(MakeLabel(InOwnerCharacter, "DoAction"));
		DoAction->FinishSpawning(TM);

		if (Equipment)
		{
			DoAction->SetEquipment(Equipment->IsEquipped());
		}

		if (Attachment)
		{
			Attachment->OnAttachmentBeginOverlap.AddDynamic(DoAction, &ACDoAction::OnAttachmentBeginOverlap);
			Attachment->OnAttachmentEndOverlap.AddDynamic(DoAction, &ACDoAction::OnAttachmentEndOverlap);
		}
	}

	*OutActionObject = NewObject<UCActionObject>();
	(*OutActionObject)->Attachment = Attachment;
	(*OutActionObject)->Equipment = Equipment;
	(*OutActionObject)->DoAction = DoAction;
	(*OutActionObject)->EquipmentColor = EquipmentColor;
}
FString UCActionData::MakeLabel(ACharacter* InOwnerCharacter, FString InMiddleName)
{
	FString Label;
	Label.Append(InOwnerCharacter->GetActorLabel());
	Label.Append("_");
	Label.Append(InMiddleName);
	Label.Append(GetName().Replace(TEXT("DA"), TEXT("")));
	
	return Label;
}
