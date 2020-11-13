// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpSpawner.h"

// Sets default values
APowerUpSpawner::APowerUpSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	PowerUpRespawnTime = 5.0f; //time in seconds to respawn
	RespawnTimer = 0.0f;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Binaries/3D/CuttingBoard/CuttingBoard.CuttingBoard'")); //i'm thinking like a raised dais for the powerup to hover over, also helps with getting the location
	StaticMesh->SetStaticMesh(MeshAsset.Object);
	SetRootComponent(StaticMesh);

	UClass* TempList[] = { APowerUp::StaticClass() }; //replace APowerUp with the desired actor(s) -- always followed by ::StaticClass()
	PowerUpList.Append(TempList, UE_ARRAY_COUNT(TempList));
}

// Called when the game starts or when spawned
void APowerUpSpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APowerUpSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!IsValid(SpawnedPowerUp)) {
		RespawnTimer += DeltaTime;
		if (RespawnTimer > PowerUpRespawnTime)
		{
			SpawnRandomPowerUp();
		}
	}
}

void APowerUpSpawner::SpawnRandomPowerUp()
{
	RespawnTimer = 0.0f;
	FActorSpawnParameters SpawnParameters;
	FVector SpawnLocation = GetActorLocation();
	SpawnLocation.Z = SpawnLocation.Z + 100.0f;

	int32 Index = FMath::RandRange(0, PowerUpList.Num() - 1);
	SpawnedPowerUp = GetWorld()->SpawnActor<AActor>(PowerUpList[Index], SpawnLocation, FRotator(0,0,0), SpawnParameters);
}

void APowerUpSpawner::CleanUp()
{
	if (IsValid(SpawnedPowerUp))
	{
		SpawnedPowerUp->Destroy();
	}
	Destroy();
}

bool APowerUpSpawner::IsValid(AActor* Actor)
{
	return (Actor && Actor->IsValidLowLevel() && !Actor->IsPendingKill());
}