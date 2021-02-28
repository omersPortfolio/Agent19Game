// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FInteractableBase.h"
#include "Components/TimelineComponent.h"
#include "FInteractableDoor.generated.h"

/**
 * 
 */
UCLASS()
class OKGAME_API AFInteractableDoor : public AFInteractableBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	bool Closed;

public:
	AFInteractableDoor();

	virtual void Interact() override;

	UFUNCTION()
	void OnFinish();

	UFUNCTION()
	void InterpReturn(float Value);

	FOnTimelineFloat InterpFunction{};
	FOnTimelineEvent TimelineFinish{};

	UPROPERTY()
	UTimelineComponent* DoorTimeline;

	UPROPERTY(EditAnywhere)
	UCurveFloat* CurveFloat;
	
};
