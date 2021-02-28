// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FHUD.generated.h"

/**
 * 
 */
UCLASS()
class OKGAME_API AFHUD : public AHUD
{
	GENERATED_BODY()

public:

	AFHUD();

	UPROPERTY(EditAnywhere, Category = "Game HUD")
		TSubclassOf<class UUserWidget> PlayerGuiClass;

	UPROPERTY()
		class UUserWidget* PlayerGui;

protected:
	virtual void BeginPlay() override;
	
};
