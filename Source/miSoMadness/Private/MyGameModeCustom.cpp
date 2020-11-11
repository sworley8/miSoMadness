// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeCustom.h"

AMyGameModeCustom::AMyGameModeCustom(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	/* Use our custom Player-Controller Class */
	PlayerControllerClass = AMyPlayerControllerCustom::StaticClass();
}

UClass* AMyGameModeCustom::GetDefaultPawnClassForController(AController* InController)
{
	/* Override Functionality to get Pawn from PlayerController */
	AMyPlayerControllerCustom* MyController = Cast<AMyPlayerController>(InController);
	if (MyController)
	{
		return MyController->GetPlayerPawnClass();
	}

	/* If we don't get the right Controller, use the Default Pawn */
	return DefaultPawnClass;
}