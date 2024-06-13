// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent *PhysicsHandle = GetPhysicsHandle();

	if (!PhysicsHandle || !PhysicsHandle->GetGrabbedComponent()) return;

	FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;

	PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	return GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}

bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult) const
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);

	bool HasHit = GetWorld()->SweepSingleByChannel(
		OutHitResult,
		Start, End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere
	);

	return HasHit;
}

void UGrabber::Grab()
{
	UPhysicsHandleComponent *PhysicsHandle = GetPhysicsHandle();

	if (!PhysicsHandle) return;

	FHitResult HitResult;
	bool HasHit = GetGrabbableInReach(HitResult);

	if (!HasHit) return;

	UPrimitiveComponent *HitComponent = HitResult.GetComponent();

	HitComponent->SetSimulatePhysics(true);
	HitComponent->WakeAllRigidBodies();

	AActor *HitActor = HitResult.GetActor();

	HitActor->Tags.Add(*GrabbedTag);
	HitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	UE_LOG(LogTemp, Display, TEXT("Detaching"));

	PhysicsHandle->GrabComponentAtLocationWithRotation(
		HitComponent,
		NAME_None,
		HitResult.ImpactPoint,
		GetComponentRotation()
	);
}

void UGrabber::Release()
{
	UPhysicsHandleComponent *PhysicsHandle = GetPhysicsHandle();

	if (!PhysicsHandle || !PhysicsHandle->GetGrabbedComponent()) return;

	UPrimitiveComponent *GrabbedComponent = PhysicsHandle->GetGrabbedComponent();

	GrabbedComponent->GetOwner()->Tags.Remove(*GrabbedTag);

	GrabbedComponent->WakeAllRigidBodies();

	PhysicsHandle->ReleaseComponent();
}