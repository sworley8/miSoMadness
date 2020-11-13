// Fill out your copyright notice in the Description page of Project Settings.


#include "SumoItemSpawner.h"

// Sets default values
ASumoItemSpawner::ASumoItemSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemSpawnTime = 10.0f; //time in seconds to Spawn
	SpawnTimer = 0.0f;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Binaries/3D/CuttingBoard/CuttingBoard.CuttingBoard'"));
	StaticMesh->SetStaticMesh(MeshAsset.Object);
	SetRootComponent(StaticMesh);

	/*
	UClass* TempList[] = { APowerUp::StaticClass() };
	ItemList.Append(TempList, UE_ARRAY_COUNT(TempList));
	Uncomment this snippet to add c++ classes to the array.
	*/
}

// Called when the game starts or when spawned
void ASumoItemSpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASumoItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);SpawnTimer += DeltaTime; //should probably check to make sure there isn't anything in the way first
	if (SpawnTimer > ItemSpawnTime)
	{
		SpawnRandomItem();
	}
}

void ASumoItemSpawner::SpawnRandomItem()
{
	SpawnTimer = 0.0f;
	FActorSpawnParameters SpawnParameters;
	FVector SpawnLocation = GetActorLocation();
	SpawnLocation.Z = SpawnLocation.Z + 100.0f;

	int32 Index = FMath::RandRange(0, ItemList.Num() - 1);
	SpawnedItems.Add(GetWorld()->SpawnActor<AActor>(ItemList[Index], SpawnLocation, FRotator(0, 0, 0), SpawnParameters));
}

void ASumoItemSpawner::CleanUp() //destroys any spawned items and resets the array. won't destroy the spawner itself, though.
{
	for (AActor* Item : SpawnedItems)
	{
		if (IsValid(Item)) {
			Item->Destroy();
		}
	}
	SpawnedItems.Empty();
}

bool ASumoItemSpawner::IsValid(AActor* Actor)
{
	return (Actor && Actor->IsValidLowLevel() && !Actor->IsPendingKill());
}