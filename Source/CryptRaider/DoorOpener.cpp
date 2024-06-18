// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorOpener.h"

UDoorOpener::UDoorOpener()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDoorOpener::BeginPlay()
{
	Super::BeginPlay();
}

void UDoorOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UDoorOpener::GetIsOpen()
{
	return IsOpen;
}

bool UDoorOpener::GetIsUnlocked()
{
	return IsUnlocked;
}

void UDoorOpener::SetIsOpen(bool Value)
{
	IsOpen = Value;
}

void UDoorOpener::SetIsUnlocked(bool Value)
{
	IsUnlocked = Value;
}

void UDoorOpener::ToggleIsOpen()
{
	SetIsOpen(!IsOpen);
}

void UDoorOpener::ToggleIsUnlocked()
{
	SetIsUnlocked(!IsUnlocked);
}

void UDoorOpener::OpenDoor(USceneComponent *Door, float RotationAmount, float DeltaTime)
{
	// Door->SetWorldRotation(FRotator(-90, 0, 270));
	// Door->AddLocalRotation(FRotator(0, 180, 0));

	FRotator CurrentRotation = Door->GetRelativeRotation();
	FRotator EndRotation = FRotator(0, RotationAmount, 0);
	float Speed = FVector::Distance(CurrentRotation.Vector(), EndRotation.Vector()) / MoveTime;

	FRotator NewRotation = FMath::VInterpConstantTo(CurrentRotation.Vector(), EndRotation.Vector(), DeltaTime, Speed).Rotation();

	Door->SetRelativeRotation(NewRotation);
	// GetOwner()->SetActorLocation(NewLocation);
}