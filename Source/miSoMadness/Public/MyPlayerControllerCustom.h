// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerControllerCustom.generated.h"

/**
 * 
 */
UCLASS()
class MISOMADNESS_API AMyPlayerControllerCustom : public APlayerController
{
	GENERATED_BODY()
public:
	// Constructor
	AMyPlayerControllerCustom(const FObjectInitializer& ObjectInitializer);

	FORCEINLINE UClass* GetPlayerPawnClass() { return MyPawnClass; }

protected:
	// Return The Correct Pawn Class Client Side
	UFUNCTION(Reliable, Client)
	void DeterminePawnClass();
	virtual void DeterminePawnClass_Implementation();

	// Use BeginPlay to start the functionality
	virtual void BeginPlay() override;

	// Set pawn class on server for this controller
	UFUNCTION(Reliable, Server, WithValidation)
	virtual void ServerSetPawn(TSubclassOf<APawn> InPawnClass);
	virtual void ServerSetPawn_Implementation(TSubclassOf<APawn> InPawnClass);
	virtual bool ServerSetPawn_Validate(TSubclassOf<APawn> InPawnClass);

	// Actual Pawn class we want to use
	UPROPERTY(Replicated)
	TSubclassOf<APawn> MyPawnClass;

	// First pawn type to use
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "My Controller")
	TSubclassOf<APawn> PawnToUseA;

	// First pawn type to use
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "My Controller")
	TSubclassOf<APawn> PawnToUseB;
	


	
};
