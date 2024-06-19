#include "DoorLocker.h"

UDoorLocker::UDoorLocker()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDoorLocker::BeginPlay()
{
	Super::BeginPlay();

	Trigger = GetOwner()->GetComponentByClass<UTriggerComponent>();
	Door = GetOwner()->GetComponentByClass<UDoorOpener>();

}

void UDoorLocker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Door->SetIsUnlocked(!Trigger->GetIsTriggered());
}

