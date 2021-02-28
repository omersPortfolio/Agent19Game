// Fill out your copyright notice in the Description page of Project Settings.


#include "FInteractableDoor.h"
#include <Kismet/KismetMathLibrary.h>



AFInteractableDoor::AFInteractableDoor()
{
	DoorTimeline = CreateDefaultSubobject<UTimelineComponent>("Timeline");
	InterpFunction.BindUFunction(this, FName("InterpReturn"));
	TimelineFinish.BindUFunction(this, FName("OnFinish"));

	Closed = true;
}

void AFInteractableDoor::BeginPlay()
{
	Super::BeginPlay();

	if (CurveFloat)
	{
		DoorTimeline->AddInterpFloat(CurveFloat, InterpFunction, FName("Alpha"));
		DoorTimeline->SetTimelineFinishedFunc(TimelineFinish);
		DoorTimeline->SetLooping(false);
	}
}

void AFInteractableDoor::Interact()
{
	if (Closed)
	{
		DoorTimeline->Play();
	}
	else
	{
		DoorTimeline->Reverse();
	}
	Closed = !Closed;

}

void AFInteractableDoor::OnFinish()
{

}

void AFInteractableDoor::InterpReturn(float Value)
{
	Mesh->SetRelativeRotation(FRotator(0, UKismetMathLibrary::Ease(0, -110, Value, EEasingFunc::SinusoidalInOut), 0));
}
