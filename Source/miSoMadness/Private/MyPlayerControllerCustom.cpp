// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerControllerCustom.h"

AMyPlayerControllerCustom::AMyPlayerControllerCustom(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer){
	PawnToUserA = NULL;
	PawnToUserB = NULL;

	bReplicates = true;
}

void AMyPlayerControllerCustom::BeginPlay() 
{
	Super::BeginPlay();

	DeterminePawnClass();
}

void AMyPlayerControllerCustom::DeterminePawnClass_Implementation()
{
	if (IsLocalController()) // Only do this locally (Not Client-Only, since SErver wants thiss too)
	{
		//Load Text File Into String Array
		TArray<FString> TextStrings;
		const FString FilePath = FPaths::GameSourceDir() + "Textfiles/PlayersSettings.txt";

		// Use PawnA if the Text File tells us to
		if (TextStrings[0] == "PawnA") {
			ServerSetPawn(PawnToUseA);
			return;
		}

		ServerSetPawn(PawnToUseB);
		return;
	}
}

bool AMyPlayerControllerCustom::ServerSetPawn_Validate(TSubclassOf<APawn> InPawnClass) 
{
	return true;

}

void AMyPlayerControllerCustom::ServerSetPawn_Implementation(TSubclassOf<APawn> InPawnClass) 
{
	MyPawnClass = InPawnClass;

	// Just in the case we didn't get the PawnClass ont he server in time
	GetWorld()->GetAuthGameMode()->RestartPlayer(this);
}

// Replication
void AMyPlayerControllerCustom::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProbs) const
{
	DORE
}
