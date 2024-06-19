// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    AActor *Actor = GetAcceptableActor();

    if (Actor && Mover)
    {
        UPrimitiveComponent *Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());

        if (Component)
        {
            Component->SetSimulatePhysics(false);
        }

        Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);

        if (ShouldSnapTriggeringObject)
        {
            Actor->SetActorRelativeRotation(SnapRotation);
            Actor->SetActorRelativeLocation(SnapLocation);
        }

        IsTriggered = true;
    }
    else
    {
        IsTriggered = false;
    }
}

void UTriggerComponent::SetMover(UMover *NewMover)
{
    Mover = NewMover;
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
    TArray<AActor*> Actors;

    GetOverlappingActors(Actors);

    for (AActor *Actor : Actors)
    {
        if (Actor->ActorHasTag(TriggerTagName) && CanBeUsedAsTrigger(Actor)) return Actor;
    }

    return nullptr;
}

bool UTriggerComponent::CanBeUsedAsTrigger(AActor *Actor) const
{
    return (ObjectMustBeReleased) ? ObjectMustBeReleased && !Actor->ActorHasTag("Grabbed") : true;
}

bool UTriggerComponent::GetIsTriggered()
{
    return IsTriggered;
}