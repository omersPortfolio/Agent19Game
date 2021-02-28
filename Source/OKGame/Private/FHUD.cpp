// Fill out your copyright notice in the Description page of Project Settings.


#include "FHUD.h"

#include <Blueprint/UserWidget.h>

AFHUD::AFHUD()
{
	/*static ConstructorHelpers::FClassFinder<UUserWidget> playerHud(TEXT("/Game/Blueprints/UI/WBP_UI"));
	if (playerHud.Succeeded())
		PlayerGuiClass = playerHud.Class;*/
}

void AFHUD::BeginPlay()
{
	/*PlayerGui = CreateWidget<UUserWidget>(GetGameInstance(), PlayerGuiClass);
	PlayerGui->AddToViewport();*/
}