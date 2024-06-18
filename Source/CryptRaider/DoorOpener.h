// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoorOpener.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UDoorOpener : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDoorOpener();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Getters and Setters
	UFUNCTION(BlueprintCallable)
	bool GetIsOpen();
	UFUNCTION(BlueprintCallable)
	bool GetIsUnlocked();

	UFUNCTION(BlueprintCallable)
	void SetIsOpen(bool Value);
	UFUNCTION(BlueprintCallable)
	void SetIsUnlocked(bool Value);

	UFUNCTION(BlueprintCallable)
	void ToggleIsOpen();
	UFUNCTION(BlueprintCallable)
	void ToggleIsUnlocked();

	UFUNCTION(BlueprintCallable)
	void OpenDoor(USceneComponent *Door, float RotationAmount, float DeltaTime);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float RotationOffset;

	UPROPERTY(EditAnywhere)
	float MoveTime = 4;

	bool IsOpen;
	bool IsUnlocked;

	FRotator StartRotation;
};
