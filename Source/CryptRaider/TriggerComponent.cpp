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

    if (Actor == nullptr)
    {
        Mover->SetShouldMove(false);
        
        // UE_LOG(LogTemp, Display, TEXT("No Overlapping Actors"));
    }
    else
    {
        Mover->SetShouldMove(true);

        // FString Name = GetAcceptableActor()->GetActorNameOrLabel();

        // UE_LOG(LogTemp, Display, TEXT("Overlapping Actor: %s"), *Name);
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
        if (Actor->ActorHasTag(TriggerTagName)) return Actor;
    }

    return nullptr;
}