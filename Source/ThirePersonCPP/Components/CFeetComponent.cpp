#include "CFeetComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

UCFeetComponent::UCFeetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	LeftSocket = "Foot_L";
	RightSocket = "Foot_R";

	Additional = 55.0f;
	FootHeight = 5.0f;
	InterpSpeed = 10.0f;

	DrawDebugType = EDrawDebugTrace::ForOneFrame;
}


void UCFeetComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
}


void UCFeetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float LeftDistance;
	FRotator LeftRotation;
	Trace(LeftSocket, LeftDistance, LeftRotation);

	float RightDistance;
	FRotator RightRotation;
	Trace(RightSocket, RightDistance, RightRotation);

	float Floating=FMath::Min(LeftDistance, RightDistance);

	// World Space
	Data.PelvisDistance.Z = UKismetMathLibrary::FInterpTo(Data.PelvisDistance.Z, Floating, DeltaTime, InterpSpeed);

	// Bone Space(Local Space)
	// In Local Space, X Axis is Up Vector?
	Data.LeftDistance.X = UKismetMathLibrary::FInterpTo(Data.LeftDistance.X, LeftDistance - Floating,DeltaTime, InterpSpeed); // 0 float / - float
	Data.RightDistance.X = UKismetMathLibrary::FInterpTo(Data.RightDistance.X, -(RightDistance - Floating), DeltaTime, InterpSpeed);

	// World Space
	Data.LeftRotation = UKismetMathLibrary::RInterpTo(Data.LeftRotation, LeftRotation, DeltaTime, InterpSpeed);
	Data.RightRotation = UKismetMathLibrary::RInterpTo(Data.RightRotation, RightRotation, DeltaTime, InterpSpeed);
}

void UCFeetComponent::Trace(FName InSocket, float& OutDistance, FRotator& OutRotation)
{
	OutDistance = 0.f;
	OutRotation = FRotator::ZeroRotator;
	FVector SocketLocation = OwnerCharacter->GetMesh()->GetSocketLocation(InSocket);
	FVector Start(SocketLocation.X, SocketLocation.Y, OwnerCharacter->GetActorLocation().Z);

	float CapsuleHalfHeight = OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	float TraceZ = Start.Z - CapsuleHalfHeight - Additional;

	FVector End(Start.X, Start.Y, TraceZ);

	TArray<AActor*> Ignores;
	Ignores.Add(OwnerCharacter);

	FHitResult Hit;
	UKismetSystemLibrary::LineTraceSingle
	(
		GetWorld(),
		Start,
		End,
		UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility),
		true,
		Ignores,
		DrawDebugType,
		Hit,
		true
	);

	CheckFalse(Hit.bBlockingHit);
	//CheckFalse(Hit.IsValidBlockingHit());

	float DigLength = (Hit.ImpactPoint - Hit.TraceEnd).Size();
	OutDistance = FootHeight + DigLength - Additional;

	FVector ImpactNoraml = Hit.ImpactNormal;
	float Pitch = -UKismetMathLibrary::DegAtan2(ImpactNoraml.X, ImpactNoraml.Z);
	float Roll = UKismetMathLibrary::DegAtan2(ImpactNoraml.Y, ImpactNoraml.Z);

	Pitch = FMath::Clamp(Pitch, -30.0f, 30.0f);
	Roll = FMath::Clamp(Roll, -15.0f, 15.0f);

	FRotator ImpactRotation(Pitch, 0.f, Roll);
	OutRotation = ImpactRotation;
}

