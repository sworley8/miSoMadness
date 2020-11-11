// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeCustom.generated.h"

/**
 * 
 */
UCLASS()
class MISOMADNESS_API AMyGameModeCustom : public AGameModeBase
{
	GENERATED_UCLASS_BODY()

	UClass* GetDefaultPawnClassForController(AController* InController) override;
	
};
