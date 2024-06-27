// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "DoorOpener.h"
#include "Grabber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	UGrabber();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Grab();

	UFUNCTION(BlueprintCallable)
	void Release();

	UFUNCTION(BlueprintCallable)
	void OpenDoor();
	
	UFUNCTION(BlueprintCallable)
	bool GetIsGrabbing() const;

	UFUNCTION(BlueprintCallable)
	bool GetIsNearGrabbable() const;

	UFUNCTION(BlueprintCallable)
	FString GetGrabbableName() const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float MaxGrabDistance = 400;

	UPROPERTY(EditAnywhere)
	float GrabRadius = 100;

	UPROPERTY(EditAnywhere)
	float HoldDistance = 200;

	FString const GrabbedTag = "Grabbed";

	bool IsGrabbing = false;

	bool IsNearGrabbable = false;

	FString GrabbableName = "";

	UPhysicsHandleComponent* GetPhysicsHandle() const;
	
	bool GetGrabbableInReach(FHitResult& OutHitResult) const;
};
