// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Mover.h"
#include "TriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CRYPTRAIDER_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	UTriggerComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetMover(UMover* Mover);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	FName TriggerTagName;

	UPROPERTY(EditAnywhere)
	bool ShouldSnapTriggeringObject;

	UPROPERTY(EditAnywhere)
	bool ObjectMustBeReleased;

	UPROPERTY(EditAnywhere)
	FVector SnapLocation;

	UPROPERTY(EditAnywhere)
	FRotator SnapRotation;

	UMover *Mover;

	bool IsTriggered = false;

	AActor* GetAcceptableActor() const;

	bool CanBeUsedAsTrigger(AActor* Actor) const;
};