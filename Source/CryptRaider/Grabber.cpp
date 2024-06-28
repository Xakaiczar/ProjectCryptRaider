#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	float DefaultMaxGrabDistance = 400;
	float DefaultGrabRadius = 100;
	float DefaultHoldDistance = 200;

	MaxGrabDistance = (MaxGrabDistance > 0) ? MaxGrabDistance : DefaultMaxGrabDistance;
	GrabRadius = (GrabRadius > 0) ? GrabRadius : DefaultGrabRadius;
	HoldDistance = (HoldDistance > 0) ? HoldDistance : DefaultHoldDistance;
}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent *PhysicsHandle = GetPhysicsHandle();

	FHitResult OutHitResult;

	IsNearGrabbable = GetGrabbableInReach(OutHitResult);

	GrabbableName = IsNearGrabbable ? OutHitResult.GetActor()->GetActorNameOrLabel() : "";

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

	AActor *HitActor = OutHitResult.GetActor();

	if (!HitActor || HitActor->ActorHasTag("Untouchable")) return false;

	return HasHit;
}

void UGrabber::Grab()
{
	UPhysicsHandleComponent *PhysicsHandle = GetPhysicsHandle();

	if (!PhysicsHandle) return;

	FHitResult HitResult;
	bool HasHit = GetGrabbableInReach(HitResult);

	if (!HasHit) return;

	AActor *HitActor = HitResult.GetActor();

	UPrimitiveComponent *HitComponent = HitResult.GetComponent();

	HitComponent->SetSimulatePhysics(true);
	HitComponent->WakeAllRigidBodies();

	HitActor->Tags.Add(*GrabbedTag);
	HitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	UE_LOG(LogTemp, Display, TEXT("Detaching"));

	PhysicsHandle->GrabComponentAtLocationWithRotation(
		HitComponent,
		NAME_None,
		HitResult.ImpactPoint,
		GetComponentRotation()
	);

	IsGrabbing = true;
}

void UGrabber::Release()
{
	UPhysicsHandleComponent *PhysicsHandle = GetPhysicsHandle();

	if (!PhysicsHandle || !PhysicsHandle->GetGrabbedComponent()) return;

	UPrimitiveComponent *GrabbedComponent = PhysicsHandle->GetGrabbedComponent();

	GrabbedComponent->GetOwner()->Tags.Remove(*GrabbedTag);

	GrabbedComponent->WakeAllRigidBodies();

	PhysicsHandle->ReleaseComponent();

	IsGrabbing = false;
}

void UGrabber::OpenDoor()
{
	if (IsGrabbing) return;

	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	FHitResult OutHitResult;

	bool HasHit = GetWorld()->SweepSingleByChannel(
		OutHitResult,
		Start, End,
		FQuat::Identity,
		ECC_GameTraceChannel3,
		Sphere);

	if (!HasHit) return;

	UPrimitiveComponent *HitComponent = OutHitResult.GetComponent();
	FString Name = HitComponent->GetOwner()->GetActorNameOrLabel();

	UE_LOG(LogTemp, Display, TEXT("Hit: %s"), *Name);

	UDoorOpener *Door = OutHitResult.GetActor()->GetComponentByClass<UDoorOpener>();

	if (!Door) return;

	if (Door->GetIsUnlocked())
	{
		Door->ToggleIsOpen();
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Door %s is locked!"), *Name);
	}
}

bool UGrabber::GetIsGrabbing() const
{
	return IsGrabbing;
}

bool UGrabber::GetIsNearGrabbable() const
{
	return IsNearGrabbable;
}

FString UGrabber::GetGrabbableName() const
{
	return GrabbableName;
}
