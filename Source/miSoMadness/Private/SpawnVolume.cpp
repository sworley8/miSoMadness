// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "SpawnVolume.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (GetLocalRole() == ROLE_Authority) {
		// Only the Server of networking game needs to take care of below

		whereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
		RootComponent = whereToSpawn;
	}

}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();

	spawnLocation = GetWorld()->GetFirstPlayerController()->GetSpawnLocation();
	spawnLocationsSet.Add(spawnLocation);
	
	/*
	* Sabin Kim: playerNum is always 0 for some reason. plz help
	*/
	playerNum = GetWorld()->PlayerNum;
	UE_LOG(LogTemp, Error, TEXT("%d players in the game"), playerNum);
	// Testing to see if 10 PlayerStart objects are properly instantiated if there are 10 players
	if (playerNum < 2)
		playerNum = 10;

	if (whereToSpawn) {
		for (int i = 0; i < playerNum - 1; ++i)
			createPlayerStart();
	}
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASpawnVolume::createPlayerStart() {
	if (UWorld* const world = GetWorld()) {

		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = GetInstigator();

		spawnLocation.X = UKismetMathLibrary::RandomFloatInRange(20.f, FMath::Max(50.f, spawnLocationXRange));
		spawnLocation.Y = UKismetMathLibrary::RandomFloatInRange(-spawnLocationYRange, spawnLocationYRange);
		while (spawnLocationsSet.Contains(spawnLocation)) {
			spawnLocation.X = UKismetMathLibrary::RandomFloatInRange(20.f, spawnLocationXRange);
			spawnLocation.Y = UKismetMathLibrary::RandomFloatInRange(-spawnLocationYRange, spawnLocationYRange);
		}

		world->SpawnActor<APlayerStart>(spawnLocation, FRotator(0.f, 0.f, 0.f), spawnParams);

		UE_LOG(LogTemp, Error, TEXT("Player Start at %s"), *spawnLocation.ToString());
	}
}