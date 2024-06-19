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
}

void UTriggeredMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Mover->SetShouldMove(Trigger->GetIsTriggered());
}

