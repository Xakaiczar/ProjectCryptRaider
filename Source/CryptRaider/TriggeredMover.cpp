#include "TriggeredMover.h"

UTriggeredMover::UTriggeredMover()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggeredMover::BeginPlay()
{
	Super::BeginPlay();

	Trigger = GetOwner()->GetComponentByClass<UTriggerComponent>();
	Mover = GetOwner()->GetComponentByClass<UMover>();

	FString TriggerText = Trigger->GetIsTriggered() ? "true" : "false";
	FString MoverText = Mover->GetShouldMove() ? "true" : "false";

	UE_LOG(LogTemp, Display, TEXT("Trigger Is Triggered: %s"), *TriggerText);
	UE_LOG(LogTemp, Display, TEXT("Mover Should Move: %s"), *MoverText);
}

void UTriggeredMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FString TriggerText = Trigger->GetIsTriggered() ? "true" : "false";
	FString MoverText = Mover->GetShouldMove() ? "true" : "false";

	UE_LOG(LogTemp, Display, TEXT("Trigger Is Triggered: %s"), *TriggerText);
	UE_LOG(LogTemp, Display, TEXT("Mover Should Move: %s"), *MoverText);
}

