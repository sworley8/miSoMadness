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

	if (whereToSpawn && whatToSpawn)
		for (int i = 0; i < 5; ++i)
			spawnCharacter();
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASpawnVolume::spawnCharacter() {
	if (GetLocalRole() == ROLE_Authority && whatToSpawn) {
		if (UWorld* const world = GetWorld()) {

			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			spawnParams.Instigator = GetInstigator();

			spawnLocation.Y = UKismetMathLibrary::RandomFloatInRange(-spawnLocationYRange, spawnLocationYRange);

			ACharacter* const spawnedPlayer = world->SpawnActor<ACharacter>(whatToSpawn, spawnLocation, FRotator(0.f, 0.f, 0.f), spawnParams);
		}
	}
}