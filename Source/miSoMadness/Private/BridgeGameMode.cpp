// Fill out your copyright notice in the Description page of Project Settings.

#include "BridgeGameMode.h"

// Sets default values
ABridgeGameMode::ABridgeGameMode()
{
}

// Called when the game starts or when spawned
void ABridgeGameMode::BeginPlay()
{
	Super::BeginPlay();
	SpawnRandomBridgeItems(4); //just here as a simple test for now
}

void ABridgeGameMode::SpawnBridgeItem(UStaticMesh* SpawnMesh, FVector SpawnLocation, FRotator SpawnRotation)
{
	FActorSpawnParameters SpawnParameters;
	ABridgeItem* SpawnedBridgeItem = GetWorld()->SpawnActor<ABridgeItem>(ABridgeItem::StaticClass(), SpawnLocation, SpawnRotation, SpawnParameters);
	SpawnedBridgeItem->ChangeMesh(SpawnMesh);
	BridgeItems.Add(SpawnedBridgeItem);
}

void ABridgeGameMode::SpawnRandomBridgeItems(int32 NumberOfItems) //Spawns BridgeItems so that there is an even balance of mesh diversity
{
	while (NumberOfItems > 0)
	{
		TArray<UStaticMesh*> MeshesCopy(BridgeItemMeshes);
		int32 Iterations = FMath::Min(MeshesCopy.Num(), NumberOfItems);
		for (int32 i = 0; i < Iterations; i++)
		{
			int32 Index = FMath::RandRange(0, MeshesCopy.Num() - 1);
			SpawnBridgeItem(MeshesCopy[Index], FVector(0, 0, 0), FRotator(0, 0, 0)); //Currently spawns everything in the same place and at the same time
			MeshesCopy.RemoveAt(Index);
		}
		NumberOfItems -= Iterations;
	}
}

