// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetOwner()->GetActorLocation();
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ShouldMove)
	{
		FVector Destination = StartLocation + MoveOffset;
		MoveTo(Destination, DeltaTime);
	}
	else
	{
		MoveTo(StartLocation, DeltaTime);
	}
}

void UMover::Move(float DeltaTime)
{
    FVector CurrentLocation = GetOwner()->GetActorLocation();
    FVector EndLocation = StartLocation + MoveOffset;
    float Speed = FVector::Distance(StartLocation, EndLocation) / MoveTime;

    FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, EndLocation, DeltaTime, Speed);

    GetOwner()->SetActorLocation(NewLocation);
}

void UMover::MoveTo(FVector Destination, float DeltaTime)
{
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	float Speed = MoveOffset.Length() / MoveTime;

	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, Destination, DeltaTime, Speed);

	GetOwner()->SetActorLocation(NewLocation);
}

void UMover::SetStartLocation(FVector NewLocation)
{
	StartLocation = NewLocation;
}

bool UMover::GetShouldMove()
{
	return UMover::ShouldMove;
}

void UMover::SetShouldMove(bool NewValue)
{
    ShouldMove = NewValue;
}