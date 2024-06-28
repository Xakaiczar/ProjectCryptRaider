#include "Lock.h"

ULock::ULock()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void ULock::BeginPlay()
{
	Super::BeginPlay();
}

void ULock::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Trigger = GetOwner()->GetComponentByClass<UTriggerComponent>();

	if (!Trigger->GetIsTriggered()) return;

	AActor *Actor = GetOwner();

	if (!Actor) return;

	Actor->Tags.Remove("LockedLock");

	UPrimitiveComponent *Lock = Cast<UPrimitiveComponent>(Actor->GetRootComponent());

	Lock->SetSimulatePhysics(Trigger->GetIsTriggered());
}

