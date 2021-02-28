// Fill out your copyright notice in the Description page of Project Settings.


#include "FInteractableLight.h"

AFInteractableLight::AFInteractableLight()
{
	State = true;
	Intensity = 10000.0f;
	Light = CreateDefaultSubobject<USpotLightComponent>("Light");
	Light->SetupAttachment(RootComponent);
}

void AFInteractableLight::Interact()
{
	if (State)
	{
		Light->SetIntensity(0);
	}
	else
	{
		Light->SetIntensity(Intensity);
	}
	State = !State;
}

void AFInteractableLight::BeginPlay()
{
	Super::BeginPlay();
	Light->SetIntensity(Intensity);
}
