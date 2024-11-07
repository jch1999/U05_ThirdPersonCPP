#include "CActionData.h"
#include "CEquipment.h"
#include "Global.h"
#include "GameFramework/Character.h"

void UCActionData::BeginPlay(ACharacter* InOwnerCharacter)
{
	CheckNull(InOwnerCharacter);

	if (EquipmentClass)
	{
		FTransform TM;

		Equipment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACEquipment>(EquipmentClass, TM, InOwnerCharacter, nullptr);
		Equipment->SetData(EquipmentData);
		Equipment->SetColor(EquipmentColor);
		Equipment->SetActorLabel(MakeLabel(InOwnerCharacter, "Equipment"));
		Equipment->FinishSpawning(TM);
	}
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
