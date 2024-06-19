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

	if (Door->GetIsOpen())
	{
		Door->SetIsUnlocked(true);
	}
	else
	{
		Door->SetIsUnlocked(!Trigger->GetIsTriggered());
	}
}

